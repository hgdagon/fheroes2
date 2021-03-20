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
#ifndef H2WORLD_H
#define H2WORLD_H

#include <vector>

#include "artifact_ultimate.h"
#include "castle_heroes.h"
#include "gamedefs.h"
#include "kingdom.h"
#include "maps.h"
#include "maps_objects.h"
#include "maps_tiles.h"
#include "week.h"
#include "world_pathfinding.h"
#include "world_regions.h"
#include <string>

class Heroes;
class Castle;
class Kingdom;
class Recruits;
class Radar;
class MapObjectSimple;
class ActionSimple;

struct ListActions : public std::list<ActionSimple *>
{
    ~ListActions();
    void clear( void );
};

struct MapObjects : public std::map<uint32_t, MapObjectSimple *>
{
    ~MapObjects();
    void clear( void );
    void add( MapObjectSimple * );
    std::list<MapObjectSimple *> get( const Point & );
    MapObjectSimple * get( uint32_t uid );
    void remove( const Point & );
    void remove( uint32_t uid );
};

using MapActions = std::map<int32_t, ListActions>;

struct CapturedObject
{
    ObjectColor objcol;
    Troop guardians;
    int split;

    CapturedObject()
        : split( 1 )
    {}

    int GetSplit( void ) const
    {
        return split;
    }
    int GetObject( void ) const
    {
        return objcol.first;
    }
    int GetColor( void ) const
    {
        return objcol.second;
    }
    Troop & GetTroop( void )
    {
        return guardians;
    }

    void Set( int obj, int col )
    {
        objcol = ObjectColor( obj, col );
    }
    void SetColor( int col )
    {
        objcol.second = col;
    }
    void SetSplit( int spl )
    {
        split = spl;
    }

    bool GuardiansProtected( void ) const
    {
        return guardians.isValid();
    }
};

struct CapturedObjects : std::map<int32_t, CapturedObject>
{
    void Set( int32_t, int, int );
    void SetColor( int32_t, int );
    void ClearFog( int );
    void ResetColor( int );

    CapturedObject & Get( int32_t );
    Funds TributeCapturedObject( int col, int obj );

    uint32_t GetCount( int, int ) const;
    uint32_t GetCountMines( int, int ) const;
    int GetColor( int32_t ) const;
};

struct EventDate
{
    EventDate()
        : first( 0 )
        , subsequent( 0 )
        , colors( 0 )
        , computer( false )
    {}

    void LoadFromMP2( StreamBuf );

    bool isAllow( int color, uint32_t date ) const;
    bool isDeprecated( uint32_t date ) const;

    Funds resource;
    uint32_t first;
    uint32_t subsequent;
    int colors;
    bool computer;
    std::string message;
};

StreamBase & operator<<( StreamBase &, const EventDate & );
StreamBase & operator>>( StreamBase &, EventDate & );

using Rumors = std::list<std::string>;
using EventsDate = std::list<EventDate>;
using MapsTiles = std::vector<Maps::Tiles>;

class World : protected Size
{
public:
    ~World()
    {
        Reset();
    }

    bool LoadMapMP2( const std::string & );
    bool LoadMapMAP( const std::string & );

    void NewMaps( uint32_t, uint32_t );

    static World & Get( void );

    int32_t w( void ) const
    {
        return Size::w;
    }

    int32_t h( void ) const
    {
        return Size::h;
    }

    const Maps::Tiles & GetTiles( uint32_t, uint32_t ) const;
    Maps::Tiles & GetTiles( uint32_t, uint32_t );
    const Maps::Tiles & GetTiles( const int32_t tileId ) const;
    Maps::Tiles & GetTiles( const int32_t tileId );

    void InitKingdoms( void );

    Kingdom & GetKingdom( int color );
    const Kingdom & GetKingdom( int color ) const;

    const Castle * GetCastle( const Point & ) const;
    Castle * GetCastle( const Point & );

    const Heroes * GetHeroes( int /* hero id */ ) const;
    Heroes * GetHeroes( int /* hero id */ );

    const Heroes * GetHeroes( const Point & ) const;
    Heroes * GetHeroes( const Point & );

    Heroes * FromJailHeroes( int32_t );
    Heroes * GetFreemanHeroes( int race = 0 ) const;

    const Heroes * GetHeroesCondWins( void ) const;
    const Heroes * GetHeroesCondLoss( void ) const;

    CastleHeroes GetHeroes( const Castle & ) const;

    const UltimateArtifact & GetUltimateArtifact( void ) const;
    bool DiggingForUltimateArtifact( const Point & );

    // overall number of cells of the world map: width * height
    size_t getSize() const;
    int GetDay( void ) const;
    int GetWeek( void ) const;
    int GetMonth( void ) const;
    uint32_t CountDay( void ) const;
    uint32_t CountWeek( void ) const;
    bool BeginWeek( void ) const;
    bool BeginMonth( void ) const;
    bool LastDay( void ) const;
    bool LastWeek( void ) const;
    const Week & GetWeekType( void ) const;
    std::string DateString( void ) const;

    void NewDay( void );
    void NewWeek( void );
    void NewMonth( void );

    const std::string & GetRumors( void );

    int32_t NextTeleport( int32_t ) const;
    MapsIndexes GetTeleportEndPoints( int32_t ) const;

    int32_t NextWhirlpool( int32_t ) const;
    MapsIndexes GetWhirlpoolEndPoints( int32_t ) const;

    void CaptureObject( int32_t, int col );
    uint32_t CountCapturedObject( int obj, int col ) const;
    uint32_t CountCapturedMines( int type, int col ) const;
    uint32_t CountObeliskOnMaps( void );
    int ColorCapturedObject( int32_t ) const;
    void ResetCapturedObjects( int );
    CapturedObject & GetCapturedObject( int32_t );
    ListActions * GetListActions( int32_t );

    void ActionForMagellanMaps( int color );
    void ClearFog( int color );
    void UpdateRecruits( Recruits & ) const;

    int CheckKingdomWins( const Kingdom & ) const;
    bool KingdomIsWins( const Kingdom &, int wins ) const;
    int CheckKingdomLoss( const Kingdom & ) const;
    bool KingdomIsLoss( const Kingdom &, int loss ) const;

    void AddEventDate( const EventDate & );
    EventsDate GetEventsDate( int color ) const;

    MapEvent * GetMapEvent( const Point & );
    MapObjectSimple * GetMapObject( uint32_t uid );
    void RemoveMapObject( const MapObjectSimple * );
    const MapRegion & getRegion( size_t id ) const;
    size_t getRegionCount() const;

    bool isTileBlocked( int toTile, bool fromWater ) const;
    bool isValidPath( int index, int direction, const int heroColor ) const;
    uint32_t getDistance( const Heroes & hero, int targetIndex );
    std::list<Route::Step> getPath( const Heroes & hero, int targetIndex );
    void resetPathfinder();

    void ComputeStaticAnalysis();
    static uint32_t GetUniq( void );

    uint32_t GetMapSeed() const;

private:
    World()
        : Size( 0, 0 )
        , _rumor( nullptr )
    {}

    void Defaults( void );
    void Reset( void );
    void MonthOfMonstersAction( const Monster & );
    void ProcessNewMap();
    void PostLoad();
    void pickRumor();

private:
    friend class Radar;
    friend StreamBase & operator<<( StreamBase &, const World & );
    friend StreamBase & operator>>( StreamBase &, World & );
#ifdef WITH_XML
    friend TiXmlElement & operator>>( TiXmlElement &, World & );
#endif

    MapsTiles vec_tiles;
    AllHeroes vec_heroes;
    AllCastles vec_castles;
    Kingdoms vec_kingdoms;
    Rumors vec_rumors;
    const std::string * _rumor;
    EventsDate vec_eventsday;

    // index, object, color
    CapturedObjects map_captureobj;

    UltimateArtifact ultimate_artifact;

    uint32_t day = 0;
    uint32_t week = 0;
    uint32_t month = 0;

    Week week_current;
    Week week_next;

    int heroes_cond_wins = Heroes::UNKNOWN;
    int heroes_cond_loss = Heroes::UNKNOWN;

    MapActions map_actions;
    MapObjects map_objects;

    // This data isn't serialized
    Maps::Indexes _allTeleporters;
    Maps::Indexes _whirlpoolTiles;
    std::vector<MapRegion> _regions;
    PlayerWorldPathfinder _pathfinder;

    uint32_t _seed;
};

StreamBase & operator<<( StreamBase &, const CapturedObject & );
StreamBase & operator>>( StreamBase &, CapturedObject & );
StreamBase & operator<<( StreamBase &, const World & );
StreamBase & operator>>( StreamBase &, World & );

StreamBase & operator<<( StreamBase &, const ListActions & );
StreamBase & operator>>( StreamBase &, ListActions & );

StreamBase & operator<<( StreamBase &, const MapObjects & );
StreamBase & operator>>( StreamBase &, MapObjects & );

extern World & world;

#endif
