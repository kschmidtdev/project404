/**
 * File: DBEngine.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 13 2007 | Initial design
 * Seung Woo Han, February 13 2007 | Done for all the basic implementation
 */

#include <util.h>


#include "DBEngine.h"                                     // class implemented
#include <iostream>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

DBEngine* DBEngine::_instance = 0;

DBEngine* DBEngine::GetInstance()
{
    if( !_instance )
    {
        _instance = new DBEngine();
    }

    return _instance;
}

DBEngine::~DBEngine()
{
}

void DBEngine::Initialize()
{
    // Get Database instance.
    mDB = DatabaseManager::GetInstance();

    tacAssert( mDB );

    // Load XML file.
    mDB->LoadFromFile( "database.xml" );

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
}

void DBEngine::Shutdown()
{
    vector<Character*>::iterator CharIter;
    vector<Item*>::iterator ItemIter;

    for (CharIter=mCharacterList.begin(); CharIter!=mCharacterList.end(); CharIter++)
    {
        delete *CharIter;
    }

    for (ItemIter=mItemList.begin(); ItemIter!=mItemList.end(); ItemIter++)
    {
        delete *ItemIter;
    }

    if( _instance )
    {
        delete _instance; // delete DatabaseManager instance.
        _instance = NULL;
    }
}

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================
WeaponItem* DBEngine::CreateWeapon( DBNode* WeaponNode )
{
    DBInt* WeaponAttribute = dynamic_cast<DBInt*>( WeaponNode->GetFirstAttribute() ); // Downcast the attribute of a weapon node, so, we can retrieve the value of a weapon.
    WeaponItem* newWeapon = new WeaponItem( WeaponNode->GetName(), WeaponAttribute->GetData() ); // Create new weapon with name and its value which came from the weapon node.
    mItemList.push_back(newWeapon); // Add this new weapon instance into the item list.
    return newWeapon;
}

ArmorItem* DBEngine::CreateArmor( DBNode* ArmorNode )
{
    DBInt* ArmorAttribute = dynamic_cast<DBInt*>( ArmorNode->GetFirstAttribute() ); // Downcast the attribute of a armor node, so, we can retrieve the value of a armor.
    ArmorItem* newArmor = new ArmorItem( ArmorNode->GetName(), ArmorAttribute->GetData() ); // Create new armor with its name and value which came from the armor node.
    mItemList.push_back(newArmor); // Add this new armor instance into the item list.
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
    while ( PartyMemberNode != NULL ) // for (int i=0; i<4; i++)
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
    while ( EnemiesMemberNode != NULL ) // for (int i=0; i<4; i++)
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

DBVector2D* DBEngine::LoadPartyStartingPoint(Character* thisCharacter)
{
    DBNode* PartyNode = mDB->Search( "Party" );

    DBString* PartyMemberNameData;
    vector<Character*>::iterator Iter;

     // Search Characters.
    DBNode* PartyMemberNode = PartyNode->GetFirstChild(); // first member in the party.
    while ( PartyMemberNode != NULL ) // for (int i=0; i<4; i++)
    {
        PartyMemberNameData = dynamic_cast<DBString*>( PartyMemberNode->GetFirstAttribute() );

        if ( PartyMemberNameData->GetData() == thisCharacter->GetName() )
        {
            return dynamic_cast<DBVector2D*>( PartyMemberNode->GetAttribute( "Starting Point" ) );
        }

        PartyMemberNode = PartyNode->GetNextChild();
    }

    return NULL; // not found.
}

DBVector2D* DBEngine::LoadEnemiesStartingPoint(Character* thisCharacter)
{
    DBNode* EnemiesNode = mDB->Search( "Enemies" );

    DBString* EnemiesMemberNameData;
    vector<Character*>::iterator Iter;

     // Search Characters.
    DBNode* EnemiesMemberNode = EnemiesNode->GetFirstChild(); // first member in the party.
    while ( EnemiesMemberNode != NULL ) // for (int i=0; i<4; i++)
    {
        EnemiesMemberNameData = dynamic_cast<DBString*>( EnemiesMemberNode->GetFirstAttribute() );

        if ( EnemiesMemberNameData->GetData() == thisCharacter->GetName() )
        {
            return dynamic_cast<DBVector2D*>( EnemiesMemberNode->GetAttribute( "Starting Point" ) );
        }

        EnemiesMemberNode = EnemiesNode->GetNextChild();
    }

    return NULL; // not found.
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////
DBEngine::DBEngine()
{
}

/////////////////////////////// PRIVATE    ///////////////////////////////////
