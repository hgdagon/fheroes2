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
#ifndef H2RESOURCE_H
#define H2RESOURCE_H

#include "gamedefs.h"
#include "serialize.h"

struct cost_t
{
    uint16_t gold;
    uint8_t wood;
    uint8_t mercury;
    uint8_t ore;
    uint8_t sulfur;
    uint8_t crystal;
    uint8_t gems;
};

#define COST_NONE                                                                                                                                                        \
    {                                                                                                                                                                    \
        0, 0, 0, 0, 0, 0, 0                                                                                                                                              \
    }

class ResourceCount;

#ifdef WITH_XML
class TiXmlElement;
void LoadCostFromXMLElement( cost_t &, const TiXmlElement & );
#endif

namespace Resource
{
    enum
    {
        UNKNOWN = 0x00,
        WOOD = 0x01,
        MERCURY = 0x02,
        ORE = 0x04,
        SULFUR = 0x08,
        CRYSTAL = 0x10,
        GEMS = 0x20,
        GOLD = 0x40,
        ALL = WOOD | MERCURY | ORE | SULFUR | CRYSTAL | GEMS | GOLD
    };
}

class Funds
{
public:
    Funds();
    Funds( int32_t _ore, int32_t _wood, int32_t _mercury, int32_t _sulfur, int32_t _crystal, int32_t _gems, int32_t _gold );
    Funds( int rs, uint32_t count );
    Funds( const cost_t & );
    Funds( const ResourceCount & );

    Funds operator+( const Funds & ) const;
    Funds operator*( uint32_t mul ) const;
    Funds operator-( const Funds & ) const;
    Funds & operator+=( const Funds & );
    Funds & operator*=( uint32_t mul );
    Funds & operator-=( const Funds & );
    Funds & operator=( const cost_t & );

    int32_t Get( int rs ) const;
    int32_t * GetPtr( int rs );

    bool operator<( const Funds & ) const;
    bool operator<=( const Funds & ) const;
    bool operator>( const Funds & ) const;
    bool operator>=( const Funds & ) const;

    int getLowestQuotient( const Funds & ) const;
    int GetValidItems( void ) const;
    uint32_t GetValidItemsCount( void ) const;

    void Trim( void ); // set all values to be >= 0

    void Reset( void );
    std::string String( void ) const;

    int32_t wood;
    int32_t mercury;
    int32_t ore;
    int32_t sulfur;
    int32_t crystal;
    int32_t gems;
    int32_t gold;
};

StreamBase & operator<<( StreamBase &, const cost_t & );
StreamBase & operator>>( StreamBase &, cost_t & );
StreamBase & operator<<( StreamBase &, const Funds & );
StreamBase & operator>>( StreamBase &, Funds & );

namespace Resource
{
    const char * String( int resource );
    int Rand( bool with_gold = false );

    /* return index sprite objnrsrc.icn */
    uint32_t GetIndexSprite( int resource );
    int FromIndexSprite( uint32_t index );

    /* return index sprite resource.icn */
    uint32_t GetIndexSprite2( int resource );
    int FromIndexSprite2( uint32_t index );

    class BoxSprite : protected Rect
    {
    public:
        BoxSprite( const Funds &, uint32_t );

        const Rect & GetArea( void ) const;
        void SetPos( int32_t, int32_t );
        void Redraw( void ) const;

        const Funds rs;
    };
}

#endif
