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


class UIMarketLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIMarketLayout(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UIMarketLayout(const UIMarketLayout& from);

    /**
     * Destructor.
	 */
    ~UIMarketLayout(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIMarketLayout&                     operator=(UIMarketLayout& from);

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

#endif  // _UIMarketLayout_h_
