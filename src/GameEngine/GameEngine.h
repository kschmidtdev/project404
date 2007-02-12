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
 * Mike Malyuk, February 8, 2007, | Initial design
 */

#ifndef GameEngine_h
#define GameEngine_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include "City.h"
#include "Level.h"
#include "Character.h"
#include "Item.h"


// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class GameEngine
{
public:

//ENUMS
enum Cities
    {
        CITYA = 0,
        CITYB,
        CITYC,
        ATTR_COUNT
    };
// LIFECYCLE

    /**
     * Default constructor.
	 */
    GameEngine(void);

    /**
     * Destructor.
	 */
    ~GameEngine(void);

// OPERATIONS
//  Character* GetInstChar(string templatename);
//  Item* GetInstItem(string templatename);
//  void DBWrite();
//  void Initialize();

    /**
     * Pass information to a level instance
	 */
    void BattleInit(vector<Character*> partymem, Cities place);

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
    void SetCursorBattle(x, y);

// INQUIRY (reading)
    /**
     * Return items in a Market
	 */
    vector<Item*> ReturnMarket();

    /**
     * Return items in a Armory
	 */
    vector<Item*> ReturnArmory();

protected:
// PROTECTED VARIABLES
    vector<Character*> mCharacters;
    vector<Character*> mParty;
    vector<Level*> mLevels;
    vector<City*> mCities;
    vector<Item*> mItems;
    Level* mCurLvl;
    City* mCurCity;
    Point* mCurTile;
    Character* mCurChar;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _GameEngine_h_
