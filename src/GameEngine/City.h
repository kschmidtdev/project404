/**
 * A class that representes a city in the Game.
 *
 * #include "City.h"
 *
 * A class that representes a city (or over-map location) in the "Game Space".
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, March 13, 2007 | Initial Creation
 * Andrew Osborne, March 13, 2007 | Note: a lot of list methods are not fleshed out in .cpp
 * Karl Schmidt, March 14 2007    | Added city ID, removed default constructor (unused)
 * Mike Malyuk,  March 27 1007    | Set up retrieval for items
 * Andrew Osborne, March 29 2007 | Made GetMarket, GetArmory return pointers instead of copies
 */

#ifndef City_h
#define City_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <GameEngine/Item.h>
#include <Point.h>
#include <GameEngine/Map.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

typedef vector<Item*> ItemPtrVec;


class City
{
public:
// LIFECYCLE

    /**
     * Real constructor (more things to be added later)
	 */
    City(Point p, string fileName);

    /**
     * Destructor.
	 */
    ~City(void);

// OPERATIONS
// ACCESS (writing)

    /**
     * Adding Items to Armory/Market
     *
     *@param destination = "Armory" or "Market", nItem = pointer to item being added
     */
    void AddItem(string destination, Item* nItem);

    /**
     * Removing Items to Armory/Market
     *
     *@param source = "Armory" or "Market", oldItem = pointer to item being removed
     */
    void RemoveItem(string source, Item* oldItem);

    /**
     * Clear all Items in Armory/Market
     *
     *@param source = "Armory" or "Market"
     */
    void ClearItems(string source);

    /**
     * Sets as to whether a level/city has been defeated or not.
     */
    void SetDefeated(bool n);

// INQUIRY (reading)

    /**
     * Discovers whether there is an armory or not
     */
    bool HasArmory(void);

    /**
     * Discovers whether there is a Market or not
     */
    bool HasMarket(void);

    /**
     * Return an array of items for the armory
     */
    ItemPtrVec* GetArmory(void) {return &mArmoryItems;}

    /**
     * Return an array of items for the Market
     */
    ItemPtrVec* GetMarket(void) {return &mMarketItems;}

    /**
     * Return position on map
     */
    Point GetMapPos(void);

    /**
     * Returns image name
     */
    string GetImageName(void);

    /**
     * Returns whether level has been defeated or not.
     */
    bool IsDefeated(void);

    /**
     * Return the ID generated for the City
     */
    int GetID() { return mID; };

protected:
// PROTECTED VARIABLES

    // Basic Properties
    string mName;

    // Battle Properties
    //Level* mLevel;
    Map* mBattleMap;
    bool mDefeated;

    // Shop/Market Properties
    ItemPtrVec mArmoryItems;
    ItemPtrVec mMarketItems;

    // UI Properties
    Point mMapPos;
    string mImageFilename;

    static int _idCount;

    int mID;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _City_h_
