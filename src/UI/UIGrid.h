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
 */

#ifndef UIGrid_h
#define UIGrid_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UIElement.h>
#include <UITile.h>
#include <EventListener.h>
#include <UIImage.h>
#include <UICharWindow.h>
#include <GameEngine/Character.h>
#include <GameEngine/Level.h>


// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

typedef vector<UITile> UITileVec;
typedef UITileVec::iterator UITileItr;
typedef vector<UIImage> UIImageVec;
typedef UIImageVec::iterator UIImageItr;
typedef vector<UIImage*> UIImagePtrVec;
typedef UIImagePtrVec::iterator UIImagePtrItr;
typedef vector<Point> PointVec;
typedef PointVec::iterator PointItr;

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
    void AddMoveableRange( vector<Character*> enemies, vector<Character*> enemies, Character* you);

    /**
     *  Clears the points which make up
     */
    void ClearMoveableRange( void );

    /**
     * Used for displaying an attacking range of motion
     */
    void AddAttackRange( PointVec attackableSpots);

    /**
     * Clear the attack range that appears
     */
    void ClearAttackRange( void );

    /**
     * Clear the attack range that appears
     */
    void ClearRange( const UIImagePtrVec & elements );

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
    bool ValidPoint( const Point & p );

    /**
     *
     */
    bool HasCharacter( const Point & p );

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

    // Display/UI elements
    UIImageVec mImageMoveRange;
    UIImageVec mImageAttackRange;



    // Regular Communication
    Level* mLevel;

// PROTECTED METHODS

// TODO: These need correct commenting
    int FindIndex( const int x, const int y );
    int FindIndex( const Point & p );
    public:
    void ConfirmFunction( const Point & p );
    protected:
    SDL_Surface* GetClassSurface( Character* c, const string group );
    Point GridToAbsoluteCoordinates( const Point & p );


private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIGrid_h_
