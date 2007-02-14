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
 * Andrew Osborne, February 11 2007, Initial Creation
 * Karl Schmidt, February 13 2007, Added typedefs instead of lots of vector<Type>
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
#include <GameEngine/GameEngine.h>
#include <UIImage.h>
#include <GameEngine/Character.h>
#include <GameEngine/Level.h>


// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

typedef vector<UITile*> UITileVec;
typedef UITileVec::iterator UITileItr;
typedef vector<UIImage*> UIImageVec;
typedef UIImageVec::iterator UIImageItr;
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
    virtual void addCharacter(Character *c);

    /**
     * Removes character element from grid.
	 */
    virtual void removeCharacter(Point p);

    /**
     * Used for displaying the range of motion for a particular player
     */
    void AddMoveableRange( vector<Point> moveableSpots);

    /**
     *  Clears the points which make up
     */
    void ClearMoveableRange( void );

    /**
     * Used for displaying an attacking range of motion
     */
    void AddAttackRange( vector<Point> attackableSpots);

    /**
     * Clear the attack range that appears
     */
    void ClearAttackRange( void );

    /**
     * Generic Function used for adding movement/attack range
     */
    void AddRange( vector<Point> pointRange, vector<UIImage*> elementRange);

    /**
     * Clear the attack range that appears
     */
    void ClearRange( vector<UIImage*> elements );


// ACCESS (writing)

    /**
     * Allows BattleLayout to pass handle for level communication
     */
    void setLevel(Level* l);

// INQUIRY (reading)

    /**
     * Check to see if point is 'valid' point on grid
     */
    bool validPoint(Point p);

    /**
     *
     */
    bool hasCharacter(Point p);

protected:
// PROTECTED VARIABLES
    UITileVec mTiles;
    int mTileWidth;
    int mTileHeight;
    int mNumRows;
    int mNumColumns;

    // Parent
    //UIBattleScreenLayout *mBattleLayout;

    // Cursor values
    Point mCursorPos;
    Point mMaxCursorPos;
    Point mCursorStart;
    Point mTileStart;
    int mTileOffset;  // This variable assumes square tiles
    int mTotalTileOffset;
    UIElement* mCursor;

    // Gameplay-Character Movement/Attack variables

    // Gameplay elements
    vector<Point> mMoveRange;
    vector<Point> mAttackRange;
    Character* mCurCharacter;

    // Display/UI elements
    UIImageVec mImageMoveRange;
    UIImageVec mImageAttackRange;



    // Regular Communication
    Level* mLevel;
    //GameEngine* mGameEngine;

// PROTECTED METHODS
    int findIndex(int x, int y);
    int findIndex(Point p);
    void confirmFunction(Point p);
    SDL_Surface* getClassSurface(Character* c);
    Point gridToAbsoluteCoordinates(Point p);

    /**
     * Refines point vector to ensure all points are valid and don't contain points that have other characters
     * on them
     *
     *@return refined point vector
     */
    vector<Point> RefineMoveRange( vector<Point> moveRange);


private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIGrid_h_
