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
 * Andrew Osborne, March 12, 2007, Added Update Map
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Andrew Osborne, March 24 2007 | converted from EventListener to UIEventListener
 */

#ifndef UIOverMap_h
#define UIOverMap_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UIElement.h>
#include <UI/UIText.h>
#include <UI/UIOverMapTile.h>
#include <UI/UIOverMapCursor.h>
#include <UIEventListener.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

typedef std::vector<UIOverMapTile> MapTileVec;
typedef MapTileVec::iterator MapTileItr;


class UIOverMap : public UIElement, public UIEventListener
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIOverMap(void);

    /**
     * Destructor.
	 */
    ~UIOverMap(void);

// OPERATORS
// OPERATIONS

    /**
     * Listens for Key Press from User
    */
    virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

    /**
     * Overrides RenderSelf to render the tiles.
	 */
    virtual void RenderSelf(SDL_Surface* destination);

    /**
     * Ensures proper level/map progression
     */
     void UpdateMap(void);

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


    // Level Progression info
    int mCurrentLevelProgression;


private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIOverMap_h_
