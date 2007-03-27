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
 * Mike Malyuk, March 10, 2007   | Added map to AI removed point
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
 * Mike Malyuk, March 26, 2007   | Added variable for difficulty, changed constructor
 */

#ifndef AIControl_h
#define AIControl_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GameEngine/Map.h>
// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

class Level;


class AIControl
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    AIControl(Level* level, const Map & map, int difficulty);

    /**
     * Destructor.
	 */
    ~AIControl(void);

    // OPERATIONS
    Point DoAction();
    // ACCESS (writing)
    void SetLevel(Level* level){mLevel = level;}// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    Map mMap;
    Level* mLevel;
    int mDifficulty;
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _AIControl_h_
