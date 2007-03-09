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
 */

#ifndef UIMenu_h
#define UIMenu_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <SDL.h>
#include <Renderer/SDLRenderable.h>
#include <UIElement.h>
#include <EventListener.h>
#include <FuncObj.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

typedef vector<UIElement*> UIElementPtrVec;
typedef UIElementPtrVec::iterator UIElementPtrItr;
typedef vector<FuncObj*> FuncObjPtrVec;
typedef FuncObjPtrVec::iterator FuncObjPtrItr;

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

    /**
     * Hides buttons from viewing
     */
    void HideButton(int n);

    /**
     * Shows button for viewing
     */
    void ShowButton(int n);

    /**
     * After Showing/Hiding operations are performed, puts menu in proper visual order
     */
    void UpdateOrder(void);

// ACCESS (writing)
    /**
     * Changes position
    */
    virtual void SetPos( const Point & nPos );


    /**
     * Adds button with opeation
     */
    virtual void AddButton( const string nName, FuncObj* operation);

    /**
     * Adds button with opeation
     */
    //virtual void SetCancelFunction( FuncObj* operation);

// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    UIElement* mCursor;
    UIElementPtrVec mButtons;
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
