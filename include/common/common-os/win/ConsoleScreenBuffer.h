/**
 * @file win/ConsoleScreenBuffer.h
 *
 * This file is part of EVEmu: EVE Online Server Emulator.<br>
 * Copyright (C) 2006-2011 The EVEmu Team<br>
 * For the latest information visit <i>http://evemu.org</i>.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA, or go to
 * <i>http://www.gnu.org/copyleft/lesser.txt</i>.
 *
 * @author Bloody.Rabbit
 */

#ifndef __COMMON__WIN__CONSOLE_SCREEN_BUFFER_H__INCL__
#define __COMMON__WIN__CONSOLE_SCREEN_BUFFER_H__INCL__

#include "win/Handle.h"

namespace common
{
    namespace win
    {
        /**
         * @brief A handle to a console screen buffer.
         *
         * @author Bloody.Rabbit
         */
        class ConsoleScreenBuffer
        : public Handle
        {
        public:
            /// A handle to the default console output screen.
            static const ConsoleScreenBuffer DEFAULT_OUTPUT_SCREEN;

            /**
             * @brief A primary constructor, creates a new console screen buffer.
             *
             * @param[in] desiredAccess A desired access to the buffer.
             * @param[in] shareMode     A share mode for the buffer.
             */
            ConsoleScreenBuffer( DWORD desiredAccess = GENERIC_READ | GENERIC_WRITE,
                                 DWORD shareMode = FILE_SHARE_READ );

            /**
             * @brief Creates a new console screen buffer.
             *
             * Any previous handle is closed.
             *
             * @param[in] desiredAccess A desired access to the buffer.
             * @param[in] shareMode     A share mode for the buffer.
             *
             * @return An error code.
             */
            DWORD Create( DWORD desiredAccess = GENERIC_READ | GENERIC_WRITE,
                          DWORD shareMode = FILE_SHARE_READ );

            /**
             * @brief Sets this buffer as active.
             *
             * An active console screen buffer is the one
             * which is currently displayed.
             *
             * @return An error code.
             */
            DWORD SetActive();
            /**
             * @brief Sets attributes of console text.
             *
             * @param[in] attributes The new attributes.
             *
             * @return An error code.
             */
            DWORD SetTextAttributes( WORD attributes );

        protected:
            /**
             * @brief A protected constructor, takes a handle directly.
             *
             * @param[in] handle The handle.
             */
            ConsoleScreenBuffer( HANDLE handle );
        };
    }
}

#endif /* !__COMMON__WIN__CONSOLE_SCREEN_BUFFER_H__INCL__ */