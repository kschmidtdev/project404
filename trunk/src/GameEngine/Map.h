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
 * Mike Malyuk, March 9, 2007    | Added GetTiles()
 * Mike Malyuk, March 10, 2007   | Added Character include and Map movement finder
 * Mike Malyuk, March 14, 2007   | Changed parameters on GetMovementRange
 */

#ifndef Map_h
#define Map_h

// SYSTEM INCLUDES
//
#include <vector>
#include "limits.h"
// PROJECT INCLUDES
//
#include "Tile.h"
#include "Point.h"
#include "Character.h"
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
    Map(vector<Tile> tiles);

    /**
     * Destructor.
	 */
    ~Map(void);

// OPERATIONS
// ACCESS (writing)
    void AddTiles(Tile tile);
// INQUIRY (reading)
    Tile GetTile(Point p);
    vector<Tile> GetTiles();
    vector<Point> GetMovementRange(vector<Character*> everyone, vector<Character*> enemies, Character* guy);
protected:
    vector<Tile> mTiles;
    int mMaxX;
    int mMaxY;
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _Map_h_
