/**
 * File: UIGrid.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 * Karl Schmidt, February 11 2007   | Added checks to prevent crashing if textures are not loaded
 * Andrew Osborne, February 11 2007 | Added Destructor and documentaton
 * Andrew Osborne, February 12 2007 | Setup characters, allowed movement, created a number of helper functions
 * Karl Schmidt, February 13 2007   | Reworked destructor, noted current bug and temporary work-around
 * Karl Schmidt, February 13 2007   | Modified hasCharacter to return a value in all cases (fixes a warning, safer)
 * Mike Malyuk,  February 14 2007   | Modified pretty much everything. Stopped newing of tiles, waste of space.
 * Mike Malyuk,  February 14 2007   | Fixed obscure bug where friend standing on tile where opponent died would be
 *                                    cleared from screen if attacker clicked on it. Also allowed your character to die
 *                                    Knight on Knight
 * Karl Schmidt, February 14 2007   | Updated function capitalization, block style, typedefs, refs
 * Mike Malyuk,  February 14 2007   | Added function to show exhausted state, refreshes on turn.
 * Mike Malyuk,  February 14 2007   | Added another check for partyexhaustion, move point far enough away to not be an issue.
 * Karl Schmidt, February 15 2007   | Added action indication support for attacking/healing
 */
#include "UIGrid.h"                                // class implemented
#include "UITile.h"
#include "UICursor.h"
#include "UIManager.h"
#include "InputManager.h"
#include "GameEngine/Level.h"
#include <Logger.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

UIGrid::UIGrid()
: mNumRows( 10 ), mNumColumns( 10 ), mCursorPos( Point(0,0) ), mTileStart( Point(10,10) ), mTileOffset( 2 )
{
    // Add all elements
    SDL_Surface *sample = ResourceManager::GetInstance()->LoadTexture("defaultTile.bmp");

    if( sample )
    {
        mTileHeight = sample->h;
        mTileWidth = sample->w;
    }

    int i, j;



    // Set Tiles in place
    // --------------------------------------------------
    int startXoffset = mTileStart.GetX();
    int startYoffset = mTileStart.GetY();
    mTotalTileOffset = mTileOffset + mTileWidth;

    UITile temp;

    for (i=0; i<mNumColumns; i++)
    {
        //tiles[i] = new UITile[mNumRows];
        for (j=0; j<mNumRows; j++)
        {
            temp = UITile();
            temp.SetPos( Point(startXoffset + i*(mTotalTileOffset), startYoffset + j*(mTotalTileOffset) ) );
            //tiles[i][j] = temp;
            mTiles.push_back( temp );
        }
    }

    // Assign self an image
    // ----------------------------------------------------
    mElementImage = ResourceManager::GetInstance()->LoadTexture("testMenu.bmp");

    // Assign Cursor its place
    // ----------------------------------------------------
    mMaxCursorPos.Set(mNumColumns - 1, mNumRows - 1);
    mCursorStart = mTileStart + Point( -mTileOffset, -mTileOffset);
    mCursor = new UICursor("tileCursor.bmp", "");
    mCursor->SetPos( mCursorStart );

    // Retrieve Game Engine
    //mGameEngine = GameEngine::GetInstance();
    //mGameEngine = NULL;

}// UIGrid


UIGrid::~UIGrid()
{
    // Release Tiles
    /*for( UITileItr i = mTiles.begin(); i != mTiles.end(); ++i )
    {
        if( *i )
        {
            delete *i;
        }
    }*/

    if( mCursor )
    {
        delete mCursor;
        mCursor = NULL;
    }

    // Move Range
    /*for( UIImageItr i = mImageMoveRange.begin(); i != mImageMoveRange.end(); ++i )
    {
        if( *i )
        {
            // EXPLICITLY FINDING POINTERS THAT EXIST IN THE OTHER VECTOR THAT DELETE'S IT'S
            // ELEMENTS IN THE FOR LOOP BELOW THIS ONE
            // WITHOUT DOING THIS THE GAME WILL CRASH IN SOME CASES, ANDREW PLEASE FIND OUT
            // WHY THESE VECTORS ARE ENDING UP WITH THE SAME POINTERS IN THEM SO THIS CHECKING
            // CODE CAN BE REMOVED
            UIImageItr dupPtrItr = find( mImageAttackRange.begin(), mImageAttackRange.end(), *i );
            if( dupPtrItr != mImageAttackRange.end() )
            {
                mImageAttackRange.erase( dupPtrItr );
            }
            delete *i;
        }
    }*/

    // Attack Range
    /*for( UIImageItr i = mImageAttackRange.begin(); i != mImageAttackRange.end(); ++i )
    {
        if( *i )
        {
            delete *i;
        }
    }*/

}// ~UIGrid


//============================= OPERATORS ====================================



//============================= OPERATIONS ===================================

void UIGrid::RenderSelf(SDL_Surface* destination)
{
    if( mElementImage )
    {
        // The menu must be rendered first
        //SDLRenderer::GetInstance()->DrawImageAt(mElementImage, mPos.GetX(), mPos.GetY(), mElementImage->w, mElementImage->h, destination);
    }

    // Moveable/Attackable Ranges are rendered first
    int curState = mLevel->ReturnState();
    UIImageItr iIter;

    if (curState==1)
    {
        // View Moveable Tiles
        iIter = mImageMoveRange.begin();
        while (iIter!=mImageMoveRange.end())
        {
            (*iIter).RenderSelf(destination);
            iIter++;
        }
    }
    else if (curState==2)
    {
        // Vies Attackable Tiles
        iIter = mImageAttackRange.begin();
        while (iIter!=mImageAttackRange.end())
        {
            (*iIter).RenderSelf(destination);
            iIter++;
        }
    }

    // Cursor is rendered second
    mCursor->RenderSelf(destination);

    // Tiles are rendered third
    for ( UITileItr iter = mTiles.begin(); iter!=mTiles.end(); ++iter )
    {
        (*iter).RenderSelf(destination);
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
                newPos.Set(mCursorStart.GetX() + mTotalTileOffset*mCursorPos.GetX(), mCursorStart.GetY() + mTotalTileOffset*mCursorPos.GetY() );
                mCursor->SetPos( newPos );
            }
            //cursor->moveUp()
            break;
        case InputManager::DOWN:
            if (mCursorPos.GetY()<mMaxCursorPos.GetY())
            {
                mCursorPos = mCursorPos + Point(0,1);
                newPos.Set(mCursorStart.GetX() + mTotalTileOffset*mCursorPos.GetX(), mCursorStart.GetY() + mTotalTileOffset*mCursorPos.GetY() );
                mCursor->SetPos( newPos );
            }
            break;
        case InputManager::LEFT:
            // Move cursor up
            if (mCursorPos.GetX()>0)
            {
                mCursorPos = mCursorPos + Point(-1,0);
                newPos.Set(mCursorStart.GetX() + mTotalTileOffset*mCursorPos.GetX(), mCursorStart.GetY() + mTotalTileOffset*mCursorPos.GetY() );
                mCursor->SetPos( newPos );
            }
            //cursor->moveUp()
            break;
        case InputManager::RIGHT:
            if (mCursorPos.GetX()<mMaxCursorPos.GetX())
            {
                mCursorPos = mCursorPos + Point(1,0);
                newPos.Set(mCursorStart.GetX() + mTotalTileOffset*mCursorPos.GetX(), mCursorStart.GetY() + mTotalTileOffset*mCursorPos.GetY() );
                mCursor->SetPos( newPos );
            }
            break;
        case InputManager::CONFIRM:
            ConfirmFunction(mCursorPos);
            break;
        case InputManager::CANCEL:
            // Will be handled later
            // Add a request to confirm quiting??
            break;
        default:
            break;

    }
}

void UIGrid::ConfirmFunction( const Point & p )
{

    //UILayout *tempLayout = UIManager::GetInstance()->getLayout("BattleScreen");
    //Level *mLevel = NULL;


    int curState = mLevel->ReturnState();
    bool validAction = false;

    Character* tempChar;
    switch(curState)
    {
        case 0:


            // Attempt to select character
            // ------------------------------------------
            tempChar = mLevel->OnSelect(p);

            // Step 1 - check to see if selected character
            // ===============
            if (tempChar==NULL) {
                // Unsuccessful, do nothing

            }
            else
            {

                // Step 2 - select Character
                // =============
                mCurCharacter = tempChar;

                // Step 3 - prepare screen/UI for moveable range
                // ==============

                //mMoveRange = mLevel->GetMoveArea();
                //mMoveRange = refineMoveArea(mMoveRange);
                //addMoveableRange(moveArea);

                // Successful, display move range
                ClearMoveableRange();
                ClearAttackRange();

                PointVec moveArea = mLevel->GetMoveArea();
                AddMoveableRange( moveArea );
                mMoveRange = moveArea;
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

            // Check if move was cancelled
            if (p==mCurCharacter->GetPoint())
            {

                Character* test = mLevel->OnSelect(p);
                ClearMoveableRange();
                ClearAttackRange();
                AddAttackRange( mLevel->GetAttackArea() );
                if(test == NULL)
                {
                    RemoveCharacter(p);
                    AddExhaustedCharacter(mCurCharacter);
                }

            }
            else
            {

                // Check to see if valid spot for movement
                for ( PointItr iter = mMoveRange.begin(); iter!=mMoveRange.end(); ++iter )
                {

                    if (p==(*iter))
                    {
                        validAction = true;
                    }
                }

                if ( validAction )
                {
                    // remove icon from old spot
                    RemoveCharacter( mCurCharacter->GetPoint() );

                    // add icon to new spot
                    Point old = mCurCharacter->GetPoint();
                    mCurCharacter->Move(p);
                    AddPartyCharacter( mCurCharacter );
                    mCurCharacter->Move(old);
                    Character* test = mLevel->OnSelect(p);
                    ClearMoveableRange();
                    if(test == NULL)
                    {
                        RemoveCharacter(p);
                        AddExhaustedCharacter(mCurCharacter);
                    }
                    // Prep screen for attack
                    ClearAttackRange();
                    AddAttackRange( mLevel->GetAttackArea() );

                }
                else
                {
                    // do nothing
                    // maybe display message later....
                }
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
            /*if ( validAction ) {
                // remove icon from old spot
                RemoveCharacter( mCurCharacter->GetPoint() );

                // add icon to new spot
                mCurCharacter->Move(p);
                addCharacter( mCurCharacter );

            } else {
                // do nothing
                // maybe display message later....
            }*/
            // now check if person is there
            if(mLevel->OnSelect(p) == NULL)
            {
            	// Draw an image to indicate action is being taken
                UIImage* indicator = new UIImage( "testIndicator.bmp" );
                Point toDrawAt( mCurCharacter->GetPoint().GetX() * mTileWidth, mCurCharacter->GetPoint().GetY() * mTileHeight );
                indicator->SetPos( toDrawAt );
                SDLRenderer::GetInstance()->AddToTempRenderQueue( indicator, SDL_GetTicks() + 400 );
                RemoveCharacter(mCurCharacter->GetPoint());
                AddExhaustedCharacter(mCurCharacter);
            }
            if(mLevel->PointHasPerson(p) != NULL && mCurCharacter != NULL && mCurCharacter->GetPoint() != p)
            {
                RemoveCharacter(p);
                mLevel->PointHasPerson(p)->Move(Point(-5,-5));
            }
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

            ClearAttackRange();
            if(mLevel->PointHasPerson(p) == NULL)
            {
                AddAttackRange( mLevel->GetAttackArea() );
            }

            /*if ( (validAction) && (target!=NULL) )
            {

                // no

            }*/

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
            tempChar = mLevel->OnAISelect(p);

            // Step 1 - check to see if selected character
            // ===============
            if (tempChar==NULL) {
                // Unsuccessful, do nothing

            }
            else
            {

                // Step 2 - select Character
                // =============
                mCurCharacter = tempChar;

                // Step 3 - prepare screen/UI for moveable range
                // ==============

                //mMoveRange = mLevel->GetMoveArea();
                //mMoveRange = refineMoveArea(mMoveRange);
                //addMoveableRange(moveArea);

                // Successful, display move range
                ClearMoveableRange();
                ClearAttackRange();

                PointVec moveArea = mLevel->GetMoveArea();
                AddMoveableRange( moveArea );
                mMoveRange = moveArea;
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
            if (p==mCurCharacter->GetPoint())
            {

                Character* test = mLevel->OnAISelect(p);
                ClearMoveableRange();
                ClearAttackRange();
                AddAttackRange( mLevel->GetAttackArea() );
                if(test == NULL)
                {
                    RemoveCharacter(p);
                    AddExhaustedCharacter(mCurCharacter);
                }

            }
            else
            {

                // Check to see if valid spot for movement
                for ( PointItr iter = mMoveRange.begin(); iter!=mMoveRange.end(); ++iter )
                {

                    if (p==(*iter))
                    {
                        validAction = true;
                    }
                }

                if ( validAction )
                {
                    // remove icon from old spot
                    RemoveCharacter( mCurCharacter->GetPoint() );

                    // add icon to new spot
                    Point old = mCurCharacter->GetPoint();
                    mCurCharacter->Move(p);
                    AddEnemyCharacter( mCurCharacter );
                    mCurCharacter->Move(old);
                    Character* test = mLevel->OnAISelect(p);
                    ClearMoveableRange();
                    if(test == NULL)
                    {
                        RemoveCharacter(p);
                        AddExhaustedCharacter(mCurCharacter);
                    }
                    // Prep screen for attack
                    ClearAttackRange();
                    AddAttackRange( mLevel->GetAttackArea() );

                }
                else
                {
                    // do nothing
                    // maybe display message later....
                }
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
            /*if ( validAction ) {
                // remove icon from old spot
                RemoveCharacter( mCurCharacter->GetPoint() );

                // add icon to new spot
                mCurCharacter->Move(p);
                addCharacter( mCurCharacter );

            } else {
                // do nothing
                // maybe display message later....
            }*/
            // now check if person is there
            Character* test = mLevel->OnAISelect(p);
            if(test == NULL)
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

            ClearAttackRange();
            if(part == NULL)
            {
                AddAttackRange( mLevel->GetAttackArea() );
            }

            /*if ( (validAction) && (target!=NULL) )
            {

                // no

            }*/

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

void UIGrid::AddRange( const PointVec & pointRange, const UIImagePtrVec & elementRange)
{

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
            mImageAttackRange.push_back( UIImage("yellowCursor.bmp") );
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


void UIGrid::AddMoveableRange( PointVec moveRange )
{

    //AddRange( moveRange, mImageMoveRange);

    // If more new Blue tiles/cursors are needed more are created

    for ( PointItr i = moveRange.begin(); i != moveRange.end(); ++i )
    {
        if(ValidPoint((*i)))
        {
            mImageMoveRange.push_back( UIImage("blueCursor.bmp") );
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

    elementIter = mImageMoveRange.begin();

    for ( PointItr i=moveRange.begin(); i!=moveRange.end(); ++i )
    {
        gridPoint = (*i);
        if ( (ValidPoint(gridPoint)) && ( (!HasCharacter(gridPoint)) || (gridPoint==charPoint) ) )
        {
            cursorPos.Set( mCursorStart.GetX() + gridPoint.GetX()*mTotalTileOffset, mCursorStart.GetY() + gridPoint.GetY()*(mTotalTileOffset) );
            (*elementIter).SetPos( cursorPos );
            (*elementIter).SetVisible( true );
            elementIter++;
        }
    }

}




//============================= ACCESS     ===================================

void UIGrid::SetLevel( Level* level )
{
    mLevel = level;
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
            return ResourceManager::GetInstance()->LoadTexture("archer_party.bmp");
        }
        else if (temp=="Knight")
        {
            return ResourceManager::GetInstance()->LoadTexture("knight_party.bmp");
        }
        else if (temp=="Healer")
        {
            return ResourceManager::GetInstance()->LoadTexture("healer_party.bmp");
        }
        else if (temp=="Mage")
        {
            return ResourceManager::GetInstance()->LoadTexture("mage_party.bmp");
        }
        else
        {
            LogWarning( string("Class surface requested for unknown character type: ") + temp );
            // you screwed up
            return ResourceManager::GetInstance()->LoadTexture("charTile.bmp");
        }
    }
    else if(group == "Enemy")
    {
        if (temp=="Archer")
        {
            return ResourceManager::GetInstance()->LoadTexture("archer_enemy.bmp");
        }
        else if (temp=="Knight")
        {
            return ResourceManager::GetInstance()->LoadTexture("knight_enemy.bmp");
        }
        else if (temp=="Healer")
        {
            return ResourceManager::GetInstance()->LoadTexture("healer_enemy.bmp");
        }
        else if (temp=="Mage")
        {
            return ResourceManager::GetInstance()->LoadTexture("mage_enemy.bmp");
        }
        else
        {
            LogWarning( string("Class surface requested for unknown character type: ") + temp );
            // you screwed up
            return ResourceManager::GetInstance()->LoadTexture("charTile.bmp");
        }
    }
    else if(group == "Exhausted")
    {
        if (temp=="Archer")
        {
            return ResourceManager::GetInstance()->LoadTexture("archer_exhaust.bmp");
        }
        else if (temp=="Knight")
        {
            return ResourceManager::GetInstance()->LoadTexture("knight_exhaust.bmp");
        }
        else if (temp=="Healer")
        {
            return ResourceManager::GetInstance()->LoadTexture("healer_exhaust.bmp");
        }
        else if (temp=="Mage")
        {
            return ResourceManager::GetInstance()->LoadTexture("mage_exhaust.bmp");
        }
        else
        {
            LogWarning( string("Class surface requested for unknown character type: ") + temp );
            // you screwed up
            return ResourceManager::GetInstance()->LoadTexture("charTile.bmp");
        }
    }
    else
    {
        return NULL;
    }

}

PointVec UIGrid::RefineMoveRange( PointVec moveRange )
{
    PointItr pointIter = moveRange.begin();
    PointVec finalVtr;
    Point gridPoint;
    Point charPoint;
    if (mCurCharacter!=NULL)
    {
        charPoint = mCurCharacter->GetPoint();
    }


    while (pointIter!=moveRange.end())
    {
        gridPoint = (*pointIter);

        if ( (ValidPoint(gridPoint)) && ( (!HasCharacter(gridPoint)) || (gridPoint==charPoint) ) )
        {
            finalVtr.push_back( gridPoint );
        }
        pointIter++;
    }

    return finalVtr;

}

/////////////////////////////// PRIVATE    ///////////////////////////////////
