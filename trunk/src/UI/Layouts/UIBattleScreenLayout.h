/**
 * UILayout class for main battle screen
 *
 * #include "UIBattleScreenLayout.h"
 *
 * The screen we need to run the game
 *
 * @see GameEngine
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Crude Creation
 */

#ifndef UIBattleScreenLayout_h
#define UIBattleScreenLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIBattleScreenLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIBattleScreenLayout(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    UIBattleScreenLayout(const UIBattleScreenLayout& from);

    /**
     * Destructor.
	 */
    ~UIBattleScreenLayout(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    UIBattleScreenLayout&                     operator=(UIBattleScreenLayout& from);

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

#endif  // _UIBattleScreenLayout_h_
