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
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Andrew Osborne, March 24 2007 | made element a UIEventListener (added Enable, Disable, ProcessEvent, SetNextEvent (methods) and
 *                                  mNextEvent, mParentLayout (attribute)
 */

#ifndef UIScrollText_h
#define UIScrollText_h

// SYSTEM INCLUDES
//
#include <vector>

// PROJECT INCLUDES
//
#include <UI/UIElement.h>
#include <UIEventListener.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class UIText;
class UILayout;

typedef std::vector<UIText*> UITextVec;
typedef UITextVec::iterator UITextItr;
typedef std::vector<std::string> StringVec;
typedef StringVec::iterator StringItr;


class UIScrollText : public UIElement, public UIEventListener
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIScrollText(void);

    /**
     * Destructor.
	 */
    ~UIScrollText(void);

// OPERATORS
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

    /**
     * Listens for Key Press from User
    */
    virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

    /**
     * (Visually) Enables Element
     */
    virtual void Enable(void);

    /**
     * (Visually) Disables Element
     */
    virtual void Disable(void);

// ACCESS (writing)

    /**
     * Changes position
    */
    virtual void SetPos( const Point & nPos );

    /**
     * Given crude string of text, will format into different lines/pages
     */
    //void AddCrudeText(string newCrude);

    /**
     * Given a vector of strings, interpret the different lines/pages
     */
    //void AddFormattedText(vector<string> newLines);

    /**
     * Adds single line of text
     */
    void AddLine( const std::string & oneLine );

    /**
     * Adds single line of text
     */
    //void AddLine(UIText* oneLine);

    /**
     * Clear all text in (Scroll box's) memory
     */
    void ClearText(void);

    /**
     * Clearn one line of text
     */
    //void ClearOneLine(void);

    /**
     * Sets text Colour
     */
    //void SetNewColour

    /**
     * Set Next Event Handler (after ScrollText is extiguished)
     */
    void SetNextEvent(UILayout *parent, UIEventListener* nextEvent);

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

    // Event Handline
    UILayout *mParentLayout;
    UIEventListener *mNextEvent;


private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIScrollText_h_
