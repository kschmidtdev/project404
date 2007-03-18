/**
 * The Layout that allows user to choose profile option.
 *
 * #include "UIProfileMenuLayout.h"
 *
 * The Layout that allows user to choose whether they wish to create a new profile, load an existing profile, or quit.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007, Initial Creation
 */

#ifndef UIProfileMenuLayout_h
#define UIProfileMenuLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIProfileMenuLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIProfileMenuLayout(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UIProfileMenuLayout(const UIProfileMenuLayout& from);

    /**
     * Destructor.
	 */
    ~UIProfileMenuLayout(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIProfileMenuLayout&                     operator=(UIProfileMenuLayout& from);

// OPERATIONS

    /**
     * Listens for Key Press from User
    */
    //virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

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

#endif  // _UIProfileMenuLayout_h_
