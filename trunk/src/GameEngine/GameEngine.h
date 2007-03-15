/**
 * GameEngine class defines the parties, is responsible for initialzing parties and game objects.
 *
 * #include "GameEngine.h"
 *
 * GameEngine is the heart of the project for game instances. Will allow the game
 * to run battles, instantiate items and characters from the DB. Also will allow saving
 * of gamestate to DB.
 *
 * Project 404 2007
 *
 * Authors:
 *
 * Mike Malyuk, February 8, 2007, | Initial design
 * Karl Schmidt, February 12 2007 | Fixed includes, made it a singleton, fixed some compilation errors
 * Karl Schmidt, February 15 2007 | Changed the name of one enum, corrected a naming convention, added a GetLevel() function
 * Mike Malyuk, February 15 2007  | Added AI
 * Karl Schmidt, February 15 2007 | Fixed an odd header include path
 * Mike Malyuk, March 10, 2007    | Removed point, implemented map
 * Andrew Osborne, March 13 2007  | Changed BattleInit, and initiated the city member variables
 */

#ifndef GameEngine_h
#define GameEngine_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
// TODO: Include City.h when it exists
//#include <GameEngine/City.h>
#include <GameEngine/Level.h>
#include <GameEngine/Character.h>
#include <GameEngine/Item.h>
#include <GameEngine/City.h>
#include <AI/AIControl.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


typedef vector<Level*> LevelPtrVec;
typedef LevelPtrVec::iterator LevelPtrItr;
typedef vector<City*> CityPtrVec;
typedef CityPtrVec::iterator CityPtrItr;

class GameEngine
{
public:

//ENUMS
enum Cities
    {
        CITYA = 0,
        CITYB,
        CITYC,
        CITY_COUNT
    };
// LIFECYCLE

    /**
    * Returns an instance of the GameEngine
    */
    static GameEngine* GetInstance();

    /**
     * Destructor.
	 */
    ~GameEngine(void);

    /**
    * Destroys the singleton instance, cleans other things up
    */
    void Shutdown();

// OPERATIONS

    /**
     * Pass information to a level instance
	 */
    void BattleInit(City *c);

    /**
     * Unload the current level
    */
    void BattleOver();

    /**
     * Check city for a market
	 */
    bool IsMarket();

    /**
     * Check city for a armory
	 */
    bool IsArmory();

    /**
     * Move the player to a city
	 */
    void MoveCity(Cities place);

    /**
     * Calculate in battle movement
	 */
    vector<Point*> CalcMove(Character* unit);

    /**
     * Tell main loop if we are in battle (true) or not (false)
	 */
    bool Update();

// ACCESS (writing)
    /**
     * Set cursor to a City, update current city
	 */
    void SetCursorOver(Cities place);

    /**
     * Set cursor to a City, update current city
	 */
    void SetCursorBattle( const int x, const int y );

    /**
     * Sets the current city as being defeated
     */
    void CityDefeated(void);


    void SetAI(Level* level);
// INQUIRY (reading)
    /**
     * Return items in a Market
	 */
    vector<Item*> ReturnMarket();

    /**
     * Return items in a Armory
	 */
    vector<Item*> ReturnArmory();

    /**
     * Returns a pointer to the current battle in progress (if there is one)
	 */
    Level* GetLevel() { return mCurLvl; };

    /**
     * Returns a vector of all the cities in the game
	 */
    CityPtrVec* GetCities() { return &mCities; };

    AIControl* GetAI() {return mAI;}

protected:
// PROTECTED METHODS
    /**
     * Default constructor.
	 */
    GameEngine(void);

// PROTECTED VARIABLES

    // Character/Party information
    vector<Character*> mCharacters;
    vector<Character*> mParty;
    vector<Item*> mItems;

    // Level information
    vector<Level*> mLevels;
    Level* mCurLvl;

    // AI
    AIControl* mAI;

    // City information
    vector<City*> mCities;
    City* mCurCity;

    // ????
    Point* mCurTile;
    Character* mCurChar;

    static GameEngine* _instance;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _GameEngine_h_
