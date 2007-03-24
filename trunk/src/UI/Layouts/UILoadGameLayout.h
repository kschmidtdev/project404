/**
 * Layout that prompts user to select saved game.
 *
 * #include "UILoadGameLayout.h"
 *
 * Layout that prompts user to select saved game.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007, Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Andrew Osborne, March 23 2007 | Added proper UI functionality (Menu with options)
 */

#ifndef UILoadGameLayout_h
#define UILoadGameLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class UIMenu;

class UILoadGameLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UILoadGameLayout(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UILoadGameLayout(const UILoadGameLayout& from);

    /**
     * Destructor.
	 */
    ~UILoadGameLayout(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UILoadGameLayout&                     operator=(UILoadGameLayout& from);

// OPERATIONS

    /**
     * Listens for Key Press from User
    */
    //virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

    /**
     * Overwrites OnLoad operation
     */
    virtual void OnLoad(void);

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES

    UIMenu* mMenu;


private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UILoadGameLayout_h_
