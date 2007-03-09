/**
 * Single tile storing weight and type
 *
 * #include "Tile.h"
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 9, 2007 | Initial design
 */

#ifndef Tile_h
#define Tile_h

// SYSTEM INCLUDES
//
#include <string>
#include <iostream>
using namespace std;
// PROJECT INCLUDES
//
#include "Point.h"
// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class Tile
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    Tile(void);

    Tile(Point p, string type);
    /**
     * Destructor.
	 */
    ~Tile(void);

// OPERATIONS
// ACCESS (writing)
// INQUIRY (reading)
    Point GetPoint();
    int GetWeight();
    string GetType();
    string GetPic();
protected:
// PROTECTED VARIABLES
   Point mTilePoint;
   string mType;
   string mPic;
   int mWeight;
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Tile_h_
