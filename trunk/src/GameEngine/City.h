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
 * Andrew Osborne, March 13, 2007, Initial Creation
 * Andrew Osborne, March 13, 2007, Note: a lot of list methods are not fleshed out in .cpp
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
     * Default constructor.
	 */
    City(void);

    /**
     * Real constructor (more things to be added later)
	 */
    City(Point p, string fileName);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    //City(const City& from);

    /**
     * Destructor.
	 */
    ~City(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    //City&                     operator=(City& from);

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
    ItemPtrVec* GetArmory(void);

    /**
     * Return an array of items for the Market
     */
    ItemPtrVec* GetMarket(void);

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

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _City_h_
