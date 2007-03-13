/**
 * A special UI class used in unit testing.
 *
 * #include "UIUnitTestHelp.h"
 *
 * A special UI class used in unit testing to verify the different functionalities in the UIElement sub-classes
 *
 * @see UIElement
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 10 2007, Initial Creation
 */

#ifndef UIUnitTestHelp_h
#define UIUnitTestHelp_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UIElement.h>
#include <UIText.h>


// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIUnitTestHelp : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIUnitTestHelp(void);

    /**
     * Used constructor.
	 */
    UIUnitTestHelp(UIElement* nTest, string nClassName);


    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UIUnitTestHelp(const UIUnitTestHelp& from);

    /**
     * Destructor.
	 */
    ~UIUnitTestHelp(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIUnitTestHelp&                     operator=(UIUnitTestHelp& from);

// OPERATIONS

    /**
     * Override RenderSelf operation
     */
    virtual void RenderSelf(SDL_Surface* destination);

    /**
     *  Instruct to run basic tests
     */
    void RunBasicTest(void);

    /**
     *  Instruct to run new test (function is run outside this method.  This method only changes display.)
     */
    void RunNewTest(string message);


// ACCESS (writing)

    /**
     * Overridden to move elements with base element
     */
    virtual void SetPos( const Point & nPos);

    /**
     * Used for taking the same class with a different set of base arguements
     */
    virtual void SetNewElement( UIElement* nElement );


// INQUIRY (reading)

protected:
// PROTECTED VARIABLES

    // Test element
    UIElement* mTestElement;

    // Text Variables
    UIText mInfoText;
    UIText mElementTypeText;
    UIText mTestNumText;
    UIText mTestNum;

    // Text Format Variables
    int mFontSize;
    int mFontRed;
    int mFontGreen;
    int mFontBlue;

    // Position variables
    Point mInfoStart;
    int mElementInfoOffset; // y offset
    int mTestNumOffset;  // y offset

    // Test number
    int mTestNumNum;

    // Delay
    int mDelayTime;

    // SDL-Renderer
    SDLRenderer* mSRend;

    bool mInitialized;

// PROTECTED METHODS

    /**
     * Delay so to let people see the test and verify that test being conducted
     */
    void Delay(void);

    /**
     * Initialze: Add this element and test element to RenderQueue
     */
    void Initialize(void);

    /**
     * Moves "help" to flush-right of element being tested
     */
    void MoveToRight(void);

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIUnitTestHelp_h_
