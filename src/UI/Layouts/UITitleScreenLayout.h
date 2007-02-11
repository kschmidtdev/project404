/**
 * UILayout sub-class for the main battle screen
 *
 * #include "UITitleScreenLayout.h"
 *
 * UILayout sub-class for the main battle screen
 *
 * @see UILayout
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Creation
 * Andrew Osborne, February 10 2007 | Documentation
 */

#ifndef UITitleScreenLayout_h
#define UITitleScreenLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UITitleScreenLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UITitleScreenLayout(void);

    /**
     * Destructor.
	 */
    ~UITitleScreenLayout(void);

// OPERATORS
// OPERATIONS
    /**
     * Method to Draw the element on the screen
     *
     * @param Desitination surface
     *
     */
    virtual void RenderSelf( SDL_Surface* destination );

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UITitleScreenLayout_h_
