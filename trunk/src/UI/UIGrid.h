/**
 * A one line description of the class.
 *
 * #include "UIGrid.h"
 *
 * A longer description.
 *
 * @see something
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date (Month Day Year), What was done
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
//#include <GameEngine.h>
#include <UIImage.h>

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

// ACCESS (writing)

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

// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    vector<UITile*> mTiles;
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

    // Range storage variables
    vector<UIImage> mMoveRange;
    vector<UIImage> mAttackRange;

    // Regular Communication
    //GameEngine* mGameEngine;

// PROTECTED METHODS
    int findIndex(int x, int y);
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIGrid_h_
