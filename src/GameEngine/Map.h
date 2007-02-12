/**
 * Maps are containers for tiles
 *
 * #include "Map.h"
 *
 * @see "Tile.h"
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 9, 2007 | Initial design
 */

#ifndef Map_h
#define Map_h

// SYSTEM INCLUDES
//
#include <vector>
// PROJECT INCLUDES
//
#include "Tile.h"
#include "Point.h"
// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class Map
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    Map(void);

    /**
     * Constructor
	 */
    Map(vector<Tile*> tiles);

    /**
     * Destructor.
	 */
    ~Map(void);

// OPERATIONS
// ACCESS (writing)
    void AddTiles(Tile* tile);
// INQUIRY (reading)
    Tile* GetTile(Point p);
protected:
    vector<Tile*> mTiles;
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Map_h_
