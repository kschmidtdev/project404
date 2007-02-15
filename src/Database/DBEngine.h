/**
 * File: DBEngine.h
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 13 2007 | Initial design
 */

#ifndef DBEngine_h
#define DBEngine_h

#include "DatabaseManager.h"
#include "../GameEngine/GameEngine.h"
#include "../GameEngine/Archer.h"
#include "../GameEngine/Healer.h"
#include "../GameEngine/Knight.h"
#include "../GameEngine/Mage.h"

class DBEngine
{
public:

    DBEngine();
    virtual ~DBEngine();
    void Initialize();
    void Shutdown();
    WeaponItem* CreateWeapon( DBNode* WeaponNode );
    ArmorItem* CreateArmor( DBNode* ArmorNode );

    vector<Character*>* LoadParty();
    vector<Character*>* LoadEnemies();
    DBVector2D* LoadPartyStartingPoint(Character* thisCharacter);
    DBVector2D* LoadEnemiesStartingPoint(Character* thisCharacter);

protected:

private:

    DatabaseManager* mDB;
    vector<Character*> mCharacterList;

};

#endif  // _DBEngine_



