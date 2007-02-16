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
 * Karl Schmidt, February 14 2007 | Updated function capitalization, block style, typedefs, refs
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
     * Remove character icon from tile
     */
    void RemoveCharacter(void);



// ACCESS (writing)

    /**
     * Adds character icon to tile (metaphorically - on top of terrain)
     */
    void AddCharacter(SDL_Surface *nSur);
// INQUIRY (reading)

    /**
     * Returns boolean value whether character exists on tile or not
     */
    bool HasCharacter(void);



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
