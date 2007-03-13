/**
 * Scrolling Text box for display
 *
 * #include "UIScrollText.h"
 *
 * Scrolling Text box for display
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 12 2007, Initial Creation
 */

#ifndef UIScrollText_h
#define UIScrollText_h

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
typedef vector<UIText*> UITextVec;
typedef UITextVec::iterator UITextItr;
typedef vector<string> StringVec;
typedef StringVec::iterator StringItr;


class UIScrollText : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIScrollText(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //UIScrollText(const UIScrollText& from);

    /**
     * Destructor.
	 */
    ~UIScrollText(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //UIScrollText&                     operator=(UIScrollText& from);

// OPERATIONS

    /**
     * Progress to next page of text
     *
     * @return true - on success, false on no page to progress too
     */
    bool NextPage();

    /**
     * Method renders Scrolling Text
	 *
	 * @param the destination (SDL_Surface) where the menu will go.
	 *
	 */
    virtual void RenderSelf(SDL_Surface *destination);

// ACCESS (writing)

    /**
     * Changes position
    */
    virtual void SetPos( const Point & nPos );

    /**
     * Given crude string of text, will format into different lines/pages
     */
    void AddCrudeText(string newCrude);

    /**
     * Given a vector of strings, interpret the different lines/pages
     */
    void AddFormattedText(vector<string> newLines);

    /**
     * Adds single line of text
     */
    void AddLine(string oneLine);

    /**
     * Adds single line of text
     */
    void AddLine(UIText* oneLine);

    /**
     * Clear all text in (Scroll box's) memory
     */
    void ClearText(void);

    /**
     * Clearn one line of text
     */
    void ClearOneLine(void);

    /**
     * Sets text Colour
     */
    //void SetNewColour

// INQUIRY (reading)

protected:
// PROTECTED VARIABLES

    // Text information
    UITextVec mUILines;
    StringVec mStringLines;

    int mMaxLength;
    int mMaxLines; // # of lines on screen at once

    // Text Formating
    int mColourRed;
    int mColourGreen;
    int mColourBlue;
    int mFontSize;

    // Position Formating
    int mLineSpacing;
    Point mStartPoint;
    Point mLineOffest;

    // Current Display informatino
    int mCurStartIndex;


private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIScrollText_h_
