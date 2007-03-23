/**
 * A class that represents lone text on the screen.
 *
 * #include "UIText.h"
 *
 * A class that represents lone text on the screen like the text seen on the "Congradulations screen"
 *
 * @see UIWinLayout
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 14 2007 | Initial Creation
 * Andrew Osborne, March 9 2007 | Added new ChangeText command that allows you to change all parameters
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
 * Karl Schmidt, March 21 2007 | Re-arranged class to eliminate code duplication as much as possible,
 								 added support for black background text
 * Andrew Osborne, March 21 2007 | Added 'CenterText' operation
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 */

#ifndef UIText_h
#define UIText_h

// SYSTEM INCLUDES
//
#include <string>

// PROJECT INCLUDES
//
#include <UI/UIElement.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIText : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIText(void);

    /**
     * Full constructor.
	 */
    UIText( const std::string & text, const int size, const int r, const int g, const int b, const bool backBlack = false );

    /**
     * Partial constructor.
	 */
    UIText( const std::string & text);

    /**
     * Destructor.
	 */
    virtual ~UIText(void);

// OPERATORS


// OPERATIONS

    /**
     * Method that centers the text on passed element.
     *
     *@param UIElement to center text around.
	 */
    void CenterText(UIElement* centerElement);

// ACCESS (writing)

    /**
     * Method that changes text .
	 */
    void ChangeText(const std::string & newText);

    /**
     * New Text (with parameters)
     */
    void ChangeText(const std::string & newText, const int s, const int r, const int g, const int b, const bool backBlack = false );

    /**
     * Change Colour.
	 */
    void SetColour( const int r, const int g, const int b);

    /**
     * Change Size.
	 */
    void SetSize( const int s);



// INQUIRY (reading)

protected:
// PROTECTED METHODS

    inline void MakeText();
    inline void DestroyText();

// PROTECTED VARIABLES
    int mRed;
    int mGreen;
    int mBlue;
    int mSize;
    std::string mText;
    bool mBackBlack;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIText_h_
