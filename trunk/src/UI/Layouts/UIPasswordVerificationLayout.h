/**
 * A one line description of the class.
 *
 * #include "UIPasswordVerificationLayout.h"
 *
 * A longer description.
 *
 * @see something
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date (Month Day Year), What was done
 */

#ifndef UIPasswordVerificationLayout_h
#define UIPasswordVerificationLayout_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UILayout.h>
#include <UIText.h>

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
    string mStarString;
    string mPwdString;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIPasswordVerificationLayout_h_
