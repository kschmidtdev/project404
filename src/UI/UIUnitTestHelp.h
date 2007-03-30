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
 * Karl Schmidt, March 22 2007   | Correcting include orders and paths
 * Karl Schmidt, March 29 2007   | Turfed an unused default constructor
 */

#ifndef UIUnitTestHelp_h
#define UIUnitTestHelp_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UIElement.h>
#include <UI/UIText.h>


// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class SDLRenderer;

class UIUnitTestHelp : public UIElement
{
public:
// LIFECYCLE

    /**
     * Used constructor.
	 */
    UIUnitTestHelp(UIElement* nTest, const std::string & nClassName);


    /**
     * Destructor.
	 */
    ~UIUnitTestHelp(void);

// OPERATORS
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
    void RunNewTest( const std::string & message );


// ACCESS (writing)

    /**
     * Overridden to move elements with base element
     */
    virtual void SetPos( const Point & nPos);

    /**
     * Used for taking the same class with a different set of base arguements
     */
    virtual void SetNewElement( UIElement* nElement );

    /**
     * Sets Delay time (so it's quick for all test, except the current debug
     */
    void SetDelay(int n);


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
