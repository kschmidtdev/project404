/**
 * The base class for a button element on screen
 *
 * #include "UIButton.h"
 *
 * The only addition feature of a button element will be a constructor that allows for the passed string to be seen
 * on the button
 *
 * @see UIMenu
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 */

#ifndef UIButton_h
#define UIButton_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UIElement.h>
#include <UIText.h>
#include <FuncObj.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIButton : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIButton(void);

    /**
     * Default constructor.
	 */
	UIButton(const string text);

    /**
     * Destructor.
	 */
    ~UIButton(void);

// OPERATORS
    /**
     * Override Renderself to allow for text to be written as well.
	 */
    virtual void RenderSelf(SDL_Surface* destination);


// OPERATIONS
// ACCESS (writing)

    /**
     * Set position of button - automatically moves and centers text with it.
	 */
    virtual void setPos(Point nPos);

    /**
     * specifies operation to be performed upon pressing the button.
	 */
    void setOperation(FuncObj* nOperation);


// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    UIText mText;
    FuncObj* mOperation;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIButton_h_
