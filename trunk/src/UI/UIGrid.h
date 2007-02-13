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
//#include <UIBattleScreenLayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


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

// ACCESS (writing)

    /**
     * Used by parent to allow access to certain operations
     */
    //void setParent(UIBattleScreenLayout* parent);

// INQUIRY (reading)

    /**
     * Check to see if point is 'valid' point on grid
     */
    bool validPoint(Point p);

protected:
// PROTECTED VARIABLES
    vector<UITile*> mTiles;
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
    vector<UIImage> mImageMoveRange;
    vector<UIImage> mImageAttackRange;



    // Regular Communication
    //GameEngine* mGameEngine;

// PROTECTED METHODS
    int findIndex(int x, int y);
    void confirmFunction(Point p);
    SDL_Surface* getClassSurface(Character* c);

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIGrid_h_
