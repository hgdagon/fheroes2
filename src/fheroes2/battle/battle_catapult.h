/***************************************************************************
 *   Copyright (C) 2010 by Andrey Afletdinov <fheroes2@gmail.com>          *
 *                                                                         *
 *   Part of the Free Heroes2 Engine:                                      *
 *   http://sourceforge.net/projects/fheroes2                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef H2BATTLE_CATAPULT_H
#define H2BATTLE_CATAPULT_H

#include "gamedefs.h"

class HeroBase;

namespace Battle
{
    enum
    {
        CAT_WALL1 = 1,
        CAT_WALL2 = 2,
        CAT_WALL3 = 3,
        CAT_WALL4 = 4,
        CAT_TOWER1 = 5,
        CAT_TOWER2 = 6,
        CAT_BRIDGE = 7,
        CAT_CENTRAL_TOWER = 8,
        CAT_MISS = 9
    };

    class Catapult
    {
    public:
        Catapult( const HeroBase & );

        static Point GetTargetPosition( int );

        uint32_t GetShots( void ) const
        {
            return catShots;
        }
        int GetTarget( const std::vector<uint32_t> & ) const;
        uint32_t GetDamage() const;

    private:
        uint32_t catShots;
        uint32_t doubleDamageChance;
        bool canMiss;
    };
}

#endif
