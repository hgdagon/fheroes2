/***************************************************************************
 *   Copyright (C) 2009 by Andrey Afletdinov <fheroes2@gmail.com>          *
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

#ifndef H2PAIRS_H_
#define H2PAIRS_H_

#include <utility>

#include "color.h"
#include "mp2.h"
#include "resource.h"

class IndexDistance : public std::pair<int32_t, uint32_t>
{
public:
    IndexDistance()
        : std::pair<int32_t, uint32_t>( -1, 0 ){};
    IndexDistance( int32_t i, uint32_t d )
        : std::pair<int32_t, uint32_t>( i, d ){};

    static bool Shortest( const IndexDistance & id1, const IndexDistance & id2 )
    {
        return id1.second < id2.second;
    };
    static bool Longest( const IndexDistance & id1, const IndexDistance & id2 )
    {
        return id1.second > id2.second;
    };
};

StreamBase & operator>>( StreamBase &, IndexDistance & );

class IndexObject : public std::pair<int32_t, int>
{
public:
    IndexObject()
        : std::pair<int32_t, int>( -1, MP2::OBJ_ZERO ){};
    IndexObject( int32_t index, int object )
        : std::pair<int32_t, int>( index, object ){};

    bool isIndex( int32_t index ) const
    {
        return index == first;
    };
    bool isObject( int object ) const
    {
        return object == second;
    };
};

StreamBase & operator>>( StreamBase &, IndexObject & );

class ObjectColor : public std::pair<int, int>
{
public:
    ObjectColor()
        : std::pair<int, int>( MP2::OBJ_ZERO, Color::NONE ){};
    ObjectColor( int object, int color )
        : std::pair<int, int>( object, color ){};

    bool isObject( int object ) const
    {
        return object == first;
    };
    bool isColor( int colors ) const
    {
        return ( colors & second ) != 0;
    };
};

StreamBase & operator>>( StreamBase &, ObjectColor & );

class ResourceCount : public std::pair<int, uint32_t>
{
public:
    ResourceCount()
        : std::pair<int, uint32_t>( Resource::UNKNOWN, 0 ){};
    ResourceCount( int res, uint32_t count )
        : std::pair<int, uint32_t>( res, count ){};

    bool isResource( int res ) const
    {
        return res == first;
    };
    bool isValid( void ) const
    {
        return ( first & Resource::ALL ) && second;
    };
};

StreamBase & operator>>( StreamBase &, ResourceCount & );

#endif
