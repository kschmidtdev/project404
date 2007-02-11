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

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIGrid : public UIElement
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
    virtual void RenderSelf(SDL_Surface* destination);

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    vector<UITile*> mTiles;
    int mTileWidth;
    int mTileHeight;
    int mNumColumns;
    int mNumRows;

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
