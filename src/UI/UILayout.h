/**
 * UILayout - an instance of a single screen (e.g Main Menu Screen )
 *
 * #include "UILayout.h"
 *
 * UILayout class represetns a single screen that a user would see (e.g. Main menu screen, battle screen).  It also
 * contains a list (vector) of all the elements on the screen for reference purposes.
 *
 * @see UIManager
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 7, 2007 | Initial class creation
 * Karl Schmidt, February 10 2007 | Changed inheritance from UIElemnt to SDLRenderable
 * Andrew Osborne, February 10 2007 | Fleshed out documentation
 * Andrew Osborne, February 11 2007 | Made UILayout inherit EventListener, added processEvent method
 * Karl Schmidt, February 13 2007 | Added typedefs instead of lots of vector<Type>
 * Karl Schmidt, February 14 2007 | Updated function capitalization, block style, typedefs, refs
 * Mike Malyuk, February 15 2007  | Added virtual function to get at Grid, look at this for v2
 * Andrew Osborne, March 21 2007  | Added SetEventHandler to allow easier passing of "event handling" among UIElements
 * Karl Schmidt, March 22 2007    | Correcting include orders and paths
 */

#ifndef UILayout_h
#define UILayout_h

// SYSTEM INCLUDES
//
#include <vector>

// PROJECT INCLUDES
//
#include <EventListener.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//
class UIElement;
class UIGrid;

typedef std::vector<UIElement*> UIElementPtrVec;
typedef UIElementPtrVec::iterator UIElementPtrItr;

class UILayout : public EventListener
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UILayout(void);

    /**
     * Destructor.
	 */
    virtual ~UILayout(void);

// OPERATORS
// OPERATIONS

    /**
     * Method that is run upon layout being loaded as current layout (called from UIManager)
	 *
	 */
    virtual void OnLoad(void);

    /**
     * Method that is run upon layout NO LONGER being used as current layout (called from UIManager)
	 *
	 */
    virtual void OnClose(void);

    /**
     * Listens for Key Press from User
    */
    virtual void ProcessEvent( const InputManager::INPUTKEYS evt );

    virtual UIGrid* GetGrid(){return NULL;};

// ACCESS (writing)

    /**
     * Sets current event handler
    */
    virtual void SetEventHandler( EventListener *e ) { mDefaultEventListener=e; }

// INQUIRY (reading)
    const std::string & GetName(void) const;

protected:
// PROTECTED VARIABLES
    UIElementPtrVec mElements;
    EventListener* mDefaultEventListener;
    std::string mName;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UILayout_h_
