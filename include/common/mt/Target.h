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

#ifndef __MT__TARGET_H__INCL__
#define __MT__TARGET_H__INCL__

namespace Mt
{
    /**
     * @brief An execution target.
     *
     * @author Bloody.Rabbit
     */
    class Target
    {
    public:
        /**
         * @brief Processes the given Target.
         *
         * Static to avoid "delete this" in the code.
         *
         * @param[in] target The Target to process.
         */
        static void Process( Target* target );

        /// Must be virtual if proper destructor shall be invoked.
        virtual ~Target() {}

    protected:
        /**
         * @brief Determines whether the Target should be deleted when Run() returns.
         *
         * @retval true  Target should be deleted.
         * @retval false Target should not be deleted.
         */
        virtual bool deleteOnExit() = 0;

        /**
         * @brief Runs the target.
         */
        virtual void Run() = 0;
    };
}

#endif /* !__MT__TARGET_H__INCL__ */