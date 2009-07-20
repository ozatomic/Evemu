/*
	------------------------------------------------------------------------------------
	LICENSE:
	------------------------------------------------------------------------------------
	This file is part of EVEmu: EVE Online Server Emulator
	Copyright 2006 - 2008 The EVEmu Team
	For the latest information visit http://evemu.mmoforge.org
	------------------------------------------------------------------------------------
	This program is free software; you can redistribute it and/or modify it under
	the terms of the GNU Lesser General Public License as published by the Free Software
	Foundation; either version 2 of the License, or (at your option) any later
	version.

	This program is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
	FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License along with
	this program; if not, write to the Free Software Foundation, Inc., 59 Temple
	Place - Suite 330, Boston, MA 02111-1307, USA, or go to
	http://www.gnu.org/copyleft/lesser.txt.
	------------------------------------------------------------------------------------
	Author:		Zhur
*/

#include "EvemuPCH.h"

PyCallable_Make_InnerDispatcher(JumpCloneService)

class JumpCloneBound
: public PyBoundObject {
public:
	
	PyCallable_Make_Dispatcher(JumpCloneBound)
	
	JumpCloneBound(PyServiceMgr *mgr, StationDB *db)
	: PyBoundObject(mgr),
	  m_db(db),
	  m_dispatch(new Dispatcher(this))
	{
		_SetCallDispatcher(m_dispatch);
		
		PyCallable_REG_CALL(JumpCloneBound, GetCloneState)
		PyCallable_REG_CALL(JumpCloneBound, InstallCloneInStation)
	}
	virtual ~JumpCloneBound() { delete m_dispatch; }
	virtual void Release() {
		//I hate this statement
		delete this;
	}
	
	PyCallable_DECL_CALL(GetCloneState)
	PyCallable_DECL_CALL(InstallCloneInStation)

protected:
	StationDB *const m_db;		//we do not own this
	Dispatcher *const m_dispatch;	//we own this
};



JumpCloneService::JumpCloneService(PyServiceMgr *mgr, DBcore *db)
: PyService(mgr, "jumpCloneSvc"),
  m_dispatch(new Dispatcher(this)),
  m_db(db)
{
	_SetCallDispatcher(m_dispatch);
	
//	PyCallable_REG_CALL(JumpCloneService, )
}

JumpCloneService::~JumpCloneService() {
	delete m_dispatch;
}

PyBoundObject *JumpCloneService::_CreateBoundObject(Client *c, const PyRep *bind_args) {
	_log(CLIENT__MESSAGE, "JumpCloneService bind request for:");
	bind_args->Dump(stdout, "    ");

	return(new JumpCloneBound(m_manager, &m_db));
}

PyResult JumpCloneBound::Handle_InstallCloneInStation(PyCallArgs &call) {
	//takes no arguments, returns no arguments

	_log(CLIENT__ERROR, "Unhandled InstallCloneInStation");
	
	return(new PyRepNone());
}

PyResult JumpCloneBound::Handle_GetCloneState(PyCallArgs &call) {
	
	//returns (clones, implants, timeLastJump)
	//where jumpClones is a rowset? with at least columns: jumpCloneID, locationID

	_log(CLIENT__ERROR, "Unimplemented GetCloneState");

	PyRepDict *d = new PyRepDict;
	d->add("clones", new PyRepNone);
	d->add("implants", new PyRepNone);
	d->add("timeLastJump", new PyRepNone);

	return(new PyRepObject("util.KeyVal", d));
}

/*
PyResult JumpCloneService::Handle_(PyCallArgs &call) {
	PyRep *result = NULL;

	return result;
}*/























