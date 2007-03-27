/**
 * Layout that represents Armory in City.
 *
 * #include "UIArmoryLayout.h"
 *
 * Layout that represents Armory in City.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007, Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Andrew Osborne, March 25 2007 | Implemented proper functionality
 */

#ifndef UIArmoryLayout_h
#define UIArmoryLayout_h

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
class UIText;



class UIArmoryLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIArmoryLayout(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UIArmoryLayout(const UIArmoryLayout& from);

    /**
     * Destructor.
	 */
    ~UIArmoryLayout(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIArmoryLayout&                     operator=(UIArmoryLayout& from);

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
    UIText* mFeedback;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIArmoryLayout_h_
