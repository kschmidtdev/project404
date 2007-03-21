/**
 * Layout used to create a new profile
 *
 * #include "UINewProfileLayout.h"
 *
 * Layout used to create a new profile
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007, Initial Creation
 */

#ifndef UINewProfileLayout_h
#define UINewProfileLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UINewProfileLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UINewProfileLayout(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UINewProfileLayout(const UINewProfileLayout& from);

    /**
     * Destructor.
	 */
    ~UINewProfileLayout(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UINewProfileLayout&                     operator=(UINewProfileLayout& from);

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

#endif  // _UINewProfileLayout_h_
