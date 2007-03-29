/**
 * File: GameEngine.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 12 2007 | Initial creation of file
 * Karl Schmidt, February 15 2007 | Added BattleInit placeholder func( loads one level )
 * Mike Malyuk,  February 15 2007 | Added AI
 * Mike Malyuk,  March 10, 2007   | Replaced point with map for BattleInit
 * Andrew Osborne, March 11 2007  | Added GetLevels (and created instantiations of the levels in the game)
 * Karl Schmidt, March 12, 2007	  | Fixed a memory leak (deleting levels on Shutdown now)
 * Andrew Osborne, March 13 2007  | Added GetCities, and changed BattleInit
 * Mike Malyuk,    March 14 2007  | Set AIController with proper map
 * Karl Schmidt,   March 14 2007  | Level is now loaded depending on city ID
 * Seung Woo Han, March 15 2007   | Save Game at the end of each battle.
 * Karl Schmidt,   March 15 2007  | Removed saving the game at the end of each battle
 * Karl Schmidt, March 15 2007    | Support for city defeating status to update db
 * Karl Schmidt, March 20 2007    | Major adding of consts and reference usage, rearranging includes
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Mike Malyuk,  March 26 2007    | Calling new AI constructor
 * Karl Schmidt, March 27 2007    | Added support for loading/saving difficulty from/to DBEngine
 * Mike Malyuk,  March 27 2007    | Added cash! Everyone loves it!
 * Mike Malyuk,  March 28 2007    | Except when turns buggers it up! Fixed small bug with 0 turns
 */

#include "GameEngine.h"                                // class implemented

#include <util.h>

#include <Database/DBEngine.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

GameEngine* GameEngine::_instance = 0;

GameEngine* GameEngine::GetInstance()
{
    if( !_instance )
    {
        _instance = new GameEngine();
    }
    return _instance;
}

GameEngine::~GameEngine()
{
}// ~GameEngine

void GameEngine::Shutdown()
{
    BattleOver();

    for( CityPtrItr i = mCities.begin(); i != mCities.end(); ++i )
    {
        delete *i;
    }
    mCities.clear();

    if( _instance )
    {
        delete _instance;
        _instance = NULL;
    }
}


// NOTES ======================

// THIS IS IN NO WAY COMPLETE

	/* Things that need to be done:
	 - There needs to be more than one map/level in the database to load.
	 - There should be "SOME" operation that uses the arguements
	 - Level must take an arguement to select a stage... or take map as arguement.. or
        ...something
     -
	*/

	/*

	THINGS THAT NEED TO CHANGE ELSEWHERE:

	Level:
         - Loads party members from GameEngine, not DBEngine
         - takes the argument of

    Grid:
         - Needs to take map as constructing argument
	*/



//void GameEngine::BattleInit(vector<Character*> partyMem, City *c, Map* map)
void GameEngine::BattleInit(City *c)
{
    tacAssert( c != NULL );

    if( c == NULL )
    {
        return;
    }
    // Set current city
    mCurCity = c;

    // Initialize level (if not already done)
    if( mCurLvl )
    {
        // Already made a level
        return;
    }

    LogInfo( "Loading Level #" + toString(c->GetID()) );
    mCurLvl = new Level( c->GetID() );

    // Initialize AI
    mAI = new AIControl(mCurLvl, *(mCurLvl->GetMap()), GetAIDifficulty() );

}

void GameEngine::BattleOver()
{
    if( mCurLvl )
    {
        mCash = mCash + (mCurCity->GetID()*10000)/mCurLvl->GetNumTurns();
        std::cout << "Current Cash: " << mCash << std::endl;
        delete mCurLvl;
        mCurLvl = NULL;
    }
    if( mAI )
    {
        delete mAI;
        mAI = NULL;
    }
}

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================

void GameEngine::SetAI(Level* level)
{
    mAI->SetLevel(level);
}

void GameEngine::SetCash(int moolah)
{
    mCash = moolah;
}

void GameEngine::CityDefeated(void)
{
    if (mCurCity)
    {
        DBEngine::GetInstance()->SetBattleCompleted( mCurCity->GetID(), true );
        mCurCity->SetDefeated(true);
    }
}

void GameEngine::UpdateCitiesFromDB()
{
    for( unsigned int i = 0; i < mCities.size(); ++i )
    {
        mCities[i]->SetDefeated( DBEngine::GetInstance()->GetBattleCompleted( i+1 ) );
    }
}

void GameEngine::SetAIDifficulty( const int AIDifficulty )
{
    DBEngine::GetInstance()->SetCurrentDifficulty( AIDifficulty );
}

const int GameEngine::GetAIDifficulty() const
{
    return DBEngine::GetInstance()->GetCurrentDifficulty();
};

const int GameEngine::GetCash() const
{
    return mCash;
};

//============================= INQUIRY    ===================================


/////////////////////////////// PROTECTED  ///////////////////////////////////

GameEngine::GameEngine()
: mCurLvl( NULL ),
  mAI( NULL ),
  mCurCity( NULL ),
  mCurTile( NULL ),
  mCurChar( NULL ),
  mCurStage( 0 ),
  mCash( 0 )
{

    // Need to create different cities....
    mCities.push_back( new City( Point(20, 400), (string) "victory.png") );
    mCities.push_back( new City( Point(130, 350), (string) "victory.png") );
    mCities.push_back( new City( Point(180, 270), (string) "victory.png") );
    mCities.push_back( new City( Point(270, 170), (string) "victory.png") );
    mCities.push_back( new City( Point(390, 70), (string) "victory.png") );

    /*mLevels.push_back( new Level() );
    mLevels.push_back( new Level() );
    mLevels.push_back( new Level() );
    mLevels.push_back( new Level() );
    mLevels.push_back( new Level() );*/

}// GameEngine


/////////////////////////////// PRIVATE    ///////////////////////////////////
