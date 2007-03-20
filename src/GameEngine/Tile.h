/**
 * Single tile storing weight and type
 *
 * #include "Tile.h"
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 9, 2007 | Initial design
 * Mike Malyuk, March 8 2007     | Added Tile mPic string and getter, allows UI to create easier
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
 */

#ifndef Tile_h
#define Tile_h

// SYSTEM INCLUDES
//
#include <string>

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

    /**
     * Tile Constructor
     */
    Tile( const Point & p, const std::string & type );

    /**
     * Destructor.
	 */
    ~Tile(void);

// OPERATIONS
// ACCESS (writing)
// INQUIRY (reading)
    const Point& GetPoint() const;
    const int GetWeight() const;
    const std::string& GetType() const;
    const std::string& GetPic() const;
protected:
// PROTECTED VARIABLES
   Point mTilePoint;
   std::string mType;
   std::string mPic;
   int mWeight;
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Tile_h_
