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
	Author:		Bloody.Rabbit
*/

#include "EvemuPCH.h"

/*
 * Skill
 */
Skill::Skill(
	ItemFactory &_factory,
	uint32 _skillID,
	// InventoryItem stuff:
	const Type &_type,
	const ItemData &_data )
: InventoryItem(_factory, _skillID, _type, _data)
{
}

Skill *Skill::Load(ItemFactory &factory, uint32 skillID, bool recurse)
{
	return InventoryItem::Load<Skill>( factory, skillID, recurse );
}

Skill *Skill::_Load(ItemFactory &factory, uint32 skillID)
{
	return InventoryItem::_Load<Skill>( factory, skillID );
}

Skill *Skill::_LoadItem(ItemFactory &factory, uint32 skillID,
	// InventoryItem stuff:
	const Type &type, const ItemData &data)
{
	return Skill::_LoadItem<Skill>( factory, skillID, type, data );
}

Skill *Skill::_LoadSkill(ItemFactory &factory, uint32 skillID,
	// InventoryItem stuff:
	const Type &type, const ItemData &data)
{
	return new Skill( factory, skillID, type, data );
}

Skill *Skill::Spawn(ItemFactory &factory, ItemData &data)
{
	uint32 skillID = _Spawn( factory, data );
	if( skillID == 0 )
		return NULL;
	return factory.GetSkill( skillID, false );
}

uint32 Skill::_Spawn(ItemFactory &factory, ItemData &data)
{
	// check it's a skill
	const Type *type = factory.GetType( data.typeID );
	if( type == NULL )
		return 0;

	if( type->categoryID() != EVEDB::invCategories::Skill )
	{
		_log( ITEM__ERROR, "Trying to spawn %s as Skill.", type->category().name().c_str() );
		return 0;
	}

	// spawn item, nothing else
	return InventoryItem::_Spawn( factory, data );
}

uint32 Skill::GetSPForLevel(uint8 level)
{
	return(SKILL_BASE_POINTS * skillTimeConstant() * pow(32, (level - 1) / 2.0));
}

bool Skill::SkillPrereqsComplete(Character &ch)
{
	InventoryItem *requiredSkill;

	if( requiredSkill1() != 0 )
	{
		requiredSkill = ch.GetByTypeFlag( requiredSkill1(), flagSkill );
		if( requiredSkill == NULL )
			requiredSkill = ch.GetByTypeFlag( requiredSkill1(), flagSkillInTraining );
		if( requiredSkill == NULL )
			return false;

		if( requiredSkill1Level() > requiredSkill->skillLevel() )
			return false;
	}

	if( requiredSkill2() != 0 )
	{
		requiredSkill = ch.GetByTypeFlag( requiredSkill2(), flagSkill );
		if( requiredSkill == NULL )
			requiredSkill = ch.GetByTypeFlag( requiredSkill2(), flagSkillInTraining );
		if( requiredSkill == NULL )
			return false;

		if( requiredSkill2Level() > requiredSkill->skillLevel() )
			return false;
	}

	if( requiredSkill3() != 0 )
	{
		requiredSkill = ch.GetByTypeFlag( requiredSkill3(), flagSkill );
		if( requiredSkill == NULL )
			requiredSkill = ch.GetByTypeFlag( requiredSkill3(), flagSkillInTraining );
		if( requiredSkill == NULL )
			return false;

		if( requiredSkill3Level() > requiredSkill->skillLevel() )
			return false;
	}

	return true;
}


