/**
 * Layout that represents a Market in a City.
 *
 * #include "UIMarketLayout.h"
 *
 * Layout that represents a Market in a City.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007, Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 * Andrew Osborne, March 25 2007 | Implemented proper functionality
 * Andrew Osborne, March 29 2007 | Added Item window and party money
 */

#ifndef UIMarketLayout_h
#define UIMarketLayout_h

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
class Item;
class UIItemWindow;

class UIMarketLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIMarketLayout(void);

    /**
     * Destructor.
	 */
    ~UIMarketLayout(void);

// OPERATORS
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
    UIText* mMoney;
    UIItemWindow* mItemWindow;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIMarketLayout_h_
