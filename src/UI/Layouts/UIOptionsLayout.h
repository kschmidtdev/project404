/**
 * The Layout that allows user to change options in the game.
 *
 * #include "UIOptionsLayout.h"
 *
 * The Layout that allows user to change options in the game.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew osborne, March 18 2007, Initial Design
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Andrew Osborne, March 24 2007, Proper UI Implementation
 */

#ifndef UIOptionsLayout_h
#define UIOptionsLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIOptionsLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIOptionsLayout(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UIOptionsLayout(const UIOptionsLayout& from);

    /**
     * Destructor.
	 */
    ~UIOptionsLayout(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIOptionsLayout&                     operator=(UIOptionsLayout& from);

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

#endif  // _UIOptionsLayout_h_
