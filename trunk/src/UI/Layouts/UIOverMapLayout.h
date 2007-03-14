/**
 * Layout class for Over Map
 *
 * #include "UIOverMapLayout.h"
 *
 * Layout class for Over Map
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 4, 2007, Initial Creation
 * Andrew Osborne, March 12, 2007, Added OnLoad to allow for OverMap updating.
 */

#ifndef UIOverMapLayout_h
#define UIOverMapLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UIOverMap.h>
#include <UILayout.h>
#include <UIMenu.h>
#include <UIScrollText.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIOverMapLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIOverMapLayout(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UIOverMapLayout(const UIOverMapLayout& from);

    /**
     * Destructor.
	 */
    ~UIOverMapLayout(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIOverMapLayout&                     operator=(UIOverMapLayout& from);

// OPERATIONS

    /**
     * Override OnLoad to allow for map updates
     */
    virtual void OnLoad( void );

    /**
     * Listens for Key Press from User
    */
    virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    UIOverMap* mOverMap;
    UIMenu* mMenu;
    UIScrollText* mScrollBox;
    bool mScrollBoxEnabled;




private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIOverMapLayout_h_
