/**
 * UILayout - an instance of a single screen (e.g Main Menu Screen )
 *
 * #include "UILayout.h"
 *
 * UILayout class represetns a single screen that a user would see (e.g. Main menu screen, battle screen).  It also
 * contains a list (vector) of all the elements on the screen for reference purposes.
 *
 * @see UIManager
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 7, 2007 | Initial class creation
 * Karl Schmidt, February 10 2007 | Changed inheritance from UIElemnt to SDLRenderable
 * Andrew Osborne, February 10 2007 | Fleshed out documentation
 * Andrew Osborne, February 11 2007 | Made UILayout inherit EventListener, added processEvent method
 */

#ifndef UILayout_h
#define UILayout_h

// SYSTEM INCLUDES
//
#include <vector>

using namespace std;

// PROJECT INCLUDES
//
#include <UIElement.h>
#include <EventListener.h>
#include <InputManager.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UILayout : public EventListener
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UILayout(void);

    /**
     * Destructor.
	 */
    virtual ~UILayout(void);

// OPERATORS
// OPERATIONS
    /**
     * Method renders menu on screen
	 *
	 * @param the destination (SDL_Surface) where the menu will go.
	 *
	 */
    //virtual void RenderSelf(SDL_Surface* destination);

    /**
     * Method that is run upon layout being loaded as current layout (called from UIManager)
	 *
	 */
    virtual void onLoad(void);

    /**
     * Method that is run upon layout NO LONGER being used as current layout (called from UIManager)
	 *
	 */
    virtual void onClose(void);

    /**
     * Listens for Key Press from User
    */
    virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    vector<UIElement*> elements;
    EventListener* defaultEventListener;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UILayout_h_