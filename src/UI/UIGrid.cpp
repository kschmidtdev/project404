/**
 * File: UIGrid.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007   | Initial Creation
 * Karl Schmidt,   February 11 2007   | Added checks to prevent crashing if textures are not loaded
 * Andrew Osborne, February 11 2007   | Added Destructor and documentaton
 * Andrew Osborne, February 12 2007   | Setup characters, allowed movement, created a number of helper functions
 * Karl Schmidt,   February 13 2007   | Reworked destructor, noted current bug and temporary work-around
 * Karl Schmidt,   February 13 2007   | Modified hasCharacter to return a value in all cases (fixes a warning, safer)
 * Mike Malyuk,    February 14 2007   | Modified pretty much everything. Stopped newing of tiles, waste of space.
 * Mike Malyuk,    February 14 2007   | Fixed obscure bug where friend standing on tile where opponent died would be
 *                                      cleared from screen if attacker clicked on it. Also allowed your character to die
 *                                      Knight on Knight
 * Karl Schmidt,   February 14 2007   | Updated function capitalization, block style, typedefs, refs
 * Mike Malyuk,    February 14 2007   | Added function to show exhausted state, refreshes on turn.
 * Mike Malyuk,    February 14 2007   | Added another check for partyexhaustion, move point far enough away to not be an issue.
 * Karl Schmidt,   February 15 2007   | Added action indication support for attacking/healing
 * Mike Malyuk,    March 4 2007       | Reworked ConfirmFunction, removed a lot of redundant code, removed
 *                                      our dependence on NULL, instead using state. Removed use of mMoveRange
 * Mike Malyuk,    March 9 2007       | Finally implemented starting version of Map. Grid now drawn from Map.
 * Karl Schmidt, March 9 2007	 	  | Changed textures to png, re-arranged render order, took out magic offset number
 * Mike Malyuk,  March 10 2007        | Changed implementations to remove Level move info and insert Map move info
 * Andrew Osborne, March 11 2007      | Added CharWindow functionality to respond to cursor movement - added CursorUpdate method
 *                                    | & setCharWindow
 * Karl Schmidt,	March 11 2007	  | Added a hacky fix to a rare crash bug. (see a big comment block at around line 364
 * Mike Malyuk,     March 14 2007     | Added new params to GetMovementRange in Map, fixed.
 * Karl Schmidt,	March 14 2007	  | Removed previous hacky fix, moved to elsewhere
 * Mike Malyuk,     March 14 2007     |Added Initialize, set more pointers to NULL, removed old methods,
 *                                     optimized movement by only making one call to Map for movement per player vs 2
 * Karl Schmidt, 	March 14 2007	  | Added and re-arranged initialize list so more pointers are set to NULL on construction (safer)
 * Mike Malyuk,     March 14 2007     | Generalized columns in Initializer
 * Andrew osborne,  March 14 2007     | Removed Cursor, as it is a lame duck class that does nothing different from UIImage
 * Seung Woo Han,   March 17 2006     | New Pics
 * Karl Schmidt,    March 20 2007     | Major adding of consts and reference usage, rearranging includes
 * Karl Schmidt,    March 21 2007     | Added support for health change indication UI
 * Karl Schmidt,    March 22 2007     | Correcting include orders and paths
 * Karl Schmidt,    March 23 2007     | Got rid of more using namespace std; usage
 * Karl Schmidt,    March 23 2007     | Added mini-map implementation, enum instead of string for character tile type identification,
                                        removed some old code that wasn't used anymore
 * Karl Schmidt,    March 29 2007     | Added DoLoseOrWin helper function, removed commented out code
 * Karl Schmidt,    March 30 2007     | Modified DrawHealthIndicationers as per issue 74, add hacky but slightly nicer text,
 										added a 1 second delay when the game is over (win or lose)
 */

#include "UIGrid.h"                                // class implemented

#include <util.h>
#include <Logger.h>

#include <UI/UIManager.h>
#include <InputManager.h>
#include <UI/UICharWindow.h>

#include <GameEngine/Character.h>
#include <GameEngine/Level.h>
#include <ResourceManager/ResourceManager.h>
#include <Renderer/SDLRenderer.h>

namespace
{
    const int INDICATER_DELAY = 600;
    const Point mapOffset( 10, 10 );
    const Point miniMapOffset( 450, 380 );

    const std::string MINIMAPIMAGE_PREFIX( "mini_" );
    const std::string MINIMAP_PARTY_IMG( MINIMAPIMAGE_PREFIX + "party.png" );
    const std::string MINIMAP_ENEMY_IMG( MINIMAPIMAGE_PREFIX + "enemy.png" );
}

/////////////////////////////// PUBLIC ///////////////////////////////////////
//============================= LIFECYCLE ====================================

UIGrid::UIGrid()
: UIElement(),
  mTiles(),
  mMovePoints(),
  mNumRows( 10 ), mNumColumns( 10 ), mCursorPos( Point(0,0) ), mTileStart( Point(10,10) ), mTileOffset( 0 ),
  mCursor(NULL), mCharWindow( NULL ), mMap( NULL ), mCurCharacter( NULL ), mLevel( NULL )
{

}// UIGrid


UIGrid::~UIGrid()
{
    if( mCursor )
    {
        delete mCursor;
        mCursor = NULL;
    }
}// ~UIGrid


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================

void UIGrid::RenderSelf(SDL_Surface* destination)
{
    // Tiles are rendered first (bottom)
    for ( UITileItr iter = mTiles.begin(); iter!=mTiles.end(); ++iter )
    {
        iter->RenderSelf(destination);
    }

    // Cursor is rendered last (top)
    mCursor->RenderSelf(destination);

    for( UITileItr i = mMiniMap.begin(); i != mMiniMap.end(); ++i )
    {
        i->RenderSelf( destination );
    }
}

void UIGrid::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    // Come back to this later
    Point newPos;

    switch(evt)
    {
        case InputManager::UP:
            // Move cursor up
            if (mCursorPos.GetY()>0)
            {
                mCursorPos = mCursorPos + Point(0,-1);
                UpdateCursor();
            }
            break;
        case InputManager::DOWN:
            if (mCursorPos.GetY()<mMaxCursorPos.GetY())
            {
                mCursorPos = mCursorPos + Point(0,1);
                UpdateCursor();
            }
            break;
        case InputManager::LEFT:
            // Move cursor up
            if (mCursorPos.GetX()>0)
            {
                mCursorPos = mCursorPos + Point(-1,0);
                UpdateCursor();
            }
            break;
        case InputManager::RIGHT:
            if (mCursorPos.GetX()<mMaxCursorPos.GetX())
            {
                mCursorPos = mCursorPos + Point(1,0);
                UpdateCursor();
            }
            break;
        case InputManager::CONFIRM:
            ConfirmFunction(mCursorPos);
            break;
        case InputManager::CANCEL:
            break;
        default:
            break;

    }
}

void UIGrid::ConfirmFunction( const Point & p )
{
    int curState = mLevel->ReturnState();
    Point old;
    bool pointexists = false;
    vector<Point> movement;
    switch(curState)
    {
        case Level::FREE:
        {

            // Attempt to select character
            // ------------------------------------------
            mCurCharacter = mLevel->OnSelect(p);

            // Step 1 - check to see if selected character
            // ===============
            if ( mLevel->ReturnState() == 0)
            {
                // Unsuccessful, do nothing
            }

            else
            {

                // Step 2 - prepare screen/UI for moveable range
                // ==============
                AddMoveableRange( mLevel->GetEveryone(), mLevel->GetEnemies(), mCurCharacter);
            }
        }
        break;

        case Level::MOVE:
        {

            // Attempting to MOVE to new spot
            // ----------------------------------------------

            // Step 1 - check if valid point

            // Step 2 - check if clicked-self

            // Step 3 - Move Character

            // Step 4 - acknowledge level of move

            // Step 5 - Remove moveable Range from screen

            // Step 6 - Prep screen/UI for Attackable Range

            old = mCurCharacter->GetPoint();
            for(vector<Point>::iterator piter = mMovePoints.begin(); piter != mMovePoints.end(); piter++)
            {
                if((*piter) == p)
                {
                    pointexists = true;
                }
            }
            if(pointexists)
            {
                mLevel->OnSelect(p);

                if ( mLevel->ReturnState() == 2 || mLevel->ReturnState() == 0 || mLevel->ReturnState() == 3)
                {
                    // remove icon from old spot
                    RemoveCharacter( old);

                    // add icon to new spot

                    mCurCharacter->Move(p);
                    AddPartyCharacter( mCurCharacter );

                    if( mLevel->ReturnState() == 0 || mLevel->ReturnState() == 3 )
                    {
                        RemoveCharacter(p);
                        AddExhaustedCharacter(mCurCharacter);
                        ClearMoveableRange();
                    }

                    // Prep screen for attack
                    else
                    {
                        ClearMoveableRange();
                        AddAttackRange( mLevel->GetAttackArea() );
                    }
                    //ClearMoveableRange();
                }

                else
                {
                    // do nothing
                    // maybe display message later....
                }

                if(mLevel->AllExhaustedParty())
                {
                    vector<Character*> revigorate = mLevel->GetParty();
                    for(vector<Character*>::iterator citer = revigorate.begin(); citer != revigorate.end(); citer++)
                    {
                        RemoveCharacter((*citer)->GetPoint());
                        AddPartyCharacter((*citer));
                    }
                    mLevel->SetState(Level::AIFREE);
                }

                //Check for EndGame
                DoLoseOrWin( mLevel );
            }
        }
        break;
        case Level::ATTACK:
        {
            // Attempting to attack
            //------------------------------------------------------

            // Step 1 - check for valid attack point

            // Step 2 - check for self-clicked

            // Step 3 - Attack other character

            // Step 4 - run end turn check (is target dead, is enemy dead, is party exhausted)

            // Step 5 - Initialize next turn

            // check to see if attack-range is valid

            // now check if person is there
            Character* defender = mLevel->OnSelect(p);
            if( (mLevel->ReturnState() == Level::FREE || mLevel->ReturnState() == Level::AIFREE) )
            {
                DrawHealthIndicationers( mCurCharacter, defender );

                RemoveCharacter(mCurCharacter->GetPoint());
                AddExhaustedCharacter(mCurCharacter);
                ClearAttackRange();
            }

            if(mLevel->PointHasPerson(p) != NULL && mCurCharacter != NULL && mCurCharacter->GetPoint() != p)
            {
                RemoveCharacter(p);
                mLevel->PointHasPerson(p)->Move(Point(-5,-5));
            }
            UpdateCursor();
            if(mCurCharacter->IsDead())
            {
                RemoveCharacter(mCurCharacter->GetPoint());
                mCurCharacter->Move(Point(-5,-5));
            }

            //keep game running
            if(mLevel->AllExhaustedParty())
            {
                vector<Character*> revigorate = mLevel->GetParty();
                for(vector<Character*>::iterator citer = revigorate.begin(); citer != revigorate.end(); citer++)
                {
                    RemoveCharacter((*citer)->GetPoint());
                    AddPartyCharacter((*citer));
                }
                mLevel->SetState(Level::AIFREE);
            }

            // Check for end game

            // Check for end turn

            //Check for EndGame
            DoLoseOrWin( mLevel );
        }
        break;

        case Level::AIFREE:
        {
            // Attempt to select character
            // ------------------------------------------
            mCurCharacter = mLevel->OnAISelect(p);

            // Step 1 - check to see if selected character
            // ===============
            if (mLevel->ReturnState() == 3)
            {
                // Unsuccessful, do nothing
            }
            else
            {
                // Step 2 - prepare screen/UI for moveable range
                // ==============
                AddMoveableRange( mLevel->GetEveryone(), mLevel->GetParty(), mCurCharacter );
            }
        }
        break;

        case Level::AIMOVE:
        {
            // Attempting to MOVE to new spot
            // ----------------------------------------------

            // Step 1 - check if valid point

            // Step 2 - check if clicked-self

            // Step 3 - Move Character

            // Step 4 - acknowledge level of move

            // Step 5 - Remove moveable Range from screen

            // Step 6 - Prep screen/UI for Attackable Range

            // Check if move was cancelled
            old = mCurCharacter->GetPoint();
            for(vector<Point>::iterator piter = mMovePoints.begin(); piter != mMovePoints.end(); piter++)
            {
                if((*piter) == p)
                {
                    pointexists = true;
                }
            }
            if(pointexists)
            {
                mLevel->OnAISelect(p);

                if ( mLevel->ReturnState() == 3 || mLevel->ReturnState() == 5 || mLevel->ReturnState() == 0 )
                {
                    // remove icon from old spot
                    RemoveCharacter( old);

                    // add icon to new spot

                    mCurCharacter->Move(p);
                    AddEnemyCharacter( mCurCharacter );

                    if( mLevel->ReturnState() == 0 || mLevel->ReturnState() == 3)
                    {
                        RemoveCharacter(p);
                        AddExhaustedCharacter(mCurCharacter);

                    }
                    // Prep screen for attack
                    ClearMoveableRange();
                }

                else
                {
                    // do nothing
                    // maybe display message later....
                }

                if(mLevel->AllExhaustedEnemies())
                {
                    vector<Character*> revigorate = mLevel->GetEnemies();
                    for(vector<Character*>::iterator citer = revigorate.begin(); citer != revigorate.end(); citer++)
                    {
                        RemoveCharacter((*citer)->GetPoint());
                        AddEnemyCharacter((*citer));
                    }
                    mLevel->SetState(Level::FREE);
                }

                DoLoseOrWin( mLevel );
            }
        }
        break;

        case Level::AIATTACK:
        {
            // Attempting to attack
            //------------------------------------------------------

            // Step 1 - check for valid attack point

            // Step 2 - check for self-clicked

            // Step 3 - Attack other character

            // Step 4 - run end turn check (is target dead, is enememy dead, is party exhausted)

            // Step 5 - Initialize next turn

            // check to see if attack-range is valid

            // now check if person is there
            Character* defender = mLevel->OnAISelect(p);

            if(mLevel->ReturnState() == Level::FREE || mLevel->ReturnState() == Level::AIFREE)
            {
                DrawHealthIndicationers( mCurCharacter, defender );
                RemoveCharacter(mCurCharacter->GetPoint());
                AddExhaustedCharacter(mCurCharacter);
            }
            Character* part = mLevel->AIPointHasPerson(p);

            if(part != NULL && mCurCharacter != NULL && mCurCharacter->GetPoint() != p)
            {
                RemoveCharacter(p);
                part->Move(Point(-5,-5));
            }

            if(mCurCharacter->IsDead())
            {
                RemoveCharacter(mCurCharacter->GetPoint());
                mCurCharacter->Move(Point(-5,-5));
            }

            //keep game running
            if(mLevel->AllExhaustedEnemies())
            {
                vector<Character*> revigorate = mLevel->GetEnemies();
                for(vector<Character*>::iterator citer = revigorate.begin(); citer != revigorate.end(); citer++)
                {
                    RemoveCharacter((*citer)->GetPoint());
                    AddEnemyCharacter((*citer));
                }
                mLevel->SetState(Level::FREE);
            }


            // Check for end game

            // Check for end turn
            //Check for "Losing" EndGame

            DoLoseOrWin( mLevel );
        }
        break;

    }
}

void UIGrid::AddEnemyCharacter(Character *c)
{
    const Point & p = c->GetPoint();

    if ( ValidPoint(p)  )
    {
        int index = FindIndex( p );
        mTiles[index].AddCharacter( GetClassSurface( c, G_ENEMY ) );
        mMiniMap[index].AddCharacter( GetClassSurface(c, G_ENEMY, true ) );
    }
}

void UIGrid::AddPartyCharacter(Character *c)
{
    const Point & p = c->GetPoint();

    if ( ValidPoint(p)  )
    {
        int index = FindIndex( p );
        mTiles[index].AddCharacter( GetClassSurface( c, G_PARTY ) );
        mMiniMap[index].AddCharacter( GetClassSurface( c, G_PARTY, true ) );
    }
}

void UIGrid::AddExhaustedCharacter(Character *c)
{
    const Point & p = c->GetPoint();

    if ( ValidPoint(p)  )
    {
        int index = FindIndex( p );
        mTiles[index].AddCharacter( GetClassSurface( c, G_EXHAUSTED ) );
        mMiniMap[index].AddCharacter( GetClassSurface( c, G_EXHAUSTED, true ) );
    }
}

void UIGrid::RemoveCharacter( const Point & p)
{
    if ( ValidPoint(p) )
    {
        int index = FindIndex( p );
        mTiles[index].RemoveCharacter();
        mMiniMap[index].RemoveCharacter();
    }
}


inline void UIGrid::ClearMoveableRange(void)
{
    for_each( mTiles.begin(), mTiles.end(), mem_fun_ref( &UITile::RemoveRange ) );
}


inline void UIGrid::ClearAttackRange(void)
{
    for_each( mTiles.begin(), mTiles.end(), mem_fun_ref( &UITile::RemoveRange ) );
}

void UIGrid::AddAttackRange( const PointVec & attackRange )
{
    SDL_Surface* RangeImage = ResourceManager::GetInstance()->LoadTexture("yellowCursor.png");
    int index;

    for ( PointConstItr i=attackRange.begin(); i!=attackRange.end(); ++i )
    {
        if(ValidPoint((*i)))
        {
            index = FindIndex( (*i) );
            mTiles[index].AddRange(RangeImage);
        }
    }
}


void UIGrid::AddMoveableRange( const vector<Character*> & everyone, const vector<Character*> & enemies, Character* you )
{
    mMovePoints = mMap->GetMovementRange(everyone, enemies, you);

    SDL_Surface* RangeImage = ResourceManager::GetInstance()->LoadTexture("blueCursor.png");

    for ( PointItr i = mMovePoints.begin(); i != mMovePoints.end(); ++i )
    {
        if (ValidPoint((*i)))
        {
            mTiles[ FindIndex( (*i) ) ].AddRange(RangeImage);
        }
    }
}


void UIGrid::ClearCharacters( void )
{
    for_each( mTiles.begin(), mTiles.end(), mem_fun_ref( &UITile::RemoveCharacter ) );
    for_each( mMiniMap.begin(), mMiniMap.end(), mem_fun_ref( &UITile::RemoveCharacter ) );
}


//============================= ACCESS     ===================================

void UIGrid::SetLevel( Level* level )
{
    mLevel = level;
}

void UIGrid::SetCharWindow( UICharWindow* charWindow)
{
    mCharWindow = charWindow;
}

//============================= INQUIRY    ===================================

const bool UIGrid::ValidPoint( const Point & p ) const
{
    int x = p.GetX();
    int y = p.GetY();

    if ( (x<mNumColumns) && (y<mNumRows) && (x>=0) && (y>=0) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

const bool UIGrid::HasCharacter( const Point & p )
{
    int index = FindIndex(p);
    if( index != -1 )
    {
        //UITile* temp =
        return mTiles[index].HasCharacter();
    }
    else
    {
        return false;
    }
}

void UIGrid::UpdateCursor(void)
{
    // This function assumes no cursor offset (needs to be mCursorOffset for it to work properly)
    Point mCursorOffset(0,0);

    if (ValidPoint(mCursorPos))
    {

        // Update cursor position
        mCursor->SetPos( mTiles[ FindIndex(mCursorPos) ].GetPos() + mCursorOffset);

        // Find whether current point has character
        const vector<Character*> & everyoneVector = mLevel->GetEveryone();
        vector<Character*>::const_iterator iter = everyoneVector.begin();
        Character *tempChar = NULL;

        while ( (iter != everyoneVector.end()) && (tempChar==NULL) )
        {

             if((*iter)->GetPoint() == mCursorPos)
             {
                   tempChar = (*iter);
             }
            iter++;

        }

        // Put that character on display
        if (mCharWindow)
        {
            if (tempChar!=NULL)
            {
                mCharWindow->SetCharacter(tempChar);
            }
            else
            {
                mCharWindow->ClearCharacter();
            }
        }
    }
    else
    {
        // Something is seriously wrong....the cursor has gone off the screen
    }


}

void UIGrid::Initialize()
{
    if(mLevel == NULL)
    {
        return;
    }
    // Add all elements
    SDL_Surface *sample = ResourceManager::GetInstance()->LoadTexture("defaultTile.png");
    mMap = mLevel->GetMap();
    mNumColumns = mMap->GetMaxX();
    mNumRows = mMap->GetMaxY();
    if( sample )
    {
        mTileHeight = sample->h;
        mTileWidth = sample->w;
    }
    mTotalTileOffset = mTileWidth;
    const TileVec & storage = mMap->GetTiles();

    mTiles.reserve( 100 );
    mMiniMap.reserve( 100 );

    for( TileConstItr iter = storage.begin(); iter != storage.end(); ++iter )
    {
        mTiles.push_back( UITile( (*iter), mapOffset ) );
        mMiniMap.push_back( UITile( iter->GetPoint(), MINIMAPIMAGE_PREFIX + iter->GetPic(), miniMapOffset ) );
    }

    // Assign self an image
    // ----------------------------------------------------
    mElementImage = ResourceManager::GetInstance()->LoadTexture("testMenu.png");

    // Assign Cursor its place
    // ----------------------------------------------------
    mMaxCursorPos.Set(mNumColumns - 1, mNumRows - 1);
    mCursorStart = mTileStart + Point( -mTileOffset, -mTileOffset);
    mCursor = new UIImage("tileCursor.png");
    mCursor->SetPos( mCursorStart );


}


/////////////////////////////// PROTECTED  ///////////////////////////////////


const int UIGrid::FindIndex( const int x, const int y ) const
{
    if (ValidPoint( Point(x,y) ))
    {
        return y + mNumRows*x;
    }
    else
    {
        return -1;
    }
}

const int UIGrid::FindIndex( const Point & p ) const
{
    if (ValidPoint( p ))
    {
        return p.GetY() + mNumRows*p.GetX();
    }
    else
    {
        return -1;
    }
}



SDL_Surface* UIGrid::GetClassSurface( Character* c, const CHARACTER_SURFACE_GROUP group, const bool isMiniMap )
{
    std::string temp = c->GetCharacterClassName();

    if( group == G_PARTY )
    {
        if( isMiniMap )
        {
            return ResourceManager::GetInstance()->LoadTexture( "mini_party.png" );
        }
        else if ( temp == "Archer" )
        {
            return ResourceManager::GetInstance()->LoadTexture( "archer_party.png" );
        }
        else if (temp=="Knight")
        {
            return ResourceManager::GetInstance()->LoadTexture( "knight_party.png");
        }
        else if (temp=="Healer")
        {
            return ResourceManager::GetInstance()->LoadTexture( "healer_party.png");
        }
        else if (temp=="Mage")
        {
            return ResourceManager::GetInstance()->LoadTexture( "mage_party.png");
        }
        else
        {
            LogWarning( string("Class surface requested for unknown character type: ") + temp );
            // you screwed up
            return ResourceManager::GetInstance()->LoadTexture( "charTile.png");
        }
    }
    else if( group == G_ENEMY )
    {
        if( isMiniMap )
        {
            return ResourceManager::GetInstance()->LoadTexture( "mini_enemy.png" );
        }
        else if (temp=="Archer")
        {
            return ResourceManager::GetInstance()->LoadTexture( "archer_enemy.png");
        }
        else if (temp=="Knight")
        {
            return ResourceManager::GetInstance()->LoadTexture( "knight_enemy.png");
        }
        else if (temp=="Healer")
        {
            return ResourceManager::GetInstance()->LoadTexture( "healer_enemy.png");
        }
        else if (temp=="Mage")
        {
            return ResourceManager::GetInstance()->LoadTexture( "mage_enemy.png");
        }
        else
        {
            LogWarning( string("Class surface requested for unknown character type: ") + temp );
            // you screwed up
            return ResourceManager::GetInstance()->LoadTexture( "charTile.png");
        }
    }
    else if( group == G_EXHAUSTED )
    {
        if( isMiniMap )
        {
            const CharacterPtrVec & enemies = mLevel->GetEnemies();
            const CharacterPtrVec & party = mLevel->GetParty();

            if( find( enemies.begin(), enemies.end(), c ) != enemies.end() )
            {
                return ResourceManager::GetInstance()->LoadTexture( MINIMAP_ENEMY_IMG );
            }
            else if( find( party.begin(), party.end(), c ) != party.end() )
            {
                return ResourceManager::GetInstance()->LoadTexture( MINIMAP_PARTY_IMG );
            }
            else
            {
                tacAssert( false ); // Should never get here in practice
                return ResourceManager::GetInstance()->LoadTexture( "mini_defaultTile.png");
            }
        }
        else if (temp=="Archer")
        {
            return ResourceManager::GetInstance()->LoadTexture( "archer_exhaust.png");
        }
        else if (temp=="Knight")
        {
            return ResourceManager::GetInstance()->LoadTexture( "knight_exhaust.png");
        }
        else if (temp=="Healer")
        {
            return ResourceManager::GetInstance()->LoadTexture( "healer_exhaust.png");
        }
        else if (temp=="Mage")
        {
            return ResourceManager::GetInstance()->LoadTexture( "mage_exhaust.png");
        }
        else
        {
            LogWarning( string("Class surface requested for unknown character type: ") + temp );
            // you screwed up
            return ResourceManager::GetInstance()->LoadTexture( "charTile.png");
        }
    }
    else
    {
        return NULL;
    }

}

void UIGrid::DrawHealthIndicationers( Character* attacker, Character* defender )
{
    if( attacker != NULL && defender != NULL )
    {
        char dmgTxt[8];
        if( attacker->GetCharacterClassName() == "Healer" )
        {
            // Draw an image to indicate action is being taken
            sprintf( dmgTxt, " %i", mLevel->GetLastHealed() );
            UIText* amountHealed = new UIText( dmgTxt, 22, 255, 255, 0 );
            UIText* amountHealedShadow = new UIText( dmgTxt, 22, 0, 0, 0 );
            UIText* amountHealedShadow2 = new UIText( dmgTxt, 22, 0, 0, 0 );
            UIText* amountHealedShadow3 = new UIText( dmgTxt, 22, 0, 0, 0 );
            UIText* amountHealedShadow4 = new UIText( dmgTxt, 22, 0, 0, 0 );

            Point toDrawAt( defender->GetPoint().GetX() * mTileWidth + mTileWidth/2, defender->GetPoint().GetY() * mTileHeight + mTileHeight/8 );
            amountHealed->SetPos( toDrawAt );
            amountHealedShadow->SetPos( toDrawAt + Point(2,0) );
            amountHealedShadow2->SetPos( toDrawAt + Point(-2,0) );
            amountHealedShadow3->SetPos( toDrawAt + Point(0,2) );
            amountHealedShadow4->SetPos( toDrawAt + Point(0,-2) );

            Uint32 timeToDraw = SDL_GetTicks() + INDICATER_DELAY;
            SDLRenderer::GetInstance()->AddToTempRenderQueue( amountHealedShadow, timeToDraw );
            SDLRenderer::GetInstance()->AddToTempRenderQueue( amountHealedShadow2, timeToDraw );
            SDLRenderer::GetInstance()->AddToTempRenderQueue( amountHealedShadow3, timeToDraw );
            SDLRenderer::GetInstance()->AddToTempRenderQueue( amountHealedShadow4, timeToDraw );
            SDLRenderer::GetInstance()->AddToTempRenderQueue( amountHealed, timeToDraw );
        }
        else
        {
            // Draw an image to indicate action is being taken
            sprintf( dmgTxt, "%i", mLevel->GetLastDamageInflicted() );
            UIText* damageInflicted = new UIText( dmgTxt, 22, 255, 0, 0 );
            UIText* damageInflictedShadow = new UIText( dmgTxt, 22, 0, 0, 0 );
            UIText* damageInflictedShadow2 = new UIText( dmgTxt, 22, 0, 0, 0 );
            UIText* damageInflictedShadow3 = new UIText( dmgTxt, 22, 0, 0, 0 );
            UIText* damageInflictedShadow4 = new UIText( dmgTxt, 22, 0, 0, 0 );

            Point toDrawInflictedAt( defender->GetPoint().GetX() * mTileWidth + mTileWidth/2, defender->GetPoint().GetY() * mTileHeight + mTileHeight/8 );
            damageInflicted->SetPos( toDrawInflictedAt );
            damageInflictedShadow->SetPos( toDrawInflictedAt + Point(2,0) );
            damageInflictedShadow2->SetPos( toDrawInflictedAt + Point(-2,0) );
            damageInflictedShadow3->SetPos( toDrawInflictedAt + Point(0,2) );
            damageInflictedShadow4->SetPos( toDrawInflictedAt + Point(0,-2) );

            Uint32 timeToDraw = SDL_GetTicks() + INDICATER_DELAY;
            SDLRenderer::GetInstance()->AddToTempRenderQueue( damageInflictedShadow, timeToDraw );
            SDLRenderer::GetInstance()->AddToTempRenderQueue( damageInflictedShadow2, timeToDraw );
            SDLRenderer::GetInstance()->AddToTempRenderQueue( damageInflictedShadow3, timeToDraw );
            SDLRenderer::GetInstance()->AddToTempRenderQueue( damageInflictedShadow4, timeToDraw );
            SDLRenderer::GetInstance()->AddToTempRenderQueue( damageInflicted, timeToDraw );

            if( mLevel->GetLastDamageTaken() != 0 && mLevel->GetLastAttackerLevelUp() == 0 )
            {
                sprintf( dmgTxt, "%i", mLevel->GetLastDamageTaken() );
                UIText* damageTaken = new UIText( dmgTxt, 22, 255, 0, 0 );
                UIText* damageTakenShadow = new UIText( dmgTxt, 22, 0, 0, 0 );
                UIText* damageTakenShadow2 = new UIText( dmgTxt, 22, 0, 0, 0 );
                UIText* damageTakenShadow3 = new UIText( dmgTxt, 22, 0, 0, 0 );
                UIText* damageTakenShadow4 = new UIText( dmgTxt, 22, 0, 0, 0 );

                Point toDrawTakenAt( attacker->GetPoint().GetX() * mTileWidth + mTileWidth/2, attacker->GetPoint().GetY() * mTileHeight + mTileHeight/8 );
                damageTaken->SetPos( toDrawTakenAt );
                damageTakenShadow->SetPos( toDrawTakenAt + Point(2,0) );
                damageTakenShadow2->SetPos( toDrawTakenAt + Point(-2,0) );
                damageTakenShadow3->SetPos( toDrawTakenAt + Point(0,2) );
                damageTakenShadow4->SetPos( toDrawTakenAt + Point(0,-2) );

                timeToDraw = SDL_GetTicks() + INDICATER_DELAY;
                SDLRenderer::GetInstance()->AddToTempRenderQueue( damageTakenShadow, timeToDraw );
                SDLRenderer::GetInstance()->AddToTempRenderQueue( damageTakenShadow2, timeToDraw );
                SDLRenderer::GetInstance()->AddToTempRenderQueue( damageTakenShadow3, timeToDraw );
                SDLRenderer::GetInstance()->AddToTempRenderQueue( damageTakenShadow4, timeToDraw );
                SDLRenderer::GetInstance()->AddToTempRenderQueue( damageTaken, timeToDraw );
            }
        }
    }
}

inline void UIGrid::DoLoseOrWin( Level* mLevel )
{
    if( mLevel )
    {
        if (mLevel->GetLoseCondition())
        {
            SDL_Delay( 1000 );
            UIManager::GetInstance()->PushLayout("Lose");
        }
        else if( mLevel->GetWinCondition() )
        {
            SDL_Delay( 1000 );
            UIManager::GetInstance()->PushLayout("Win");
        }
    }
}

/////////////////////////////// PRIVATE    ///////////////////////////////////
