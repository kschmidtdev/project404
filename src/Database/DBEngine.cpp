/**
 * File: DBEngine.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 13 2007 | Initial design
 * Seung Woo Han, February 13 2007 | Done for all the basic implementation
 */

#include "DBEngine.h"                                     // class implemented
#include <util.h>
#include <iostream>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

DBEngine::DBEngine()
{
}

DBEngine::~DBEngine()
{
}

vector<Character*>* DBEngine::Initialize()
{
    // Get Database instance.
    mDB = DatabaseManager::GetInstance();

    tacAssert( mDB );

    // Load XML file.
    mDB->LoadFromFile( "database2.xml" );

    // Create DBNode instances from XML file.
    DBNode* TemplateNode = mDB->Search( "Templates" );
    DBNode* CharactersNode = TemplateNode->GetFirstChild(); // or GetChild("Characters");
    DBNode* ItemsNode = TemplateNode->GetNextChild(); // or GetChild("Items");
    DBNode* WeaponItemNode = ItemsNode->GetFirstChild(); // or GetChild("Weapon");
    DBNode* ArmorItemNode = ItemsNode->GetNextChild(); // or GetChild("Armor");

    // Create Character instances.
    DBNode* CharacterNode = CharactersNode->GetFirstChild();
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

        CharacterNode = CharactersNode->GetNextChild(); // Go to next Character.
    }

    return &mCharacterList;

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

vector<Character*>* DBEngine::LoadParty()
{
    vector<Character*>* PartyList = new vector<Character*>; // pointer to return.

    // Load Nodes.
    DBNode* LevelNode = mDB->Search( "Level" );
    DBNode* Stage1Node = LevelNode->GetFirstChild();
    DBNode* PartyNode = Stage1Node->GetFirstChild();

    // Search Characters.
    DBNode* PartyMemberNode = PartyNode->GetFirstChild(); // first member in the party.
    DBString* PartyMemberNameData;
    vector<Character*>::iterator Iter;
    for (int i=0; i<4; i++) // while ( PartyMemberNode != NULL )
    {
        PartyMemberNameData = dynamic_cast<DBString*>( PartyMemberNode->GetFirstAttribute() );
        for (Iter = mCharacterList.begin(); Iter != mCharacterList.end(); Iter++)
        {
            if ( (*Iter)->GetName() == PartyMemberNameData->GetData() )
            {
                PartyList->push_back( *Iter );
                break;
            }
        }

        PartyMemberNode = PartyNode->GetNextChild();
    }

    return PartyList;
}

vector<Character*>* DBEngine::LoadEnemies()
{
    vector<Character*>* EnemiesList = new vector<Character*>; // pointer to return.

    // Load Nodes.
    DBNode* EnemiesNode = mDB->Search( "Enemies" );

    // Search Characters.
    DBNode* EnemiesMemberNode = EnemiesNode->GetFirstChild(); // first member in the party.
    DBString* EnemiesMemberNameData;
    vector<Character*>::iterator Iter;
    for (int i=0; i<4; i++) // while ( EnemiesMemberNode != NULL )
    {
        EnemiesMemberNameData = dynamic_cast<DBString*>( EnemiesMemberNode->GetFirstAttribute() );
        for (Iter = mCharacterList.begin(); Iter != mCharacterList.end(); Iter++)
        {
            if ( (*Iter)->GetName() == EnemiesMemberNameData->GetData() )
            {
                EnemiesList->push_back( *Iter );
                break;
            }
        }

        EnemiesMemberNode = EnemiesNode->GetNextChild();
    }

    return EnemiesList;
}
