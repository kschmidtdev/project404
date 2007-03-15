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
 */

#include <util.h>

#include "UIGrid.h"                                // class implemented
#include "UITile.h"
//#include "UICursor.h"
#include "UIManager.h"
#include "InputManager.h"
#include "GameEngine/Level.h"
#include <Logger.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIGrid::UIGrid()
: mNumRows( 10 ), mNumColumns( 10 ), mCursorPos( Point(0,0) ), mTileStart( Point(10,10) ), mTileOffset( 0 ),
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
        (*iter).RenderSelf(destination);
    }

    // Movement ranges are rendered second (middle)
    int curState = mLevel->ReturnState();
    UIImageItr iIter;
    if( curState == Level::MOVE )
    {
        // View Moveable Tiles
        iIter = mImageMoveRange.begin();
        while (iIter!=mImageMoveRange.end())
        {
            (*iIter).RenderSelf(destination);
            iIter++;
        }
    }
    else if( curState == Level::ATTACK )
    {
        // View Attackable Tiles
        iIter = mImageAttackRange.begin();
        while (iIter!=mImageAttackRange.end())
        {
            (*iIter).RenderSelf(destination);
            iIter++;
        }
    }

    // Cursor is rendered last (top)
    mCursor->RenderSelf(destination);
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
        case 0:


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
            break;

        case 1:

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

                    }

                    // Prep screen for attack
                    else
                    {
                        AddAttackRange( mLevel->GetAttackArea() );
                    }
                    ClearMoveableRange();
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
                if (mLevel->GetWinCondition())
                {
                    UIManager::GetInstance()->PushLayout("Win");
                }
            }
            break;

        case 2:
            // Attempting to attack
            //------------------------------------------------------

            // Step 1 - check for valid attack point

            // Step 2 - check for self-clicked

            // Step 3 - Attack other character

            // Step 4 - run end turn check (is target dead, is enememy dead, is party exhausted)

            // Step 5 - Initialize next turn

            // check to see if attack-range is valid

            // now check if person is there
            mLevel->OnSelect(p);
            if(mLevel->ReturnState() == 0 || mLevel->ReturnState() == 3)
            {
            	// Draw an image to indicate action is being taken
                UIImage* indicator = new UIImage( "testIndicator.png" );
                Point toDrawAt( mCurCharacter->GetPoint().GetX() * mTileWidth, mCurCharacter->GetPoint().GetY() * mTileHeight );
                indicator->SetPos( toDrawAt );
                SDLRenderer::GetInstance()->AddToTempRenderQueue( indicator, SDL_GetTicks() + 400 );
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
            if (mLevel->GetWinCondition())
            {
                UIManager::GetInstance()->PushLayout("Win");
            }

            break;

        case 3:


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

            break;

        case 4:

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

                if (mLevel->GetLoseCondition())
                {
                    UIManager::GetInstance()->PushLayout("Lose");
                }
            }
            break;

        case 5:
            // Attempting to attack
            //------------------------------------------------------

            // Step 1 - check for valid attack point

            // Step 2 - check for self-clicked

            // Step 3 - Attack other character

            // Step 4 - run end turn check (is target dead, is enememy dead, is party exhausted)

            // Step 5 - Initialize next turn

            // check to see if attack-range is valid

            // now check if person is there
            mLevel->OnAISelect(p);

            if(mLevel->ReturnState() == 0 || mLevel->ReturnState() == 3)
            {
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
            if (mLevel->GetLoseCondition())
            {
                UIManager::GetInstance()->PushLayout("Lose");
            }

            break;

    }
}

void UIGrid::AddEnemyCharacter(Character *c)
{
    Point p = c->GetPoint();

    if ( ValidPoint(p)  )
    {
        int index = FindIndex( p );

         mTiles[index].AddCharacter( GetClassSurface(c, "Enemy"));
    }
}

void UIGrid::AddPartyCharacter(Character *c)
{
    Point p = c->GetPoint();

    if ( ValidPoint(p)  )
    {
        int index = FindIndex( p );

         mTiles[index].AddCharacter( GetClassSurface(c, "Party"));
    }
}

void UIGrid::AddExhaustedCharacter(Character *c)
{
    Point p = c->GetPoint();

    if ( ValidPoint(p)  )
    {
        int index = FindIndex( p );

         mTiles[index].AddCharacter( GetClassSurface(c, "Exhausted"));
    }
}

void UIGrid::RemoveCharacter( const Point & p)
{
    if ( ValidPoint(p) )
    {
        int index = FindIndex( p );
        mTiles[index].RemoveCharacter();
    }
}


void UIGrid::ClearMoveableRange(void)
{
    mImageMoveRange.clear();
}


void UIGrid::ClearAttackRange(void)
{
    mImageAttackRange.clear();
}

void UIGrid::AddAttackRange( PointVec attackRange )
{
    for ( PointItr i=attackRange.begin(); i!=attackRange.end(); ++i )
    {
        if(ValidPoint((*i)))
        {
            mImageAttackRange.push_back( UIImage("yellowCursor.png") );
        }
    }


    PointItr pointIter;
    UIImageItr elementIter;
    Point cursorPos;
    Point gridPoint;
    Point charPoint;
    if (mCurCharacter!=NULL)
    {
         charPoint = mCurCharacter->GetPoint();
    }

    elementIter = mImageAttackRange.begin();

    for ( PointItr i=attackRange.begin(); i!=attackRange.end(); ++i )
    {
        gridPoint = (*i);

        if ( (ValidPoint(gridPoint)))
        {
            cursorPos.Set( mCursorStart.GetX() + gridPoint.GetX()*mTotalTileOffset, mCursorStart.GetY() + gridPoint.GetY()*(mTotalTileOffset) );
            (*elementIter).SetPos( cursorPos );
            (*elementIter).SetVisible( true );
            elementIter++;
        }
    }


}


void UIGrid::AddMoveableRange( vector<Character*> everyone, vector<Character*> enemies, Character* you )
{

    mMovePoints = mMap->GetMovementRange(everyone, enemies, you);

    for ( PointItr i = mMovePoints.begin(); i != mMovePoints.end(); ++i )
    {
        mImageMoveRange.push_back( UIImage("blueCursor.png") );
    }


    PointItr pointIter;
    UIImageItr elementIter;
    Point cursorPos;
    Point gridPoint;
    Point charPoint;

    elementIter = mImageMoveRange.begin();

    for ( PointItr i=mMovePoints.begin(); i!=mMovePoints.end(); ++i )
    {
        gridPoint = (*i);
        cursorPos.Set( mCursorStart.GetX() + gridPoint.GetX()*mTotalTileOffset, mCursorStart.GetY() + gridPoint.GetY()*(mTotalTileOffset) );
        (*elementIter).SetPos( cursorPos );
        (*elementIter).SetVisible( true );
        elementIter++;
    }

}


void UIGrid::ClearCharacters( void )
{
    for (UITileItr iter = mTiles.begin(); iter !=mTiles.end(); ++iter)
    {
        (*iter).RemoveCharacter();
    }

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

bool UIGrid::ValidPoint( const Point & p )
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

bool UIGrid::HasCharacter( const Point & p )
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
        vector<Character*> everyoneVector = mLevel->GetEveryone();
        vector<Character*>::iterator iter = everyoneVector.begin();
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
    vector<Tile> storage = mMap->GetTiles();
    for(vector<Tile>::iterator iter = storage.begin(); iter != storage.end(); iter++)
    {
        mTiles.push_back(UITile((*iter)));
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


int UIGrid::FindIndex( const int x, const int y )
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

int UIGrid::FindIndex( const Point & p )
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



SDL_Surface* UIGrid::GetClassSurface(Character* c, const string group)
{
    string temp = c->GetClassName();
    if(group=="Party")
    {
        if (temp=="Archer")
        {
            return ResourceManager::GetInstance()->LoadTexture("archer_party.png");
        }
        else if (temp=="Knight")
        {
            return ResourceManager::GetInstance()->LoadTexture("knight_party.png");
        }
        else if (temp=="Healer")
        {
            return ResourceManager::GetInstance()->LoadTexture("healer_party.png");
        }
        else if (temp=="Mage")
        {
            return ResourceManager::GetInstance()->LoadTexture("mage_party.png");
        }
        else
        {
            LogWarning( string("Class surface requested for unknown character type: ") + temp );
            // you screwed up
            return ResourceManager::GetInstance()->LoadTexture("charTile.png");
        }
    }
    else if(group == "Enemy")
    {
        if (temp=="Archer")
        {
            return ResourceManager::GetInstance()->LoadTexture("archer_enemy.png");
        }
        else if (temp=="Knight")
        {
            return ResourceManager::GetInstance()->LoadTexture("knight_enemy.png");
        }
        else if (temp=="Healer")
        {
            return ResourceManager::GetInstance()->LoadTexture("healer_enemy.png");
        }
        else if (temp=="Mage")
        {
            return ResourceManager::GetInstance()->LoadTexture("mage_enemy.png");
        }
        else
        {
            LogWarning( string("Class surface requested for unknown character type: ") + temp );
            // you screwed up
            return ResourceManager::GetInstance()->LoadTexture("charTile.png");
        }
    }
    else if(group == "Exhausted")
    {
        if (temp=="Archer")
        {
            return ResourceManager::GetInstance()->LoadTexture("archer_exhaust.png");
        }
        else if (temp=="Knight")
        {
            return ResourceManager::GetInstance()->LoadTexture("knight_exhaust.png");
        }
        else if (temp=="Healer")
        {
            return ResourceManager::GetInstance()->LoadTexture("healer_exhaust.png");
        }
        else if (temp=="Mage")
        {
            return ResourceManager::GetInstance()->LoadTexture("mage_exhaust.png");
        }
        else
        {
            LogWarning( string("Class surface requested for unknown character type: ") + temp );
            // you screwed up
            return ResourceManager::GetInstance()->LoadTexture("charTile.png");
        }
    }
    else
    {
        return NULL;
    }

}

/////////////////////////////// PRIVATE    ///////////////////////////////////
