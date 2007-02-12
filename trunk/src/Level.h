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
 * Mike Malyuk, February 11 2007 | Added includes for vector, Point.h
 *                                 Added proper constructor, changed TakeTurn to void return
 *                                 Changed OnSelect to accept Point not Point*, Added ReturnState
 *                                 Added GetMovementHelp and changed GetMovement to use recursion
 *                                 Added GetTurn, Changed variables with <Point*> to <Point>
 */

#ifndef Level_h
#define Level_h

// SYSTEM INCLUDES
//
#include <vector>
// PROJECT INCLUDES
//
#include "Map.h"
#include "Character.h"
#include "Point.h"

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
     * Constructor.
	 */
    Level(vector<Character*> party, vector<Character*> badguys, vector<Point> start, Map* map);

    /**
     * Destructor.
	 */
    ~Level(void);

// OPERATIONS
    /**
     * End current users turn, move to AI, or AI moves to User
	 */
    void TakeTurn();

    /**
     * From SetCursorBattle, controls STATE by checking position for players.
     * If character exists returns pointer, if not, returns null
	 */
    Character* OnSelect(Point p);
// ACCESS (writing)
// INQUIRY (reading)

    int ReturnState();
    /**
     * Get movement possibilities
	 */
    void GetMovement();

    void GetMovementHelp(int move, int x, int y);

    /**
     * Get Map for Renderer
     */
    Map* GetMap();

    /**
     * Get Turn (true ours, false theirs)
     */
    bool GetTurn();

    bool GetLoseCondition();

    bool GetWinCondition();
protected:
// PROTECTED VARIABLES
    charState mState;
    vector<Character*> mEnemies;
    vector<Character*> mParty;
    vector<Point> mMoveArea;
    vector<Point> mAttackArea;
    vector<Point> mStart;
    Character* mCurChar;
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
