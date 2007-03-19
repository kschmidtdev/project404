/**
 * Layout to Save Game.
 *
 * #include "UISaveGameLayout.h"
 *
 * Layout to Save Game.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007, Initial Creation
 */

#ifndef UISaveGameLayout_h
#define UISaveGameLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UISaveGameLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UISaveGameLayout(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UISaveGameLayout(const UISaveGameLayout& from);

    /**
     * Destructor.
	 */
    ~UISaveGameLayout(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UISaveGameLayout&                     operator=(UISaveGameLayout& from);

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

#endif  // _UISaveGameLayout_h_
