/**
 * A one line description of the class.
 *
 * #include "UIManager.h"
 *
 * A longer description.
 *
 * @see something
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date (Month Day Year), What was done
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
     * Default constructor.
	 */
    UIManager(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    UIManager(const UIManager& from);

    /**
     * Destructor.
	 */
    ~UIManager(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    UIManager&                     operator=(UIManager& from);

// OPERATIONS
void Initialize(void);
void Shutdown(void);
void Render(void);  // or RenderSelf()

// ACCESS (writing)
void pushLayout(UILayout* newLayout);
void popLayout(void);
void addLayout(UILayout* newLayout);
void removeLayout(UILayout* removeLayout);

// INQUIRY (reading)
UILayout* peekLayout(void);

protected:
// PROTECTED VARIABLES
vector<UILayout*> LayoutMasterList;
list<UILayout*> CurrentLayoutList;
//deque<UILayout*> CurrentLayoutList;
UILayout * curLayout;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UIManager_h_
