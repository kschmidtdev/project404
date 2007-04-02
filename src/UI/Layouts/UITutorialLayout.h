/**
 * Layout that gives user a tutorial of how to use the game.
 *
 * #include "UITutorialLayout.h"
 *
 * Layout that gives user a tutorial of how to use the game.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 18 2007, Initial Creation
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Andrew Osborne, March 23 2007, Proper Implementation of functionality
 * Karl Schmidt, April 2 2007    | Added support for final tutorial, plus resetting tutorial on re-entry
 */

#ifndef UITutorialLayout_h
#define UITutorialLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class UIImage;

class UITutorialLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UITutorialLayout(void);

    /**
     * Destructor.
	 */
    ~UITutorialLayout(void);

// OPERATORS
// OPERATIONS

    /**
     * Listens for Key Press from User
    */
    virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

    void OnLoad();


// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES

    // Tutorial page indexing
    int mMinLayoutNum;
    int mMaxLayoutNum;
    int mCurLayoutNum;

    // Image filename
    std::string mLayoutFileNamePrefix;
    std::string mLayoutFileNameSuffix;

    // Tutorial Image
    UIImage* mBack;


private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UITutorialLayout_h_
