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
 * Mike Malyuk, March 14, 2007   | Added GetMaxX() and GetMaxY()
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
 * Karl Schmidt, March 23 2007   | Corrected include paths
 */

#ifndef Map_h
#define Map_h

// SYSTEM INCLUDES
//
#include <vector>
// PROJECT INCLUDES
//
#include <GameEngine/Tile.h>
#include <Point.h>
#include <GameEngine/Character.h>
// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

typedef std::vector<Tile> TileVec;
typedef TileVec::iterator TileItr;
typedef TileVec::const_iterator TileConstItr;

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
    Map( const TileVec & tiles );

    /**
     * Destructor.
	 */
    ~Map(void);

// OPERATIONS
// ACCESS (writing)
    void AddTiles( const Tile & tile);
// INQUIRY (reading)
    const Tile & GetTile( const Point & p);
    const TileVec & GetTiles() const;
    const vector<Point> GetMovementRange( const vector<Character*>& everyone, const vector<Character*> & enemies, Character* guy);
    const int GetMaxX() const {return mMaxX;}
    const int GetMaxY() const {return mMaxY;}
protected:
    TileVec mTiles;
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
