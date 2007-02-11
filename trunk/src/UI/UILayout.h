/**
 * UILayout class declaration
 *
 * #include "UILayout.h"
 *
 * UILayout class represetns a single screen that a user would see (e.g. Main menu screen, battle screen)
 *
 * @see UIElement, UIManager
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 7, 2007, Initial class creation
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

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UILayout : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UILayout(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    UILayout(const UILayout& from);

    /**
     * Destructor.
	 */
    virtual ~UILayout(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    UILayout&                     operator=(UILayout& from);

// OPERATIONS
virtual void RenderSelf(SDL_Surface* destination);
virtual void onLoad(void);
virtual void onClose(void);

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
vector<UIElement*> elements;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UILayout_h_
