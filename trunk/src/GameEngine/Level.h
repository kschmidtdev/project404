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
 * Mike Malyuk, February 14, 2007 | Added function PointHasPerson to return enemy state,
 * Mike Malyuk, February 15, 2007 | Added AI mirror functions
 * Mike Malyuk, February 15, 2007 | Added GetCurCharacter
 * Mike Malyuk, March 10, 2007    | Removed mMap and move methods, now that map does this
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
    ATTACK,
    AIFREE,
    AIMOVE,
    AIATTACK
};
// LIFECYCLE

    /**
     * Default constructor.
	 */
    Level(void);

    /**
     * Constructor.
	 */
    Level(vector<Character*> party, vector<Character*> badguys, vector<Point> start);

    /**
    * Constructor.
    */
    Level(int); // Contructor loads characters from Database.

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

    /**
     * From SetCursorBattle, controls STATE by checking position for players.
     * If character exists returns pointer, if not, returns null
	 */
    Character* OnAISelect(Point p);

// ACCESS (writing)
    void SetState(charState state){mState = state;}
// INQUIRY (reading)

    int ReturnState();

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
     * Return all points in attack area (state = 2)
     */
    vector<Point> GetAttackArea();

    /**
     * Checks if party is exhausted, if true, it will automatically switch turns
     */
    bool AllExhaustedParty();

    /**
     * Checks if party is exhausted, if true, it will automatically switch turns
     */
    bool AllExhaustedEnemies();

    /**
     * Checks if point has person, return person if it does;
     */
    Character* PointHasPerson(Point p);

    /**
     * Checks if point has person, return person if it does;
     */
    Character* AIPointHasPerson(Point p);


    /**
     * Return Enemies
     */
    vector<Character*> GetEnemies();

    /**
     * Return Party
     */
     vector<Character*> GetParty();

    /**
     * Return Party
     */
     Character* GetCurCharacter(){return mCurChar;}

protected:
// PROTECTED VARIABLES
    charState mState;
    vector<Character*> mParty;
    vector<Character*> mEnemies;
    vector<Point> mAttackArea;
    vector<Point> mStart;
    Character* mCurChar;
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
