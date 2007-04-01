/**
 * File: DBEngine.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Seung Woo Han, February 13 2007 | Initial design
 * Seung Woo Han, February 13 2007 | Done for all the basic implementation
 * Seung Woo Han, March 14 2007    | LoadBattleMap has been added.
 *                                   LoadParty, LoadEnemies, LoadPartyStartingPoint, LoadEnemiesStartringPoint
 *                                   takes a parameter(battle number) now.
 * Karl Schmidt, March 15 2007	   | Added default behaviour so that it will attempt to load a savegame in Initialize if asked, otherwise load the regular db
 * Karl Schmidt, March 15 2007     | Temporarily added in encryption/decryption hack for save file checking
 * Seung Woo Han, March 15 2007    | Put some more comments and removed test codes.
 * Karl Schmidt, March 15 2007     | Support for loading/saving encrypted db, save files, loading battle progress
 */

#include <util.h>


#include "DBEngine.h"                                     // class implemented
#include <SecurityManager.h>
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

void DBEngine::Initialize( const bool loadFromSave )
{
    // Get Database instance.
    mDB = DatabaseManager::GetInstance();

    tacAssert( mDB );

    string saveFileName = "Save001.xml";
    // Load XML file. Default : database.xml. If there is any save file, load that.
    if( loadFromSave && mDB->IsValidFile( saveFileName ) )
    {
        SecurityManager::GetInstance()->DecryptFile( saveFileName, SecurityManager::GetInstance()->GetUserHash("user1") );
        mDB->LoadFromFile( saveFileName );
        SecurityManager::GetInstance()->EncryptFile( saveFileName, SecurityManager::GetInstance()->GetUserHash("user1") );
    }
    else
    {
        string dbFileName = "database.xml";
        if( mDB->IsValidFile( dbFileName ) )
        {
            SecurityManager::GetInstance()->DecryptFile( dbFileName, SecurityManager::GetInstance()->GetUserHash("user1") );
            mDB->LoadFromFile( dbFileName );
            SecurityManager::GetInstance()->EncryptFile( dbFileName, SecurityManager::GetInstance()->GetUserHash("user1") );
        }
        else // unencrypted
        {
            LogInfo("Loading unencrypted db\n");
            mDB->LoadFromFile( dbFileName );
        }
    }

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

    mCharacterList.clear();
    mItemList.clear();

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

vector<Character*>* DBEngine::LoadParty( int battleNumber )
{
    vector<Character*>* PartyList = new vector<Character*>; // pointer to return.

    // Load Nodes.
    DBNode* LevelNode = mDB->Search( "Level" );

    // Find Correct Battle Stage.
    DBNode* StageNode = LevelNode->GetFirstChild();
    for (int i=1; i<battleNumber; i++)
    {
        StageNode = LevelNode->GetNextChild();
    }

    DBNode* PartyNode = StageNode->GetChild( "Party" );

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

vector<Character*>* DBEngine::LoadEnemies( int battleNumber )
{
    vector<Character*>* EnemiesList = new vector<Character*>; // pointer to return.

    // Load Nodes.
    DBNode* LevelNode = mDB->Search( "Level" );

    // Find Correct Battle Stage.
    DBNode* StageNode = LevelNode->GetFirstChild();
    for (int i=1; i<battleNumber; i++)
    {
        StageNode = LevelNode->GetNextChild();
    }

    // Load Nodes.
    DBNode* EnemiesNode = StageNode->GetChild( "Enemies" );

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

DBVector2D* DBEngine::LoadPartyStartingPoint( int battleNumber, Character* thisCharacter )
{
    // Load Nodes.
    DBNode* LevelNode = mDB->Search( "Level" );

    // Find Correct Battle Stage.
    DBNode* StageNode = LevelNode->GetFirstChild();
    for (int i=1; i<battleNumber; i++)
    {
        StageNode = LevelNode->GetNextChild();
    }

    DBNode* PartyNode = StageNode->GetChild( "Party" );

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

DBVector2D* DBEngine::LoadEnemiesStartingPoint( int battleNumber, Character* thisCharacter )
{
    // Load Nodes.
    DBNode* LevelNode = mDB->Search( "Level" );

    // Find Correct Battle Stage.
    DBNode* StageNode = LevelNode->GetFirstChild();
    for (int i=1; i<battleNumber; i++)
    {
        StageNode = LevelNode->GetNextChild();
    }

    // Load Nodes.
    DBNode* EnemiesNode = StageNode->GetChild( "Enemies" );

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

vector<Tile> DBEngine::LoadBattleMap( int battleNumber )
{
    vector<Tile> BattleMap; // pointer to return.

    // Load Nodes.
    DBNode* LevelNode = mDB->Search( "Level" );

    // Find Correct Battle Stage.
    DBNode* StageNode = LevelNode->GetFirstChild();
    for (int i=1; i<battleNumber; i++)
    {
        StageNode = LevelNode->GetNextChild();
    }

    // Load Nodes.
    DBNode* BattleMapNode = StageNode->GetChild( "Map" ); // will be modified to choose among many different maps.

    // Search Characters.
    DBNode* TileSetNode = BattleMapNode->GetFirstChild(); // first member in the party.

    // Variables.
    DBString* TileType;
    DBVector2D* StartCoor;
    DBVector2D* EndCoor;
    int numTiles = 0;
    const int xSize = 10; // should be various later.
    int xCoor = 0;
    int yCoor = 0;

    // Create Tile instances and store them into BattleMap vector.
    while ( TileSetNode != NULL )
    {
        TileType = dynamic_cast<DBString*>( TileSetNode->GetFirstAttribute() );
        StartCoor = dynamic_cast<DBVector2D*>( TileSetNode->GetNextAttribute() );
        EndCoor = dynamic_cast<DBVector2D*>( TileSetNode->GetNextAttribute() );

        numTiles = ( EndCoor->GetX() * xSize + EndCoor->GetY() ) - ( StartCoor->GetX() * xSize + StartCoor->GetY() ) + 1;

        xCoor = StartCoor->GetX();
        yCoor = StartCoor->GetY();
        for (int i=0; i<numTiles; i++)
        {
            Point newPoint = Point( xCoor, yCoor );
            Tile newTile = Tile( newPoint, TileType->GetData() );
            BattleMap.push_back( newTile );

            yCoor++;
            if ( yCoor > 9 ) { yCoor = 0; xCoor++; }
        }

        TileSetNode = BattleMapNode->GetNextChild();
    }

    return BattleMap;

}

bool DBEngine::GetBattleCompleted( const int battleNumber )
{
    // Load Nodes.
    DBNode* levelNode = mDB->Search( "Level" );

    // Find Correct Battle Stage.
    DBNode* stageNode = levelNode->GetFirstChild();
    for (int i = 1; i < battleNumber; ++i )
    {
        stageNode = levelNode->GetNextChild();
    }

    if( stageNode )
    {
        if( stageNode->GetAttribute("Completed") )
        {
            DBInt* completedStage = dynamic_cast<DBInt*>( stageNode->GetAttribute("Completed") );
            return completedStage->GetData();
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void DBEngine::SetBattleCompleted( const int battleNumber, const bool completed )
{
    // Load Nodes.
    DBNode* levelNode = mDB->Search( "Level" );

    // Find Correct Battle Stage.
    DBNode* stageNode = levelNode->GetFirstChild();
    for (int i = 1; i < battleNumber; ++i )
    {
        stageNode = levelNode->GetNextChild();
    }

    if( stageNode && stageNode->GetAttribute("Completed") )
    {
        DBInt* completedStage = dynamic_cast<DBInt*>( stageNode->GetAttribute("Completed") );
        completedStage->SetData( static_cast<int>(completed) );
    }
}

void DBEngine::SaveGame()
{
    vector<Character*>::iterator Iter;
    for (Iter = mCharacterList.begin(); Iter != mCharacterList.end(); Iter++)
    {
        DatabaseManager::GetInstance()->UpdateNode( (*Iter)->GetName(), "Level", (*Iter)->GetLevel() );
    }

    string saveFileName = "Save001.xml";
    DatabaseManager::GetInstance()->SaveToFile( saveFileName );
    SecurityManager::GetInstance()->EncryptFile( saveFileName, SecurityManager::GetInstance()->GetUserHash("user1") );
}

void DBEngine::SaveEncryptedFile( const string & fileName )
{
    DatabaseManager::GetInstance()->SaveToFile( fileName );
    SecurityManager::GetInstance()->EncryptFile( fileName, SecurityManager::GetInstance()->GetUserHash("user1") );
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////
DBEngine::DBEngine()
{
}

/////////////////////////////// PRIVATE    ///////////////////////////////////