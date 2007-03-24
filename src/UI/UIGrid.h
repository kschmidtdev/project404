/**
 * A class representation of the battle grid on the main screen
 *
 * #include "UIGrid.h"
 *
 * A class representation of the battle grid on the main screen
 *
 * @see UIBattleScreenLayout
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11, 2007  | Initial Creation
 * Karl Schmidt,   February 13, 2007  | Added typedefs instead of lots of vector<Type>
 * Mike Malyuk,    February 14, 2007  | Was confused by typedefs, regardless moved everything away from pointers.
 * Karl Schmidt,   February 14, 2007  | Updated function capitalization, block style, typedefs, refs
 * Mike Malyuk,    February 14, 2007  | Added function AddExhaustedCharacter
 * Mike Malyuk,    February 15, 2007  | Added MaxXY to get the edges of map
 * Mike Malyuk,    March 4, 2007      | Removed variables mMoveRange, mAttackRange, unused
 * Mike Malyuk,    March 9, 2007      | Added variable for Map
 * Mike Malyuk,    March 10, 2007     | Added info for Map, changed add moveable range to use map
 * Andrew Osborne, March 11, 2007     | Added mCharWindow & added CursorUpdate method
 * Mike Malyuk,    March 14, 2007     | Fixed range method to get latest.
 * Mike Malyuk,    March 14, 2007     | Removed defunct methods
 * Karl Schmidt,   March 20 2007      | Major adding of consts and reference usage, rearranging includes
 * Karl Schmidt,   March 21 2007      | Added support for health change indication UI
 * Karl Schmidt,   March 22 2007      | Correcting include orders and paths
 * Andrew Osborne, March 23 2007      | Added comments for protected methods
 * Karl Schmidt,   March 23 2007      | Added mini-map implementation, enum instead of string for character tile type identification,
                                        removed some old code that wasn't used anymore
 */

#ifndef UIGrid_h
#define UIGrid_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UITile.h>
#include <EventListener.h>
#include <UI/UIImage.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

class UIElement;
class UICharWindow;
class Level;
class Character;
class Map;

typedef std::vector<UITile> UITileVec;
typedef UITileVec::iterator UITileItr;
typedef std::vector<UIImage> UIImageVec;
typedef UIImageVec::iterator UIImageItr;
typedef std::vector<UIImage*> UIImagePtrVec;
typedef UIImagePtrVec::iterator UIImagePtrItr;
typedef std::vector<Point> PointVec;

class UIGrid : public UIElement, public EventListener
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIGrid(void);

    /**
     * Destructor.
	 */
    ~UIGrid(void);

// OPERATORS

// OPERATIONS
    /**
     * Overrides RenderSelf to render the tiles.
	 */
    virtual void RenderSelf(SDL_Surface* destination);

    /**
     * Overrides the ProcessEvent so that it can control the cursor.
	 */
	virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

	/**
     * Adds character element to grid.
	 */
    virtual void AddEnemyCharacter(Character *c);

	/**
     * Adds character element to grid.
	 */
    virtual void AddPartyCharacter(Character *c);

	/**
     * Adds character element to grid.
	 */
    virtual void AddExhaustedCharacter(Character *c);

    /**
     * Removes character element from grid.
	 */
    virtual void RemoveCharacter( const Point & p );

    /**
     * Used for displaying the range of motion for a particular player
     */
    void AddMoveableRange( const std::vector<Character*> & enemies, const std::vector<Character*> & enemies, Character* you);

    /**
     *  Clears the points which make up
     */
    void ClearMoveableRange( void );

    /**
     * Used for displaying an attacking range of motion
     */
    void AddAttackRange( const PointVec & attackableSpots );

    /**
     * Clear the attack range that appears
     */
    void ClearAttackRange( void );

    /**
     * Clear the character on the grid
     */
    void ClearCharacters( void );

    /**
     * Updates position of cursor and Character Window
     */
    void UpdateCursor(void);

    void Initialize();
// ACCESS (writing)

    /**
     * Allows BattleLayout to pass handle for level communication
     */
    void SetLevel( Level* level );

    /**
     * Allows BattleLayout to pass handle for Character Window Communication
     */
    void SetCharWindow( UICharWindow* charWindow);

// INQUIRY (reading)

    /**
     * Check to see if point is 'valid' point on grid
     */
    const bool ValidPoint( const Point & p ) const;

    /**
     *
     */
    const bool HasCharacter( const Point & p );

    Point MaxXY(){ return Point(mNumColumns, mNumRows);}

protected:
// PROTECTED VARIABLES

    // Tile Info
    UITileVec mTiles;
    PointVec mMovePoints;
    int mTileWidth;
    int mTileHeight;
    int mNumRows;
    int mNumColumns;


    // Cursor values
    Point mCursorPos;
    Point mMaxCursorPos;
    Point mCursorStart;
    Point mTileStart;
    int mTileOffset;  // This variable assumes square tiles
    int mTotalTileOffset;
    UIElement* mCursor;

    // Other elements on the screen under Grid's control (or influence)

    // Character Window
    UICharWindow* mCharWindow;

    //Map
    Map* mMap;

    // Gameplay-Character Movement/Attack variables

    // Gameplay elements
    Character* mCurCharacter;

    // Regular Communication
    Level* mLevel;

    UITileVec mMiniMap;

    enum CHARACTER_SURFACE_GROUP
    {
        G_PARTY = 0,
        G_ENEMY,
        G_EXHAUSTED
    };

// PROTECTED METHODS

// TODO: These need correct commenting

    /**
     * Returns index of mTiles that is represented by input.
     *
     *@param (x,y) coordinate on grid
     *
     *@return respective index of mTiles element
     */
    const int FindIndex( const int x, const int y ) const;

    /**
     * Returns index of mTiles that is represented by input.
     *
     *@param Point coordinate on grid (p = (x,y))
     *
     *@return respective index of mTiles element
     */
    const int FindIndex( const Point & p ) const;

    public:

    /**
     * Function executed when user presses CONFIRM
     */
    void ConfirmFunction( const Point & p );

    protected:

    /**
     * Function finds the SDL_Surface for a specified character (e.g. Archer) & status (e.g. Exhausted)
     *
     * @param Character pointer, string that represtes status (i.e. Party, Enemy or Exhausted)
     *
     * @return pointer to desired SDL_Surface
     */
    SDL_Surface* GetClassSurface( Character* c, const CHARACTER_SURFACE_GROUP group, const bool isMiniMap = false );

    /**
     * Returns (absolute) point on screen, given relative point on grid
     */
    const Point GridToAbsoluteCoordinates( const Point & p ) const;

	/**
	 * Draw the text about the player and the target participating in an attack/heal
	 */
    void DrawHealthIndicationers( Character* attacker, Character* defender );

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIGrid_h_
