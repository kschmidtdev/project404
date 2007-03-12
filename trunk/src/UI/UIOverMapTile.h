/**
 * A single city/location on the Over Map
 *
 * #include "UIOverMapTile.h"
 *
 * A single city/location on the Over Map
 *
 * @see UIOverMap
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 4, 2007, Initial Creation
 */

#ifndef UIOverMapTile_h
#define UIOverMapTile_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UIElement.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIOverMapTile : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIOverMapTile(void);

     /**
     * Position constructor.
	 */
    UIOverMapTile(int x, int y);

    /**
     * Position and image file name constructor
     */
    UIOverMapTile(int x, int y, string fileName);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UIOverMapTile(const UIOverMapTile& from);

    /**
     * Destructor.
	 */
    ~UIOverMapTile(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIOverMapTile&                     operator=(UIOverMapTile& from);

// OPERATIONS


    /**
     * Signifies to tile that the "level" the tile represents has been defeated
     * and progression to the next Level is allowed
     */
    void LevelDefeated(void);





// ACCESS (writing)

   /**
     * Setting what city is to the "Left" Direction
     */
    void SetLeft(UIOverMapTile* l);

    /**
     * Setting what city is to the "Right" Direction
     */
    void SetRight(UIOverMapTile* r);

    /**
     * Setting what city is to the "Up" Direction
     */
    void SetUp(UIOverMapTile* u);

    /**
     * Setting what city is to the "Down" Direction
     */
    void SetDown(UIOverMapTile* d);

    /**
     * Sets what the next and previos locations (tiles) are
     */
    void SetNextPrev(UIOverMapTile* next, UIOverMapTile* prev);


// INQUIRY (reading)

    /**
     * Retrieving what city is to the "Left" Direction
     */
    UIOverMapTile* GetLeft(void);

    /**
     * Retrieving what city is to the "Right" Direction
     */
    UIOverMapTile* GetRight(void);

    /**
     * Retrieving what city is to the "Up" Direction
     */
    UIOverMapTile* GetUp(void);

    /**
     * Retrieving what city is to the "Down" Direction
     */
    UIOverMapTile* GetDown(void);

    /**
     * Retrieving map offset (Tile's position relative to the map)
     */
    Point GetMapOffset(void);

protected:
// PROTECTED VARIABLES

    // Progression pointers
    UIOverMapTile* mNextTile;
    UIOverMapTile* mPrevTile;

    // Directional pointers (used for higher abstraction)
    UIOverMapTile* mLeftTile;
    UIOverMapTile* mRightTile;
    UIOverMapTile* mUpTile;
    UIOverMapTile* mDownTile;

    Point mMapOffset;

    //string mBattleImageFilename;
    //string mConqueredImageFilename;
    //SDL_Surface* mBattleImage;
    //SDL_Surface* mConqueredImage;

// PROTECTED OPERATIONS

    /**
     * Enables movement (left,up) to the next level
     */
    void EnableNextMove(void);

    /**
     * Enables movement (right, down) to the previous level
     */
    void EnablePrevMove(void);

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIOverMapTile_h_
