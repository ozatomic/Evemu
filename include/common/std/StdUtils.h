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
    Author:     Aim, Captnoord, Zhur, Bloody.Rabbit
*/

#ifndef __STD__STD_UTILS_H__INCL__
#define __STD__STD_UTILS_H__INCL__

/*
 * WIN32:
 *   asprintf
 *   vasprintf
 */
#ifdef WIN32
int asprintf( char** strp, const char* fmt, ... );
int vasprintf( char** strp, const char* fmt, va_list ap );
#endif /* WIN32 */

/*
 * CYGWIN:
 *   strupr
 *   strlwr
 */
#ifdef CYGWIN
char* strupr( char* tmp );
char* strlwr( char* tmp );
#endif /* CYGWIN */

/*
 * MSVC:
 *   snprintf
 *   vsnprintf
 *   strcasecmp
 *   strncasecmp
 *   strdup
 *   va_copy
 */
#ifdef MSVC
#   define snprintf            _snprintf
#   define strncasecmp         _strnicmp
#   define strcasecmp          _stricmp

#   define localtime_r( x, y ) \
    ( localtime_s( y, x ) )
#   define va_copy( a, b ) \
    ( memcpy( &( a ), &( b ), sizeof( va_list ) ) )

#   if( _MSC_VER < 1500 )
#       define vsnprintf _vsnprintf
#   else /* _MSC_VER >= 1500 */
#       define strdup _strdup
#   endif /* _MSC_VER >= 1500 */
#endif /* MSVC */

/*
 * MINGW:
 *   localtime_r
 *
 * Define localtime_r as a call to localtime.
 *
 * The page below says that MS's version of localtime uses
 * thread-specific storage, so this should not be a problem.
 *
 * http://msdn.microsoft.com/en-us/library/bf12f0hc(VS.80).aspx
 */
#ifdef MINGW
#   define localtime_r( x, y ) \
    ( (tm*)( memcpy( ( y ), localtime( x ), sizeof( tm ) ) ) )
#endif /* MINGW */

/*
 * finite
 * isnan
 */
#if defined( MSVC ) || defined( MINGW )
#   define finite _finite
#   define isnan  _isnan
#elif defined( FREE_BSD ) || defined( APPLE )
using std::finite;
using std::isnan;
#else /* !MSVC && !MINGW && !APPLE && !FREE_BSD */
#   define finite __finite
#   define isnan  __isnan
#endif /* !MSVC && !MINGW && !APPLE && !FREE_BSD */

#endif /* !__STD__STD_UTILS_H__INCL__ */