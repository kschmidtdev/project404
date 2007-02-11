/**
 * A one line description of the class.
 *
 * #include "UIMenu.h"
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

#ifndef UIMenu_h
#define UIMenu_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <SDL.h>
#include <SDLRenderable.h>
#include <UIElement.h>

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
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    UIMenu(const UIMenu& from);

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
virtual void RenderSelf(SDL_Surface *destination);
virtual void inputFunction(void);

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
