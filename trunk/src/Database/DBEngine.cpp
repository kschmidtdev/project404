/**
 * File: DBBase.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 7 2007 | Initial design
 * Seung Woo Han, February 11 2007 | Done for all the basic implementation
 */

#include "DBEngine.h"

#include <util.h>

DBEngine::DBEngine()
{
}

DBEngine::~DBEngine()
{
}

WeaponItem* DBEngine::CreateWeapon( DBNode* WeaponNode )
{
    DBInt* WeaponAttribute = dynamic_cast<DBInt*>( WeaponNode->GetFirstAttribute() );
    WeaponItem* newWeapon = new WeaponItem( WeaponNode->GetName(), WeaponAttribute->GetData() );
    return newWeapon;
}

ArmorItem* DBEngine::CreateArmor( DBNode* ArmorNode )
{
    DBInt* ArmorAttribute = dynamic_cast<DBInt*>( ArmorNode->GetFirstAttribute() );
    ArmorItem* newArmor = new ArmorItem( ArmorNode->GetName(), ArmorAttribute->GetData() );
    return newArmor;
}

vector<Character*>* DBEngine::Initialize()
{
    // Get Database instance.
    DatabaseManager* DB = DatabaseManager::GetInstance();

    tacAssert( DB );

    // Load XML file.
    DB->LoadFromFile( "database.xml" );

    // Create DBNode instances from XML file.
    DBNode* TemplateNode = DB->Search( "Templates" );
    DBNode* CharactersNode = TemplateNode->GetFirstChild(); // or GetChild("Characters");
    DBNode* Level1Node = CharactersNode->GetFirstChild(); // or GetChild("Level1");
    DBNode* ItemsNode = TemplateNode->GetNextChild(); // or GetChild("Items");
    DBNode* WeaponItemNode = ItemsNode->GetFirstChild(); // or GetChild("Weapon");
    DBNode* ArmorItemNode = ItemsNode->GetNextChild(); // or GetChild("Armor");

    // Create Character instances.
    DBNode* CharacterNode = Level1Node->GetFirstChild();
    while ( CharacterNode != NULL )
    {
        DBString* CharacterClassNode = dynamic_cast<DBString*>( CharacterNode->GetFirstAttribute() );
        DBInt* CharacterLevelNode = dynamic_cast<DBInt*>( CharacterNode->GetNextAttribute() );
        DBString* CharacterWeaponNode = dynamic_cast<DBString*>( CharacterNode->GetNextAttribute() );
        DBString* CharacterArmorNode = dynamic_cast<DBString*>( CharacterNode->GetNextAttribute() );

        if ( CharacterClassNode->GetData() == "Archer" )
        {
            // Create Weapon.
            WeaponItem* newWeapon = CreateWeapon( WeaponItemNode->GetChild( CharacterWeaponNode->GetData() ) );

            // Create Armor.
            ArmorItem* newArmor = CreateArmor( ArmorItemNode->GetChild( CharacterArmorNode->GetData() ) );

            // Create Archer.
            Archer* newArcher = new Archer( CharacterNode->GetName(), CharacterLevelNode->GetData(), newWeapon, newArmor );

            // Add Archer to the character list.
            mCharacterList.push_back( newArcher );
        }

        else if ( CharacterClassNode->GetData() == "Healer" )
        {
            // Create Weapon.
            WeaponItem* newWeapon = CreateWeapon( WeaponItemNode->GetChild( CharacterWeaponNode->GetData() ) );

            // Create Armor.
            ArmorItem* newArmor = CreateArmor( ArmorItemNode->GetChild( CharacterArmorNode->GetData() ) );

            // Create Healer.
            Healer* newHealer = new Healer( CharacterNode->GetName(), CharacterLevelNode->GetData(), newWeapon, newArmor );

            // Add Healer to the character list.
            mCharacterList.push_back( newHealer );
        }

        else if ( CharacterClassNode->GetData() == "Knight" )
        {
            // Create Weapon.
            WeaponItem* newWeapon = CreateWeapon( WeaponItemNode->GetChild( CharacterWeaponNode->GetData() ) );

            // Create Armor.
            ArmorItem* newArmor = CreateArmor( ArmorItemNode->GetChild( CharacterArmorNode->GetData() ) );

            // Create Knight.
            Knight* newKnight = new Knight( CharacterNode->GetName(), CharacterLevelNode->GetData(), newWeapon, newArmor );

            // Add Knight to the character list.
            mCharacterList.push_back( newKnight );
        }

        else if ( CharacterClassNode->GetData() == "Mage" )
        {
            // Create Weapon.
            WeaponItem* newWeapon = CreateWeapon( WeaponItemNode->GetChild( CharacterWeaponNode->GetData() ) );

            // Create Armor.
            ArmorItem* newArmor = CreateArmor( ArmorItemNode->GetChild( CharacterArmorNode->GetData() ) );

            // Create Mage.
            Mage* newMage = new Mage( CharacterNode->GetName(), CharacterLevelNode->GetData(), newWeapon, newArmor );

            // Add Mage to the character list.
            mCharacterList.push_back( newMage );
        }

        else
        {
            // unknown CharacterClass.
        }

        CharacterNode = Level1Node->GetNextChild(); // Go to next Character.
    }

    return &mCharacterList;

}
