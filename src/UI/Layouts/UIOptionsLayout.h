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
 * Karl Schmidt, March 27 2007   | Added support for AI difficulty setting/loading
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
class UIMenu;

class UIOptionsLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIOptionsLayout(void);

    /**
     * Destructor.
	 */
    ~UIOptionsLayout(void);

// OPERATORS
// OPERATIONS

    /**
     * Listens for Key Press from User
    */
    //virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

    /**
     * Method that is run upon layout being loaded as current layout (called from UIManager)
	 */
    void OnLoad();

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
private:
// PRIVATE VARIABLES

    UIMenu* mDifficultyMenu;
    UIMenu* mSoundLevelMenu;
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIOptionsLayout_h_
