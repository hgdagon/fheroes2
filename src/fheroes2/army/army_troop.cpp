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

#include <sstream>

#include "army.h"
#include "army_troop.h"
#include "game.h"
#include "heroes_base.h"
#include "luck.h"
#include "morale.h"
#include "speed.h"

Troop::Troop()
    : Monster( Monster::UNKNOWN )
    , count( 0 )
{}

Troop::Troop( const Monster & m, uint32_t c )
    : Monster( m )
    , count( c )
{}

bool Troop::operator==( const Monster & m ) const
{
    return Monster::operator==( m );
}

bool Troop::isMonster( int mons ) const
{
    return GetID() == mons;
}

Monster Troop::operator()( void ) const
{
    return *this;
}

Monster Troop::GetMonster( void ) const
{
    return *this;
}

void Troop::Set( const Troop & t )
{
    SetMonster( t.GetMonster() );
    SetCount( t.GetCount() );
}

void Troop::Set( const Monster & m, uint32_t c )
{
    Set( Troop( m, c ) );
}

void Troop::SetMonster( const Monster & m )
{
    id = m.GetID();
}

void Troop::SetCount( uint32_t c )
{
    count = c;
}

void Troop::Reset( void )
{
    id = Monster::UNKNOWN;
    count = 0;
}

const char * Troop::GetName( void ) const
{
    return Monster::GetPluralName( count );
}

uint32_t Troop::GetCount( void ) const
{
    return count;
}

uint32_t Troop::GetHitPoints( void ) const
{
    return Monster::GetHitPoints() * count;
}

uint32_t Troop::GetDamageMin( void ) const
{
    return Monster::GetDamageMin() * count;
}

uint32_t Troop::GetDamageMax( void ) const
{
    return Monster::GetDamageMax() * count;
}

double Troop::GetStrength() const
{
    return Monster::GetMonsterStrength() * count;
}

double Troop::GetStrengthWithBonus( int bonusAttack, int bonusDefense ) const
{
    return Monster::GetMonsterStrength( Monster::GetAttack() + bonusAttack, Monster::GetDefense() + bonusDefense ) * count;
}

bool Troop::isValid( void ) const
{
    return Monster::isValid() && count;
}

bool Troop::isEmpty( void ) const
{
    return !isValid();
}

payment_t Troop::GetCost( void ) const
{
    return Monster::GetCost() * count;
}

payment_t Troop::GetUpgradeCost( void ) const
{
    return Monster::GetUpgradeCost() * count;
}

bool Troop::isBattle( void ) const
{
    return false;
}

bool Troop::isModes( uint32_t ) const
{
    return false;
}

std::string Troop::GetAttackString( void ) const
{
    return std::to_string( GetAttack() );
}

std::string Troop::GetDefenseString( void ) const
{
    return std::to_string( GetDefense() );
}

std::string Troop::GetShotString( void ) const
{
    return std::to_string( GetShots() );
}

std::string Troop::GetSpeedString( void ) const
{
    return Speed::String( GetSpeed() );
}

uint32_t Troop::GetHitPointsLeft( void ) const
{
    return 0;
}

uint32_t Troop::GetSpeed( void ) const
{
    return Monster::GetSpeed();
}

uint32_t Troop::GetAffectedDuration( uint32_t ) const
{
    return 0;
}

/* ArmyTroop */
ArmyTroop::ArmyTroop( const Army * a )
    : army( a )
{}

ArmyTroop::ArmyTroop( const Army * a, const Troop & t )
    : Troop( t )
    , army( a )
{}

ArmyTroop & ArmyTroop::operator=( const Troop & t )
{
    Set( t );
    return *this;
}

uint32_t ArmyTroop::GetAttack( void ) const
{
    return Troop::GetAttack() + ( army && army->GetCommander() ? army->GetCommander()->GetAttack() : 0 );
}

uint32_t ArmyTroop::GetDefense( void ) const
{
    return Troop::GetDefense() + ( army && army->GetCommander() ? army->GetCommander()->GetDefense() : 0 );
}

int ArmyTroop::GetColor( void ) const
{
    return army ? army->GetColor() : Color::NONE;
}

int ArmyTroop::GetMorale( void ) const
{
    return army && isAffectedByMorale() ? army->GetMorale() : Troop::GetMorale();
}

int ArmyTroop::GetLuck( void ) const
{
    return army ? army->GetLuck() : Troop::GetLuck();
}

void ArmyTroop::SetArmy( const Army & a )
{
    army = &a;
}

const Army * ArmyTroop::GetArmy( void ) const
{
    return army;
}

std::string ArmyTroop::GetAttackString( void ) const
{
    if ( Troop::GetAttack() == GetAttack() )
        return std::to_string( Troop::GetAttack() );

    std::ostringstream os;
    os << Troop::GetAttack() << " (" << GetAttack() << ")";
    return os.str();
}

std::string ArmyTroop::GetDefenseString( void ) const
{
    if ( Troop::GetDefense() == GetDefense() )
        return std::to_string( Troop::GetDefense() );

    std::ostringstream os;
    os << Troop::GetDefense() << " (" << GetDefense() << ")";
    return os.str();
}

StreamBase & operator<<( StreamBase & msg, const Troop & troop )
{
    return msg << troop.id << troop.count;
}

StreamBase & operator>>( StreamBase & msg, Troop & troop )
{
    return msg >> troop.id >> troop.count;
}
