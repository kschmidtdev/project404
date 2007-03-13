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
 * Karl Schmidt, March 12, 2007	  | Fixed a memory leak (deleting levels on Shutdown now)
 */

#include <util.h>

#include "GameEngine.h"                                // class implemented


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

    for( LevelPtrItr i = mLevels.begin(); i != mLevels.end(); ++i )
    {
        delete *i;
    }
    mLevels.clear();

    if( _instance )
    {
        delete _instance;
        _instance = NULL;
    }
}

void GameEngine::BattleInit(vector<Character*> partyMem, Cities place, Map map)
{
	// THIS IS IN NO WAY COMPLETE
    if( mCurLvl )
    {
        // Already made a level
        return;
    }
    mCurLvl = new Level(0);
    mAI = new AIControl(mCurLvl, map);

}

void GameEngine::BattleOver()
{
    if( mCurLvl )
    {
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
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

GameEngine::GameEngine()
: mAI( NULL ),
  mCurLvl( NULL ),
  mCurTile( NULL ),
  mCurChar( NULL )
{
    mLevels.push_back( new Level() );
    mLevels.push_back( new Level() );
    mLevels.push_back( new Level() );
    mLevels.push_back( new Level() );
    mLevels.push_back( new Level() );

}// GameEngine


/////////////////////////////// PRIVATE    ///////////////////////////////////
