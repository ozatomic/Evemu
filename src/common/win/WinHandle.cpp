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
    Author:     Bloody.Rabbit
*/

#include "CommonPCH.h"

#include "win/WinHandle.h"

/*************************************************************************/
/* WinHandle                                                             */
/*************************************************************************/
WinHandle::WinHandle( HANDLE handle )
: mHandle( handle )
{
}

WinHandle::WinHandle( const WinHandle& oth )
: mHandle( INVALID_HANDLE )
{
    // pass to copy operator
    *this = oth;
}

WinHandle::~WinHandle()
{
    BOOL success;

    if( TRUE == isValid() )
    {
        success = Close();
        assert( TRUE == success );
    }
}

WinHandle& WinHandle::operator=( const WinHandle& oth )
{
    BOOL success;

    if( TRUE == isValid() )
    {
        success = Close();
        assert( TRUE == success );
    }

    // duplicate the target handle
    if( FALSE == oth.isValid() )
        mHandle = INVALID_HANDLE;
    else
    {
        success = ::DuplicateHandle( GetCurrentProcess(), oth.mHandle,
                                     GetCurrentProcess(), &mHandle,
                                     0, FALSE, DUPLICATE_SAME_ACCESS );
        assert( TRUE == success );
    }

    return *this;
}

BOOL WinHandle::Close()
{
    return ::CloseHandle( mHandle );
}

/*************************************************************************/
/* WinWaitableHandle                                                     */
/*************************************************************************/
WinWaitableHandle::WinWaitableHandle( HANDLE handle )
: WinHandle( handle )
{
}

DWORD WinWaitableHandle::Wait( DWORD timeout )
{
    return ::WaitForSingleObject( mHandle, timeout );
}
