/**
 * The Layout that shows the credits in the game.
 *
 * #include "UICreditsLayout.h"
 *
 * The Layout that shows the credits in the game.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007 | Initial Creation
 */

#ifndef UICreditsLayout_h
#define UICreditsLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UICreditsLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UICreditsLayout(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UICreditsLayout(const UICreditsLayout& from);

    /**
     * Destructor.
	 */
    ~UICreditsLayout(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UICreditsLayout&                     operator=(UICreditsLayout& from);

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

#endif  // _UICreditsLayout_h_
