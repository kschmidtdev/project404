/**
 * A class that helps test the correctness of UILayouts
 *
 * #include "UILayoutTestHelp.h"
 *
 * A class that helps test the correctness of UILayouts
 *
 * @see UILayout
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 15, 2007, Initial Creation
 */

#ifndef UILayoutTestHelp_h
#define UILayoutTestHelp_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class UIText;


class UILayoutTestHelp : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UILayoutTestHelp(UILayout* test);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UILayoutTestHelp(const UILayoutTestHelp& from);

    /**
     * Destructor.
	 */
    ~UILayoutTestHelp(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UILayoutTestHelp&                     operator=(UILayoutTestHelp& from);

// OPERATIONS

    /**
     * Runs basic test for OnLoad, OnClose
     */
    void RunBasicTest(void);

    /**
     * Override the RenderSelf Operation
     */
    virtual void RenderSelf(SDL_Surface* destination) ;

    /**
     * Centers Text on backdrop Image
     */
    void CenterText(void);

// ACCESS (writing)

    /**
     * Override the Set Position Operation
     */
    virtual void SetPos( const Point & nPos );
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES

    UILayout* mTestLayout;
    //UIImage* mBackdrop;
    UIText* mMessage;
    int mDelay;
    SDLRenderer *mSR;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UILayoutTestHelp_h_
