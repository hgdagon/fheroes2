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

#ifndef H2ARMY_H
#define H2ARMY_H

#include <string>
#include <utility>
#include <vector>

#include "army_troop.h"
#include "bitmodes.h"
#include "players.h"

#ifdef WITH_XML
#include "tinyxml.h"
#endif

class Castle;
class HeroBase;
class Heroes;

namespace Maps
{
    class Tiles;
}

class Troops : protected std::vector<Troop *>
{
public:
    Troops();
    Troops( const Troops & troops );
    virtual ~Troops();
    Troops & operator=( const Troops & rhs );

    void Assign( const Troop *, const Troop * );
    void Assign( const Troops & );
    void Insert( const Troops & );
    void PushBack( const Monster &, uint32_t );
    void PopBack( void );

    size_t Size( void ) const;

    Troop * GetTroop( size_t );
    const Troop * GetTroop( size_t ) const;

    void UpgradeMonsters( const Monster & );
    uint32_t GetCountMonsters( const Monster & ) const;

    uint32_t GetCount( void ) const;
    bool isValid( void ) const;
    bool HasMonster( const Monster & ) const;

    bool AllTroopsIsRace( int ) const;
    bool AllTroopsAreUndead() const;
    uint32_t GetUniqueCount( void ) const;

    bool JoinTroop( const Troop & );
    bool JoinTroop( const Monster &, uint32_t );
    bool CanJoinTroop( const Monster & ) const;

    void JoinTroops( Troops & );
    bool CanJoinTroops( const Troops & ) const;

    void MergeTroops();
    Troops GetOptimized( void ) const;

    virtual uint32_t GetAttack( void ) const;
    virtual uint32_t GetDefense( void ) const;
    virtual double GetStrength() const;

    uint32_t GetHitPoints( void ) const;
    uint32_t GetDamageMin( void ) const;
    uint32_t GetDamageMax( void ) const;

    void Clean( void );
    void UpgradeTroops( const Castle & );

    Troop * GetFirstValid( void );
    Troop * GetWeakestTroop( void );
    const Troop * GetSlowestTroop() const;

    void SortStrongest();
    void ArrangeForBattle( bool = false );

    void JoinStrongest( Troops &, bool );
    void KeepOnlyWeakest( Troops &, bool );

    void DrawMons32Line( int32_t, int32_t, uint32_t, uint32_t, uint32_t, uint32_t, bool, bool ) const;
    void SplitTroopIntoFreeSlots( const Troop & troop, const Troop & selectedSlot, const uint32_t slots );
    void AssignToFirstFreeSlot( const Troop &, const uint32_t splitCount );
    void JoinAllTroopsOfType( const Troop & targetTroop );
};

enum
{
    JOIN_NONE,
    JOIN_FREE,
    JOIN_COST,
    JOIN_FLEE
};

struct JoinCount : std::pair<int, uint32_t>
{
    JoinCount()
        : std::pair<int, uint32_t>( JOIN_NONE, 0 )
    {}
    JoinCount( int reason, uint32_t count )
        : std::pair<int, uint32_t>( reason, count )
    {}
};

class Army : public Troops, public Control
{
public:
    static std::string SizeString( uint32_t );
    static std::string TroopSizeString( const Troop & );

    // compare
    static bool WeakestTroop( const Troop *, const Troop * );
    static bool StrongestTroop( const Troop *, const Troop * );
    static bool SlowestTroop( const Troop *, const Troop * );
    static bool FastestTroop( const Troop *, const Troop * );
    static void SwapTroops( Troop &, Troop & );

    // 0: fight, 1: free join, 2: join with gold, 3: flee
    static JoinCount GetJoinSolution( const Heroes &, const Maps::Tiles &, const Troop & );
    static bool ArmyStrongerThanEnemy( const Army &, const Army & );

    static void DrawMons32Line( const Troops &, int32_t, int32_t, uint32_t, uint32_t = 0, uint32_t = 0 );
    static void DrawMonsterLines( const Troops & troops, int32_t posX, int32_t posY, uint32_t lineWidth, uint32_t drawPower, bool compact = true,
                                  bool isScouteView = true );

    Army( HeroBase * s = nullptr );
    Army( const Maps::Tiles & );
    Army( const Army & ) = delete;
    Army( Army && ) = delete;
    Army & operator=( const Army & ) = delete;
    Army & operator=( Army && ) = delete;
    ~Army();

    void Reset( bool = false ); // reset: soft or hard
    void setFromTile( const Maps::Tiles & tile );

    int GetRace( void ) const;
    int GetColor( void ) const;
    int GetControl( void ) const;
    uint32_t GetAttack( void ) const;
    uint32_t GetDefense( void ) const;

    double GetStrength() const;
    double getReinforcementValue( const Troops & reinforcement ) const;
    bool isStrongerThan( const Army & target, double safetyRatio = 1.0 ) const;

    void SetColor( int );

    int GetMorale( void ) const;
    int GetLuck( void ) const;
    int GetMoraleModificator( std::string * ) const;
    int GetLuckModificator( const std::string * ) const;
    uint32_t ActionToSirens( void );

    const HeroBase * GetCommander( void ) const;
    HeroBase * GetCommander( void );
    void SetCommander( HeroBase * );

    const Castle * inCastle( void ) const;

    std::string String( void ) const;

    void JoinStrongestFromArmy( Army & );
    void KeepOnlyWeakestTroops( Army & );

    void SetSpreadFormat( bool );
    bool isSpreadFormat( void ) const;

    bool isFullHouse( void ) const;
    bool SaveLastTroop( void ) const;

protected:
    friend StreamBase & operator<<( StreamBase &, const Army & );
    friend StreamBase & operator>>( StreamBase &, Army & );
#ifdef WITH_XML
    friend TiXmlElement & operator>>( TiXmlElement &, Army & );
#endif

    HeroBase * commander;
    bool combat_format;
    int color;
};

StreamBase & operator<<( StreamBase &, const Army & );
StreamBase & operator>>( StreamBase &, Army & );

#endif
