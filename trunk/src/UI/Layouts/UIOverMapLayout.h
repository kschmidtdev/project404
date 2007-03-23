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
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 */

#ifndef UIOverMapLayout_h
#define UIOverMapLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UIOverMap.h>
#include <UI/UILayout.h>
#include <UI/UIMenu.h>
#include <UI/UIScrollText.h>

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
     * Destructor.
	 */
    ~UIOverMapLayout(void);

// OPERATORS
// OPERATIONS

    /**
     * Get Method. Returns the pointer of mScrollBox
     */
    UIScrollText* GetUIScrollBox() { return mScrollBox; }

    /**
     * Get Method.
     */
    UIOverMap* GetOverMap() { return mOverMap; }

    void SetScrollBoxEnabled( bool bswitch ) { mScrollBoxEnabled = bswitch; }

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
