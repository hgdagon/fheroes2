/***************************************************************************
 *   Copyright (C) 2011 by Andrey Afletdinov <fheroes2@gmail.com>          *
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

#ifndef H2GAMESTATIC_H
#define H2GAMESTATIC_H

#include "gamedefs.h"
#include "serialize.h"

namespace Skill
{
    struct stats_t;
    struct values_t;
    struct secondary_t;
}

namespace GameStatic
{
    struct Data
    {
        static Data & Get( void );
        // wrapper for stream
    };

    StreamBase & operator<<( StreamBase &, const Data & );
    StreamBase & operator>>( StreamBase &, const Data & );

    uint32_t GetLostOnWhirlpoolPercent( void );
    uint32_t GetGameOverLostDays( void );
    uint32_t GetOverViewDistance( uint32_t );

    uint32_t GetKingdomMaxHeroes( void );

    uint32_t GetCastleGrownWell( void );
    uint32_t GetCastleGrownWel2( void );
    uint32_t GetCastleGrownWeekOf( void );
    uint32_t GetCastleGrownMonthOf( void );

    uint32_t GetHeroesRestoreSpellPointsPerDay( void );
    uint32_t GetMageGuildRestoreSpellPointsPercentDay( int level );

    bool isCustomMonsterUpgradeOption();
    float GetMonsterUpgradeRatio();

    int32_t ObjectVisitedModifiers( int obj );

    int GetBattleMoatReduceDefense( void );

    const Skill::stats_t * GetSkillStats( int race );
    const Skill::values_t * GetSkillValues( int skill );
    const Skill::secondary_t * GetSkillForWitchsHut( void );

    uint32_t Spell_DD_Distance( void );
    uint32_t Spell_DD_SP( void );
    uint32_t Spell_DD_HP( void );

    void SetSpell_DD_Distance( int );
    void SetSpell_DD_SP( int );
    void SetSpell_DD_HP( int );
}

#ifdef WITH_XML
class TiXmlElement;
namespace Game
{
    void CastleUpdateGrowth( const TiXmlElement * );
    void KingdomUpdateStartingResource( const TiXmlElement * );
    void HeroesUpdateStatic( const TiXmlElement * );
    void KingdomUpdateStatic( const TiXmlElement * );
    void GameOverUpdateStatic( const TiXmlElement * );
    void OverViewUpdateStatic( const TiXmlElement * );
    void WhirlpoolUpdateStatic( const TiXmlElement * );
    void MonsterUpdateStatic( const TiXmlElement * );
    void SkillUpdateStatic( const TiXmlElement * );
}
#endif

#endif
