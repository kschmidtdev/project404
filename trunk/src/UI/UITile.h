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
 * Andrew Osborne, February 11 2007 | Initial Creation
 * Karl Schmidt,   February 14 2007 | Updated function capitalization, block style, typedefs, refs
 * Mike Malyuk,    March 8 2007     | Added UITile constructor taking Tile in preparation for use of map
 * Andrew osborne, March 15 2007    | Made a change in preperation for a dynamically changing Grid.
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 */

#ifndef UITile_h
#define UITile_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UIElement.h>
#include <GameEngine/Tile.h>
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

    UITile( const Tile & tile );

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

    /**
     * Adds a Range indicator surface to tile
     */
    void AddRange(SDL_Surface* nSur);

// INQUIRY (reading)

    /**
     * Returns boolean value whether character exists on tile or not
     */
    bool HasCharacter(void);

    /**
     * Removes Range indicator surface from tile
     */
    void RemoveRange(void);



protected:
// PROTECTED VARIABLES
    SDL_Surface* mCharacterImage;
    SDL_Surface* mRangeImage;
    // Animation variable


private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UITile_h_
