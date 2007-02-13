/**
 * The UI class that represents a single tile on a grid (Battle grid)
 *
 * #include "UITile.h"
 *
 * The UI class that represents a single tile on a grid (Battle grid)
 *
 * @see UIGrid
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007, Initial Creation
 */

#ifndef UITile_h
#define UITile_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UIElement.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UITile : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UITile(void);


    /**
     * Destructor.
	 */
    ~UITile(void);

// OPERATORS


// OPERATIONS

    /**
     * Overrides RenderSelf to render the the proper tile (character or terrain).
	 */
    virtual void RenderSelf(SDL_Surface* destination);

    /**
     * Adds character icon to tile (metaphorically - on top of terrain)
     */
    void addCharacter(SDL_Surface *nSur);

    /**
     * Remove character icon from tile
     */
    void removeCharacter(void);



// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    SDL_Surface* mCharacterImage;
    // Animation variable


private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UITile_h_
