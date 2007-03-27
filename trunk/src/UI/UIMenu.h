/**
 * UIMenu class (mostly abstract) used to define a menu element on screen
 *
 * #include "UIMenu.h"
 *
 * UIMenu contains a vector of buttons, a cursor and a background box.  It also can handle eventListening
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Creation
 * Karl Schmidt, February 10 2007 | Changed some include directory formats
 * Andrew Osborne, February 10 2007 | Filled out documentation
 * Karl Schmidt, February 14 2007 | Updated function capitalization, block style, typedefs, refs
 * Andrew Osborne, February 14 2007 | Created ability to add buttons - removed from default constructor
 * Andrew Osborne, March 18 2007 | Added Enable/Disable to allow the cursor to appear/disappear if the menu is active or not
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 * Andrew Osborne, March 23 2007    | Added "ClearButtons"
 * Andrew Osborne, March 24 2007 | converted from EventListener to UIEventListener
 * Andrew Osborne, March 24 2007 | Added Cancel event support
 * Andrew Osborne, March 24 2007 | Added ability to specifiy whether UIMenu is visible when it's disabled (mVisibleWhenDisabled)
 * Andrew osborne, March 24 2007 | Added SetBackground, SetSpacing, and SetCursorFunc.
 * Karl Schmidt, March 25 2007       | Added correct variable initialization (mParentLayout and mCancelEvent weren't being set to NULL on
 									   construction, as well as support for blank rows, and skipping over them, etc
 * Karl Schmidt, March 26 2007       | Added SetCursorPos for selecting a particular menu item manually
*/

#ifndef UIMenu_h
#define UIMenu_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UIElement.h>
#include <UIEventListener.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class UIButton;
class FuncObj;
class UILayout;

typedef std::vector<UIElement*> UIElementPtrVec;
typedef UIElementPtrVec::iterator UIElementPtrItr;
typedef std::vector<FuncObj*> FuncObjPtrVec;
typedef FuncObjPtrVec::iterator FuncObjPtrItr;
typedef std::vector<UIButton*> UIButtonPtrVec;
typedef UIButtonPtrVec::iterator UIButtonPtrItr;

class UIMenu : public UIElement, public UIEventListener
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIMenu(void);

    /**
     * Destructor.
	 */
    ~UIMenu(void);

// OPERATORS
// OPERATIONS
    /**
     * Method renders menu on screen
	 *
	 * @param the destination (SDL_Surface) where the menu will go.
	 *
	 */
    virtual void RenderSelf(SDL_Surface *destination);

    /**
     * Listens for Key Press from User
    */
    virtual void ProcessEvent( const InputManager::INPUTKEYS evt );


// ACCESS (writing)
    /**
     * Changes position
    */
    virtual void SetPos( const Point & nPos );


    /**
     * Adds button with opeation
     */
    virtual void AddButton( const std::string & nName, FuncObj* operation);

    /**
     * Clear all buttons from menu
     */
    virtual void ClearButtons(void);

    /**
     * Enable Menu (make cursor visible)
     */
    virtual void Enable(void);

    /**
     * Disable Menu (make cursor invisible)
     */
    virtual void Disable(void);

    /**
     * Disable (Ghost) Menu buttons (make text grey and disable funcitonality)
     */
    void SetGhost(int n, bool b);

    /**
     * Set Parent layout
     */
    void SetParent(UILayout* parent) { mParentLayout = parent; }

    /**
     * Set Cancel Event
     */
    void SetCancel(UIEventListener* cancel) { mCancelEvent = cancel; }

    /**
     * Set Visibility when Disabled
     */
    void SetVisibleWhenDisabled(bool v) { mVisibleWhenDisabled = v; }

    /**
     * Set Vertical Spacing between Buttons
     */
    void SetSpacing(int newSpacing);

    /**
     * Set Background image filename
     */
    void SetBackground(const std::string & nName);

    /**
     * Set Cursor Function
     */
    void SetCursorFunc(FuncObj* newCursorFunc);

    /**
     * Adds a blank row to the menu, which isn't drawn and the cursor will skip over it
     */
    void AddBlankRow();

    /**
     * Sets the current position of the cursor, used when a menu should have a certain
     * element highlighted at first
     */
    void SetCursorPos( const int newCursorPos );

// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    UIElement* mCursor;
    UIButtonPtrVec mButtons;
    FuncObjPtrVec mButtonFuncs;

    // Cursor Stuff
    int mCursorPos;  // Starts with 0 to max (inclusive)
    int mMaxCursorPos;
    FuncObj* mCursorFunc;

    Point mButtonStart;
    Point mButtonOffset;
    Point mCursorOffset;

    // Event Handling
    UILayout* mParentLayout;
    UIEventListener* mCancelEvent;
    bool mVisibleWhenDisabled;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIMenu_h_
