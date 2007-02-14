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
    vector<Character*>* Initialize();
    WeaponItem* CreateWeapon( DBNode* WeaponNode );
    ArmorItem* CreateArmor( DBNode* ArmorNode );

protected:

private:

    vector<Character*> mCharacterList;

};

#endif  // _DBEngine_



