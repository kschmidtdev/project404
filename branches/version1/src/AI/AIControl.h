/**
 * AIControl module directs AI movements
 *
 * #include "AIControl.h"
 *
 * This implementation will lock into the Level controls and determine movements.
 * Will also lock into UIGrid to display actions.
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 15 2007 | Initial Design
 */

#ifndef AIControl_h
#define AIControl_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <..\src\GameEngine\Character.h>
#include <..\src\UI\UIGrid.h>
#include <..\src\Point.h>
#include <..\src\GameEngine\Level.h>
// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class AIControl
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    AIControl(Level* level, Point maxMap);

    /**
     * Destructor.
	 */
    ~AIControl(void);

// OPERATIONS
Point DoAction();
// ACCESS (writing)
void SetLevel(Level* level){mLevel = level;}
void SetMax(Point p){mMax = p;}
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    Point mMax;
    Level* mLevel;
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _AIControl_h_
