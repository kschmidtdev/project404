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
 * Karl Schmidt, February 13 2007 | Added typedefs instead of lots of vector<Type>
 * Karl Schmidt, February 14 2007 | Updated function capitalization, block style, typedefs, refs
 * Andrew Osborne, February 15 2007 | Added PopAllLayouts
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

typedef vector<UILayout*> UILayoutVec;
typedef UILayoutVec::iterator UILayoutItr;

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
    void PushLayout(UILayout* newLayout);

    /**
     * Makes the UILayout, whose name is passed, as the current layout.
	 *
	 * @param string name of desired layout.
	 */
    void PushLayout(const string newLayout);

    /**
     * Releases current UILayout and makes previous UILayout current one.
	 */
    void PopLayout(void);

    /**
     * Releases all layouts from queue. (title page remains)
	 */
    void PopAllLayouts(void);

    /**
     * Adds UILayout to master list.
     *
	 * @param new UILayout to be added.
	 */
    void AddLayout(UILayout* newLayout);

    /**
     * Removes UILayout to master list.
     *
	 * @param UILayout to be removed.
	 */
    void RemoveLayout(UILayout* removeLayout);

// INQUIRY (reading)

    /**
     * Peeks at what the current layout is.
	 *
	 * @return returns the current UILayout.
	 */
    UILayout* PeekLayout(void);

    /**
     * Given string name of layout, finds and returns that layout
     *
     * @param string name of layout
     *
	 * @return pointer to requested layout (or NULL if doesn't exist).
	 */
	 UILayout* GetLayout(const string layoutName);

	 bool GetEndGameState() { return mGameShutdown; };

	 void SetEndGameState( const bool gameShutdown ) { mGameShutdown = gameShutdown; };

    /**
     * Destructor.
	 */
    ~UIManager(void);


protected:
// PROTECTED VARIABLES
    static UIManager* _instance;

    UILayoutVec mLayoutMasterList;
    list<UILayout*> mCurrentLayoutList;
    UILayout* mCurLayout;
    bool mGameShutdown;

// PROTECTED METHODS
    /**
     * Default constructor.
	 */
    UIManager(void);

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIManager_h_
