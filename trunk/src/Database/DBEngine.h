/**
 * File: DBEngine.h
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 13 2007 | Initial design
 * Karl Schmidt, February 15 2007 | Fixed some odd header paths
 */

#ifndef DBEngine_h
#define DBEngine_h

#include "DatabaseManager.h"
#include "GameEngine/GameEngine.h"
#include "GameEngine/Archer.h"
#include "GameEngine/Healer.h"
#include "GameEngine/Knight.h"
#include "GameEngine/Mage.h"

class DBEngine
{
public:

   /**
    * Returns the instance of the DatabaseManager
    */
    static DBEngine* GetInstance();

    virtual ~DBEngine();
    void Initialize();
    void Shutdown();

    vector<Character*>* LoadParty();
    vector<Character*>* LoadEnemies();
    DBVector2D* LoadPartyStartingPoint(Character* thisCharacter);
    DBVector2D* LoadEnemiesStartingPoint(Character* thisCharacter);

    vector<Character*>* GetCharacterList() { return &mCharacterList; }
    vector<Item*>* GetItemList() { return &mItemList; }

protected:

    /**
     * Default constructor.
     */

     DBEngine();

    // PROTECTED VARIABLES

    static DBEngine* _instance;

private:

    WeaponItem* CreateWeapon( DBNode* WeaponNode ); // Function to create a weapon item instance from the Weapon Node and return it.
    ArmorItem* CreateArmor( DBNode* ArmorNode ); // Function to create a armor item instance from the Armor Node and return it.

    DatabaseManager* mDB;
    vector<Character*> mCharacterList;
    vector<Item*> mItemList;

};

#endif  // _DBEngine_



