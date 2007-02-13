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
 * Mike Malyuk, February 12 2007 | Added getters for UI.
 * Andrew Osborne, February 12 2007 | Added mDefaultConstructor to proplerly delete items after creation
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

    /**
     * Check if all party is dead
     */
    bool GetLoseCondition();

    /**
     * Check if all enemies are dead
     */
    bool GetWinCondition();

    /**
     * Return all characters in level (for UI)
     */
    vector<Character*> GetEveryone();

    /**
     * Return all points in movement area (state = 1)
     */
    vector<Point> GetMoveArea();

    /**
     * Return all points in attack area (state = 2)
     */
    vector<Point> GetAttackArea();

    /**
     * Checks if party is exhausted, if true, it will automatically switch turns
     */
    bool AllExhaustedParty();
protected:
// PROTECTED VARIABLES
    charState mState;
    vector<Character*> mParty;
    vector<Character*> mEnemies;
    vector<Point> mMoveArea;
    vector<Point> mAttackArea;
    vector<Point> mStart;
    Character* mCurChar;
    Map* mThisMap;
    bool mMyTurn;

    // For testing/version1
    bool mDefaultConstructor;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Level_h_
