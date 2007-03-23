/**
 * The layout class that represents the "Congratulations" screen
 *
 * #include "UIWinLayout.h"
 *
 * The layout class that represents the "Congratulations" screen that you see when you win a battle.
 *
 * @see UILayout, UIBattleScreenLayout
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 15 2007, Initial Creation
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 */

#ifndef UIWinLayout_h
#define UIWinLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIWinLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIWinLayout(void);

    /**
     * Destructor.
	 */
    ~UIWinLayout(void);

// OPERATORS

    /**
     * Method to Process input from user
     *
     * @param inputManager event
     *
     */
    virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

// OPERATIONS
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

#endif  // _UIWinLayout_h_
