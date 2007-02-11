/**
 * UIManager - Managers the UILayouts, controls which one is currently displayed
 *
 * #include "UIManager.h"
 *
 * UIManager constrols which layout is currently being displayed on the screen.  To set a current layout
 * call 'pushLayout', to go to a previous layout, call 'popLayout'.  UIManager also stores instances of all
 * the existing UILayouts
 *
 * @see UILayout
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 10 2007 | Initial Implementation
 * Andrew Osborne, February 10 2007 | Fleshed out comments
 * Andrew Osborne, February 11 2007 | Added GetInstance method
 */

#ifndef UIManager_h
#define UIManager_h

// SYSTEM INCLUDES
//
#include <vector>
#include <list>
using namespace std;

// PROJECT INCLUDES
//
#include <UILayout.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIManager
{
public:
// LIFECYCLE

    /**
    * Returns an instance of the inputmanager
    */
    static UIManager* GetInstance();



// OPERATORS

// OPERATIONS

    /**
     * Initializes the UIManager (Sets default layout, constructs master list, etc.).
	 *
	 */
    void Initialize(void);

    /**
     * Unconfigures UIManager, tells all of its elements to destroy themselves
     *
	 */
    void Shutdown(void);

    /**
     * Not currently used - though maybe to render the screen
     *
	 */
    void Render(void);  // or RenderSelf()

// ACCESS (writing)
    /**
     * Assigns passed UILayout as current layout.
	 *
	 * @param new current UILayout.
	 */
    void pushLayout(UILayout* newLayout);

    /**
     * Releases current UILayout and makes previous UILayout current one.
	 */
    void popLayout(void);

    /**
     * Adds UILayout to master list.
     *
	 * @param new UILayout to be added.
	 */
    void addLayout(UILayout* newLayout);

    /**
     * Removes UILayout to master list.
     *
	 * @param UILayout to be removed.
	 */
    void removeLayout(UILayout* removeLayout);

// INQUIRY (reading)

    /**
     * Peeks at what the current layout is.
	 *
	 * @return returns the current UILayout.
	 */
    UILayout* peekLayout(void);

protected:
// PROTECTED VARIABLES
    static UIManager* _instance;

    vector<UILayout*> LayoutMasterList;
    list<UILayout*> CurrentLayoutList;
    UILayout * curLayout;

// PROTECTED METHODS
    /**
     * Default constructor.
	 */
    UIManager(void);

    /**
     * Destructor.
	 */
    ~UIManager(void);

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIManager_h_
