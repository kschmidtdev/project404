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
 * Andrew Osborne, March 25 2007 | Implemented proper UI functionality
 * Andrew Osborne, March 29 2007 | Added OnClose method and mPartyList attribute
 */

#ifndef UIPartyStatusLayout_h
#define UIPartyStatusLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UILayout.h>
#include <UI/UICharWindow.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class UIMenu;
//class UICharWindow;

typedef std::vector<UICharWindow*> UICharWindowPtrVec;
typedef UICharWindowPtrVec::iterator UICharWindowPtrItr;


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
    //virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

    /**
     * Overwrites OnLoad operation
     */
    virtual void OnLoad(void);

    /**
     * Overwrites OnLoad operation
     */
    virtual void OnClose(void);

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES

    UIMenu *mMenu;
    UIMenu *mArmorMenu;
    UIMenu *mWeaponMenu;
    UIMenu *mMasterPartyMenu;
    UICharWindowPtrVec mPartyWindow;
    std::vector<Character*>* mPartyList;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIPartyStatusLayout_h_
