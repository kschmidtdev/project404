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
 */

#ifndef UIMenu_h
#define UIMenu_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UI/UIElement.h>
#include <EventListener.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class UIButton;
class FuncObj;

typedef std::vector<UIElement*> UIElementPtrVec;
typedef UIElementPtrVec::iterator UIElementPtrItr;
typedef std::vector<FuncObj*> FuncObjPtrVec;
typedef FuncObjPtrVec::iterator FuncObjPtrItr;
typedef std::vector<UIButton*> UIButtonPtrVec;
typedef UIButtonPtrVec::iterator UIButtonPtrItr;

class UIMenu : public UIElement, public EventListener
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
     * Enable Menu (make cursor visible)
     */
    void Enable(void) {mCursor->SetVisible(true); }

    /**
     * Disable Menu (make cursor invisible)
     */
    void Disable(void) {mCursor->SetVisible(false); }

    /**
     * Disable (Ghost) Menu buttons (make text grey and disable funcitonality)
     */
    void SetGhost(int n, bool b);

// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    UIElement* mCursor;
    UIButtonPtrVec mButtons;
    FuncObjPtrVec mButtonFuncs;

    int mCursorPos;  // Starts with 0 to max (inclusive)
    int mMaxCursorPos;

    Point mButtonStart;
    Point mButtonOffset;
    Point mCursorOffset;





private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIMenu_h_
