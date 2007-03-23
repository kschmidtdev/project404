/**
 * Layout for loading an existing profile
 *
 * #include "UILoadProfileLayout.h"
 *
 * Layout for loading an existing profile.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew osborne, March 18 2007, Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 */

#ifndef UILoadProfileLayout_h
#define UILoadProfileLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UILoadProfileLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UILoadProfileLayout(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UILoadProfileLayout(const UILoadProfileLayout& from);

    /**
     * Destructor.
	 */
    ~UILoadProfileLayout(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UILoadProfileLayout&                     operator=(UILoadProfileLayout& from);

// OPERATIONS

    /**
     * Listens for Key Press from User
    */
    virtual void ProcessEvent( const InputManager::INPUTKEYS evt );


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

#endif  // _UILoadProfileLayout_h_
