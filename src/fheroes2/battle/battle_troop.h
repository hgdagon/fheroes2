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

#ifndef H2BATTLE_TROOP_H
#define H2BATTLE_TROOP_H

#include <utility>
#include <vector>

#include "battle.h"
#include "battle_animation.h"
#include "battle_arena.h"
#include "battle_army.h"
#include "bitmodes.h"
#include "game_delays.h"

class Spell;
class HeroBase;

namespace Battle
{
    struct ModeDuration : public std::pair<uint32_t, uint32_t>
    {
        ModeDuration();
        ModeDuration( uint32_t, uint32_t );

        bool isMode( uint32_t ) const;
        bool isZeroDuration( void ) const;
        void DecreaseDuration( void );
    };

    struct ModesAffected : public std::vector<ModeDuration>
    {
        ModesAffected();

        uint32_t GetMode( uint32_t ) const;
        void AddMode( uint32_t, uint32_t );
        void RemoveMode( uint32_t );
        void DecreaseDuration( void );

        uint32_t FindZeroDuration( void ) const;
    };

    StreamBase & operator<<( StreamBase &, const ModesAffected & );
    StreamBase & operator>>( StreamBase &, ModesAffected & );

    enum
    {
        CONTOUR_MAIN = 0,
        CONTOUR_REFLECT = 0x01
    };

    // battle troop stats
    class Unit : public ArmyTroop, public BitModes, public Control
    {
    public:
        Unit( const Troop &, int32_t pos, bool reflect );
        ~Unit();

        virtual bool isModes( uint32_t ) const override;
        virtual bool isBattle() const override;
        virtual std::string GetShotString() const override;
        virtual std::string GetSpeedString() const override;
        virtual uint32_t GetHitPointsLeft() const override;
        virtual uint32_t GetAffectedDuration( uint32_t ) const override;
        virtual uint32_t GetSpeed() const override;
        virtual int GetMorale() const override;

        Unit * GetMirror();
        void SetMirror( Unit * );
        void SetRandomMorale( void );
        void SetRandomLuck( void );
        void NewTurn( void );

        virtual bool isValid() const override;
        bool isArchers( void ) const;
        bool isFlying( void ) const;
        bool isTwiceAttack( void ) const;

        bool AllowResponse( void ) const;
        bool isHandFighting( void ) const;
        bool isReflect( void ) const;
        bool isHaveDamage( void ) const;
        bool isMagicResist( const Spell &, uint32_t ) const;
        bool OutOfWalls( void ) const;
        bool canReach( int index ) const;
        bool canReach( const Unit & unit ) const;

        std::string String( bool more = false ) const;

        uint32_t GetUID( void ) const;
        bool isUID( uint32_t ) const;

        int32_t GetHeadIndex( void ) const;
        int32_t GetTailIndex( void ) const;
        const Position & GetPosition( void ) const;
        void SetPosition( int32_t );
        void SetPosition( const Position & );
        void SetReflection( bool );

        virtual uint32_t GetAttack() const override;
        virtual uint32_t GetDefense() const override;
        int GetArmyColor( void ) const;
        virtual int GetColor() const override;
        int GetCurrentColor() const; // the unit can be under spell what changes its affiliation
        int GetCurrentControl() const;
        uint32_t GetMoveRange() const;
        uint32_t GetSpeed( bool skip_standing_check ) const;
        virtual int GetControl() const override;
        uint32_t GetDamage( const Unit & ) const;
        int32_t GetScoreQuality( const Unit & ) const;
        uint32_t GetDead( void ) const;
        uint32_t GetHitPoints( void ) const;
        uint32_t GetShots( void ) const;
        uint32_t ApplyDamage( Unit &, uint32_t );
        uint32_t ApplyDamage( uint32_t );
        uint32_t CalculateRetaliationDamage( uint32_t damageTaken ) const;
        uint32_t CalculateMinDamage( const Unit & ) const;
        uint32_t CalculateMaxDamage( const Unit & ) const;
        uint32_t CalculateDamageUnit( const Unit & enemy, double dmg ) const;
        bool ApplySpell( const Spell &, const HeroBase * hero, TargetInfo & );
        bool AllowApplySpell( const Spell &, const HeroBase * hero, std::string * msg = NULL, bool forceApplyToAlly = false ) const;
        bool isUnderSpellEffect( const Spell & spell ) const;
        void PostAttackAction( Unit & );
        void ResetBlind( void );
        void SetBlindAnswer( bool value );
        void SpellModesAction( const Spell &, uint32_t, const HeroBase * );
        void SpellApplyDamage( const Spell &, uint32_t, const HeroBase *, TargetInfo & );
        void SpellRestoreAction( const Spell &, uint32_t, const HeroBase * );
        uint32_t Resurrect( uint32_t, bool, bool );

        bool SwitchAnimation( int rule, bool reverse = false );
        bool SwitchAnimation( const std::vector<int> & animationList, bool reverse = false );
        const AnimationState & GetFrameState( void ) const;
        AnimationSequence GetFrameState( int ) const;
        void SetDeathAnim();
        void IncreaseAnimFrame( bool loop = false );
        bool isStartAnimFrame( void ) const;
        bool isFinishAnimFrame( void ) const;
        int GetFrame( void ) const;
        int GetFrameStart( void ) const;
        int GetFrameCount( void ) const;
        uint32_t GetCustomAlpha() const;
        void SetCustomAlpha( uint32_t alpha );

        Point GetStartMissileOffset( size_t ) const;

        int M82Attk( void ) const;
        int M82Kill( void ) const;
        int M82Move( void ) const;
        int M82Wnce( void ) const;
        int M82Expl( void ) const;

        int ICNFile( void ) const;
        int ICNMiss( void ) const;

        Point GetBackPoint( void ) const;
        Point GetCenterPoint() const;
        Rect GetRectPosition( void ) const;

        uint32_t HowManyCanKill( const Unit & ) const;
        uint32_t HowManyWillKilled( uint32_t ) const;

        void SetResponse( void );
        void UpdateDirection( void );
        bool UpdateDirection( const Rect & );
        void PostKilledAction( void );

        uint32_t GetMagicResist( const Spell &, uint32_t ) const;
        int GetSpellMagic( bool force = false ) const;

        const HeroBase * GetCommander( void ) const;

        static bool isHandFighting( const Unit &, const Unit & );

        int GetAnimationState() const;
        bool isIdling() const;
        bool checkIdleDelay();

        // Find a better way to expose it without a million getters/setters
        AnimationState animation;

    private:
        friend StreamBase & operator<<( StreamBase &, const Unit & );
        friend StreamBase & operator>>( StreamBase &, Unit & );

        uint32_t uid;
        uint32_t hp;
        uint32_t count0;
        uint32_t dead;
        uint32_t shots;
        uint32_t disruptingray;
        bool reflect;

        Position position;
        ModesAffected affected;
        Unit * mirror;
        RandomizedDelay idleTimer;

        bool blindanswer;
        uint32_t customAlphaMask;
    };

    StreamBase & operator<<( StreamBase &, const Unit & );
    StreamBase & operator>>( StreamBase &, Unit & );
}

#endif
