/**
 * UIMenu class (mostly abstract) used to define a menu element on screen
 *
 * #include "UIMenu.h"
 *
 * UIMenu contains a vector of buttons, a cursor and a background box.  It also can handle eventListening
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Creation
 * Karl Schmidt, February 10 2007 | Changed some include directory formats
 * Andrew Osborne, February 10 2007 | Filled out documentation
 */

#ifndef UIMenu_h
#define UIMenu_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <SDL.h>
#include <Renderer/SDLRenderable.h>
#include <UIElement.h>
#include <EventListener.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIMenu : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIMenu(void);

    /**
     * Destructor.
	 */
    ~UIMenu(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    UIMenu&                     operator=(UIMenu& from);

// OPERATIONS
    /**
     * Method renders menu on screen
	 *
	 * @param the destination (SDL_Surface) where the menu will go.
	 *
	 */
    virtual void RenderSelf(SDL_Surface *destination);




// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    UIElement* cursor;
    int curCursorPosition;
    vector<UIElement*> buttons;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIMenu_h_
