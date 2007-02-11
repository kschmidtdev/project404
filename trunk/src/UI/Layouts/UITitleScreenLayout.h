/**
 * A one line description of the class.
 *
 * #include "UITitleScreenLayout.h"
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
