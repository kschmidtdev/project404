/**
 * The UI Element which represents the World Map
 *
 * #include "UIOverMap.h"
 *
 * The UI Element which represents the World Map.
 *
 * @see UIOverMapLayout
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 4, 2007, Initial Creation
 */

#ifndef UIOverMap_h
#define UIOverMap_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UIElement.h>
#include <UIOverMapTile.h>
#include <UIOverMapCursor.h>
#include <EventListener.h>
#include <vector>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

typedef vector<UIOverMapTile> MapTileVec;
typedef MapTileVec::iterator MapTileItr;


class UIOverMap : public UIElement, public EventListener
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIOverMap(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UIOverMap(const UIOverMap& from);

    /**
     * Destructor.
	 */
    ~UIOverMap(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIOverMap&                     operator=(UIOverMap& from);

// OPERATIONS

    virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

    /**
     * Overrides RenderSelf to render the tiles.
	 */
    virtual void RenderSelf(SDL_Surface* destination);

// ACCESS (writing)

    /**
     * Method to set the position of element relative to it's parent
     *
     * @param boolean value true=visible, false=invisible
     *
     */
    virtual void SetPos( const Point & nPos );

// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    MapTileVec mMapTiles;
    UIOverMapCursor mCursor;
    UIOverMapTile *mDefaultTile;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIOverMap_h_
