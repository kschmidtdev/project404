/**
 * The Class that represents the "Password Verification" screen.
 *
 * #include "UIPasswordVerificationLayout.h"
 *
 * The Class that represents the "Password Verification" screen that you see when the program starts up.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 15 2007, Initial Creation
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 */

#ifndef UIPasswordVerificationLayout_h
#define UIPasswordVerificationLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UILayout.h>
#include <UI/UIText.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIPasswordVerificationLayout : public UILayout
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIPasswordVerificationLayout(void);


    /**
     * Destructor.
	 */
    ~UIPasswordVerificationLayout(void);

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
    UIText* mPasswordText;
    std::string mStarString;
    std::string mPwdString;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIPasswordVerificationLayout_h_
