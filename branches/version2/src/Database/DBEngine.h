/**
 * File: DBEngine.h
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 13 2007 | Initial design
 * Karl Schmidt, February 15 2007  | Fixed some odd header paths
 * Karl Schmidt, March 15 2007 	   | Added parameter to Initialize
 * Karl Schmidt, March 15 2007     | Support for loading/saving encrypted db, save files, loading battle progress
 */

#ifndef DBEngine_h
#define DBEngine_h

#include "DatabaseManager.h"
#include "GameEngine/GameEngine.h"
#include "GameEngine/Archer.h"
#include "GameEngine/Healer.h"
#include "GameEngine/Knight.h"
#include "GameEngine/Mage.h"
#include "GameEngine/Tile.h"

class DBEngine
{
public:

    /**
     * Returns the instance of the DatabaseManager
     */
    static DBEngine* GetInstance();

    /**
     * Default destructor
     */
    virtual ~DBEngine();

    /**
     * Initialize this instance : Loading database and creating actual instances of Character, Item, and etc.
     */
    void Initialize( const bool loadFromSave = false );

    /**
     * Release memory
     */
    void Shutdown();

    /**
     * Load Player's characters in the battle.
     */
    vector<Character*>* LoadParty( int battleNumber );

    /**
     * Load AI's characters in the battle.
     */
    vector<Character*>* LoadEnemies( int battleNumber );

    /**
     * Load a starting point of player's character in the battle.
     */
    DBVector2D* LoadPartyStartingPoint( int battleNumber, Character* thisCharacter );

    /**
     * Load a starting point of AI's character in the battle.
     */
    DBVector2D* LoadEnemiesStartingPoint( int battleNumber, Character* thisCharacter );

    /**
     * Load a Battle Map (set of tiles).
     */
    vector<Tile> LoadBattleMap( int battleNumber );

    bool GetBattleCompleted( const int battleNumber );

    void SetBattleCompleted( const int battleNumber, const bool completed );

    /**
     * Update mCharacterList and save any changes to output file.
     */
    void SaveGame();

    /**
     * Save an encrypted version of the loaded database
     */
    void SaveEncryptedFile( const string & fileName );

    /**
     * Get Method. Return the pointer of the list of all the characters in the game.
     */
    vector<Character*>* GetCharacterList() { return &mCharacterList; } // INLINE METHOD.

    /**
     * Get Method. Return the pointer of the list of all the items in the game.
     */
    vector<Item*>* GetItemList() { return &mItemList; } // INLINE METHOD.

protected:

     /**
      * Default constructor.
      */
     DBEngine();

    // PROTECTED VARIABLES
    static DBEngine* _instance;

private:

    /**
     * Create WeaponItem instance from the Node.
     */
    WeaponItem* CreateWeapon( DBNode* WeaponNode ); // Function to create a weapon item instance from the Weapon Node and return it.

    /**
     * Create ArmorItem instance from the Node.
     */
    ArmorItem* CreateArmor( DBNode* ArmorNode ); // Function to create a armor item instance from the Armor Node and return it.

    // VARIABLES
    DatabaseManager* mDB;
    vector<Character*> mCharacterList;
    vector<Item*> mItemList;

};

#endif  // _DBEngine_



