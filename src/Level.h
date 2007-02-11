/**
 * Controls the aspects of a single level.
 *
 * #include "Level.h"
 *
 * Controls units and play within a battle scenario. All GameEngine calls will be passed directly to
 * Level when it is in a battle mode.
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 9, 1007 | Initial design
 */

#ifndef Level_h
#define Level_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include "Map.h"
#include "Character.h"

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class Level
{
public:
//ENUM
enum charState
{
    FREE = 0,
    MOVE,
    ATTACK
};
// LIFECYCLE

    /**
     * Default constructor.
	 */
    Level(void);

    /**
     * Destructor.
	 */
    ~Level(void);

// OPERATIONS
    /**
     * End current users turn, move to AI, or AI moves to User
	 */
    bool TakeTurn();

    /**
     * From SetCursorBattle, controls STATE by checking position for players.
     * If character exists returns pointer, if not, returns null
	 */
    Character* OnSelect(Point* p);
// ACCESS (writing)
// INQUIRY (reading)

    /**
     * Tell user if character is selected.
	 */
    bool CharSelected();

    /**
     * Get movement possibilities
	 */
    vector<Point*> GetMovement();

    /**
     * Get action possibilities
	 */
	 vector<Point*> GetAction();

    /**
     * Get Map for Renderer
     */
     Map* GetMap();

protected:
// PROTECTED VARIABLES
    charState mState;
    vector<Character*> mEnemies;
    vector<Character*> mPlayer;
    vector<Point*> mMoveArea;
    vector<Point*> mAttackArea;
    Map* mThisMap;
    bool mMyTurn;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Level_h_
