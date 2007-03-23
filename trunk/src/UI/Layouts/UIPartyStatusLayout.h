/**
 * Layout for adjusting party information (formation, equipment)
 *
 * #include "UIPartyStatusLayout.h"
 *
 * Layout for adjusting party information (formation, equipment)
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007, Initial Creation (empty)
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 */

#ifndef UIPartyStatusLayout_h
#define UIPartyStatusLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIPartyStatusLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIPartyStatusLayout(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UIPartyStatusLayout(const UIPartyStatusLayout& from);

    /**
     * Destructor.
	 */
    ~UIPartyStatusLayout(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIPartyStatusLayout&                     operator=(UIPartyStatusLayout& from);

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

#endif  // _UIPartyStatusLayout_h_
