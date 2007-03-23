/**
 * Layout that prompts user to enter tutorial or not.
 *
 * #include "UITutorialMenuLayout.h"
 *
 * Layout that prompts user to enter tutorial or not.
 *
 * @see UITutorialLayout
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007, Initial Creation
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 */

#ifndef UITutorialMenuLayout_h
#define UITutorialMenuLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include<UI/UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UITutorialMenuLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UITutorialMenuLayout(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UITutorialMenuLayout(const UITutorialMenuLayout& from);

    /**
     * Destructor.
	 */
    ~UITutorialMenuLayout(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UITutorialMenuLayout&                     operator=(UITutorialMenuLayout& from);

// OPERATIONS


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

#endif  // _UITutorialMenuLayout_h_
