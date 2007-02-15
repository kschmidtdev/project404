/**
 * File: GameEngine.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 12 2007 | Initial creation of file
 * Karl Schmidt, February 15 2007 | Added BattleInit placeholder func( loads one level )
 */
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
    if( _instance )
    {
        delete _instance;
        _instance = NULL;
    }
}

void GameEngine::BattleInit(vector<Character*> partyMem, Cities place)
{
	// THIS IS IN NO WAY COMPLETE
    if( mCurLvl )
    {
        // Already made a level
        return;
    }
    mCurLvl = new Level(0);

}

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

GameEngine::GameEngine()
: mCurLvl( NULL ),
  mCurTile( NULL ),
  mCurChar( NULL )
{
}// GameEngine


/////////////////////////////// PRIVATE    ///////////////////////////////////
