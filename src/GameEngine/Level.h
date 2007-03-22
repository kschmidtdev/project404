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
 * Karl Schmidt, March 14, 2007   | Added a hack to force the current turn to the players to solve a bug
 * Mike Malyuk, March 14, 2007    | Added Map to Level variables, added GetMap method.
 * Karl Schmidt, March 20 2007    | Major adding of consts and reference usage, rearranging includes
 * Karl Schmidt, March 21 2007    | Added storage of the last damage and healing values from attacking/defending and healing
 */

#ifndef Level_h
#define Level_h

// SYSTEM INCLUDES
//
#include <vector>
// PROJECT INCLUDES
//
#include "Point.h"
#include <GameEngine/Map.h>
#include <GameEngine/Character.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

typedef std::vector<Character*> CharacterPtrVec;
typedef CharacterPtrVec::iterator CharacterPtrItr;
typedef CharacterPtrVec::const_iterator CharacterPtrConstItr;

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
    Level( const CharacterPtrVec & party, const CharacterPtrVec & badguys, const PointVec & start);

    /**
    * Constructor.
    */
    Level( const int battleNumber); // Contructor loads characters from Database.

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
    Character* OnSelect( const Point & p );

    /**
     * From SetCursorBattle, controls STATE by checking position for players.
     * If character exists returns pointer, if not, returns null
	 */
    Character* OnAISelect( const Point & p );

// ACCESS (writing)
    void SetState( const charState state ){mState = state;}
// INQUIRY (reading)

    int ReturnState();

    /**
     * Get Turn (true ours, false theirs)
     */
    const bool GetTurn() const;

    /**
     * Check if all party is dead
     */
    const bool GetLoseCondition() const;

    /**
     * Check if all enemies are dead
     */
    const bool GetWinCondition() const;

    /**
     * Return all characters in level (for UI)
     */
    const CharacterPtrVec GetEveryone() const;

    /**
     * Return all points in attack area (state = 2)
     */
    const PointVec& GetAttackArea() const;

    /**
     * Checks if party is exhausted, if true, it will automatically switch turns
     */
    const bool AllExhaustedParty();

    /**
     * Checks if party is exhausted, if true, it will automatically switch turns
     */
    const bool AllExhaustedEnemies();

    /**
     * Checks if point has person, return person if it does;
     */
    Character* PointHasPerson( const Point & p ) const;

    /**
     * Checks if point has person, return person if it does;
     */
    Character* AIPointHasPerson( const Point & p ) const;


    /**
     * Return Enemies
     */
    const CharacterPtrVec& GetEnemies() const;

    /**
     * Return Party
     */
    const CharacterPtrVec& GetParty() const;

    /**
     *
     */
     Map* GetMap() { return &mMap; }

    /**
     * Return Party
     */
     Character* GetCurCharacter() const { return mCurChar; }

     void SetPlayerTurn() { mMyTurn = true; };

	/**
	 * Simple getters for the following values
	 */
     const int GetLastDamageInflicted() const { return mLastDmgInflicted; };
     const int GetLastDamageTaken() const { return mLastDmgTaken; };
     const int GetLastHealed() const { return mLastHealed; };

protected:
// PROTECTED VARIABLES
    charState mState;
    CharacterPtrVec mParty;
    CharacterPtrVec mEnemies;
    PointVec mAttackArea;
    PointVec mStart;
    Character* mCurChar;
    Map mMap;
    bool mMyTurn;

    int mLastDmgInflicted;
    int mLastDmgTaken;
    int mLastHealed;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Level_h_
