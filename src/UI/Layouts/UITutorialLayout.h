/**
 * Layout that gives user a tutorial of how to use the game.
 *
 * #include "UITutorialLayout.h"
 *
 * Layout that gives user a tutorial of how to use the game.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007, Initial Creation
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 */

#ifndef UITutorialLayout_h
#define UITutorialLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UITutorialLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UITutorialLayout(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UITutorialLayout(const UITutorialLayout& from);

    /**
     * Destructor.
	 */
    ~UITutorialLayout(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UITutorialLayout&                     operator=(UITutorialLayout& from);

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

#endif  // _UITutorialLayout_h_
