/**
 * File: UIGrid.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 * Karl Schmidt, February 11 2007 | Added checks to prevent crashing if textures are not loaded
 * Andrew osborne, February 11 2007 | Added Destructor and documentaton
 * Andrew Osborne, February 12 2007 | Setup characters, allowed movement, created a number of helper functions
 * Karl Schmidt, February 13 2007 | Reworked destructor, noted current bug and temporary work-around
 * Karl Schmidt, February 13 2007 | Modified hasCharacter to return a value in all cases (fixes a warning, safer)
 * Mike Malyuk,  February 14 2007 | Modified pretty much everything. Stopped newing of tiles, waste of space.
 */
#include "UIGrid.h"                                // class implemented
#include "UITile.h"
#include "UICursor.h"
#include "UIManager.h"
#include "InputManager.h"
#include "GameEngine/Level.h"

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
            temp.setPos( Point(startXoffset + i*(mTotalTileOffset), startYoffset + j*(mTotalTileOffset) ) );
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
    mCursor->setPos( mCursorStart );

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
    std::vector<UIImage>::iterator iIter;

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
    UITileItr iter;

    for (iter = mTiles.begin();
            iter!=mTiles.end(); iter++)
    {
        (*iter).RenderSelf(destination);
    }


}

void UIGrid::ProcessEvent( const InputManager::INPUTKEYS evt )
{
    // Come back to this later
    Point newPos;

    switch(evt) {
        case InputManager::UP:
            // Move cursor up
            if (mCursorPos.GetY()>0) {
                mCursorPos = mCursorPos + Point(0,-1);
                newPos.Set(mCursorStart.GetX() + mTotalTileOffset*mCursorPos.GetX(), mCursorStart.GetY() + mTotalTileOffset*mCursorPos.GetY() );
                mCursor->setPos( newPos );
            }
            //cursor->moveUp()
            break;
        case InputManager::DOWN:
            if (mCursorPos.GetY()<mMaxCursorPos.GetY()) {
                mCursorPos = mCursorPos + Point(0,1);
                newPos.Set(mCursorStart.GetX() + mTotalTileOffset*mCursorPos.GetX(), mCursorStart.GetY() + mTotalTileOffset*mCursorPos.GetY() );
                mCursor->setPos( newPos );
            }
            break;
        case InputManager::LEFT:
            // Move cursor up
            if (mCursorPos.GetX()>0) {
                mCursorPos = mCursorPos + Point(-1,0);
                newPos.Set(mCursorStart.GetX() + mTotalTileOffset*mCursorPos.GetX(), mCursorStart.GetY() + mTotalTileOffset*mCursorPos.GetY() );
                mCursor->setPos( newPos );
            }
            //cursor->moveUp()
            break;
        case InputManager::RIGHT:
            if (mCursorPos.GetX()<mMaxCursorPos.GetX()) {
                mCursorPos = mCursorPos + Point(1,0);
                newPos.Set(mCursorStart.GetX() + mTotalTileOffset*mCursorPos.GetX(), mCursorStart.GetY() + mTotalTileOffset*mCursorPos.GetY() );
                mCursor->setPos( newPos );
            }
            break;
        case InputManager::CONFIRM:
            confirmFunction(mCursorPos);
            break;
        case InputManager::CANCEL:
            // Will be handled later
            // Add a request to confirm quiting??
            break;
        default:
            break;

    }
}

void UIGrid::confirmFunction(Point p)
{

    //UILayout *tempLayout = UIManager::GetInstance()->getLayout("BattleScreen");
    //Level *mLevel = NULL;


    int curState = mLevel->ReturnState();
    printf("current State:%d\n", curState);
    printf("current Point: %d, %d:\n", p.GetX(), p.GetY() );

    bool validAction = false;

    Character* tempChar;
    switch(curState) {
        case 0:


            // Attempt to select character
            // ------------------------------------------
            printf("I'm just before onSelect\n");
            tempChar = mLevel->OnSelect(p);

            // Step 1 - check to see if selected character
            // ===============
            printf("I'm just before check\n");
            if (tempChar==NULL) {
                // Unsuccessful, do nothing
                printf("not a character\n");
            } else {

                // Step 2 - select Character
                // =============
                mCurCharacter = tempChar;
                printf("character selected\n");

                // Step 3 - prepare screen/UI for moveable range
                // ==============

                //mMoveRange = mLevel->GetMoveArea();
                //mMoveRange = refineMoveArea(mMoveRange);
                //addMoveableRange(moveArea);

                // Successful, display move range
                ClearMoveableRange();
                ClearAttackRange();

                vector<Point> moveArea = mLevel->GetMoveArea();
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
            if (p==mCurCharacter->GetPoint()) {

                mLevel->OnSelect(p);
                ClearMoveableRange();
                ClearAttackRange();
                AddAttackRange( mLevel->GetAttackArea() );


            } else {

                // Check to see if valid spot for movement
                std::vector<Point>::iterator iter;


                for (iter = mMoveRange.begin();
                        iter!=mMoveRange.end(); iter++)
                {
                    //printf("movePoint: %d, %d\n", (*iter).GetX(), (*iter).GetY() );
                    if (p==(*iter))
                        validAction = true;
                }

                //printf("Valid Move?:%d", validAction);

                if ( validAction ) {
                    // remove icon from old spot
                    removeCharacter( mCurCharacter->GetPoint() );

                    // add icon to new spot
                    Point old = mCurCharacter->GetPoint();
                    mCurCharacter->Move(p);
                    AddPartyCharacter( mCurCharacter );
                    mCurCharacter->Move(old);
                    mLevel->OnSelect(p);
                    ClearMoveableRange();
                    printf("curState after move:%d\n", mLevel->ReturnState());

                    // Prep screen for attack
                    ClearAttackRange();
                    AddAttackRange( mLevel->GetAttackArea() );

                } else {
                    // do nothing
                    // maybe display message later....
                }
            }
            if(mLevel->AllExhaustedParty())
            {
                mLevel->TakeTurn();
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
                removeCharacter( mCurCharacter->GetPoint() );

                // add icon to new spot
                mCurCharacter->Move(p);
                addCharacter( mCurCharacter );

            } else {
                // do nothing
                // maybe display message later....
            }*/
            // now check if person is there
            mLevel->OnSelect(p);
            Character* enemy = mLevel->PointHasPerson(p);
            if(enemy != NULL && mCurCharacter != NULL && mCurCharacter->GetPoint() != p)
            {
                removeCharacter(p);
            }


            //keep game running
            if(mLevel->AllExhaustedParty())
            {
                mLevel->TakeTurn();
            }
            ClearAttackRange();
            if(enemy == NULL)
            {
                AddAttackRange( mLevel->GetAttackArea() );
            }

            /*if ( (validAction) && (target!=NULL) )
            {

                // no

            }*/

            // Check for end game

            // Check for end turn

            break;

    }
}

void UIGrid::AddEnemyCharacter(Character *c)
{
    Point p = c->GetPoint();

    if ( validPoint(p)  )
    {
        int index = findIndex( p.GetX(), p.GetY() );
        //printf("index: %d, maxSize: %d\n", index, mTiles.size());
         mTiles[index].addCharacter( getClassSurface(c, "Enemy"));
    }
}

void UIGrid::AddPartyCharacter(Character *c)
{
    Point p = c->GetPoint();

    if ( validPoint(p)  )
    {
        int index = findIndex( p.GetX(), p.GetY() );
        //printf("index: %d, maxSize: %d\n", index, mTiles.size());
         mTiles[index].addCharacter( getClassSurface(c, "Party"));
    }
}

void UIGrid::removeCharacter(Point p) {

    int x = p.GetX();
    int y = p.GetY();

    if ( validPoint(p) )
    {
        int index = findIndex( x, y );
        mTiles[index].removeCharacter();
    }
}

void UIGrid::AddRange( vector<Point> pointRange, vector<UIImage*> elementRange)
{

    /*int numOfNeededRangeSquares = pointRange.size();
    int numOfCurrentRangeSqaures = elementRange.size();
    int i;
    bool isMoveRange;

    printf("needed: %d, current: %d\n", numOfNeededRangeSquares, numOfCurrentRangeSqaures);

    // If more new Blue tiles/cursors are needed more are created

    if (numOfNeededRangeSquares>numOfCurrentRangeSqaures) {
        // Need more squares
        //printf("before condition Statement\n");
        // Determing image file based on range
        string imageName;
        if (elementRange==mImageMoveRange)
        {
            imageName = "blueCursor.bmp";
            isMoveRange = true;
        }
        else if (elementRange==mImageAttackRange)
        {
            imageName = "yellowCursor.bmp";
            isMoveRange = false;

        } else {
            //printf("neither condition statisfied\n");
        }
        //printf("after condition statement\n");

        int newSquares = numOfNeededRangeSquares - numOfCurrentRangeSqaures;
        for (i=0; i<newSquares; i++)
            elementRange.push_back( new UIImage(imageName) );

    }

    std::vector<Point>::iterator pointIter;
    std::vector<UIImage*>::iterator elementIter;
    Point cursorPos;
    Point gridPoint;

    pointIter = pointRange.begin();

    elementIter = elementRange.begin();

    for (i=0; i<numOfNeededRangeSquares; i++)
    {
        gridPoint = (*pointIter);
        cursorPos.Set( mCursorStart.GetX() + gridPoint.GetX()*mTotalTileOffset, mCursorStart.GetY() + gridPoint.GetY()*(mTotalTileOffset) );
        (*elementIter)->setPos( cursorPos );
        (*elementIter)->setVisible( true );
        elementIter++;
        pointIter++;
    }

    // for remainder of unused elements, set invisible
    while (elementIter!=elementRange.end())
    {
        (*elementIter)->setVisible( false );
        elementIter++;
    }

    if (isMoveRange) {
        mImageMoveRange = elementRange;
    } else {
        mImageAttackRange = elementRange;
    }*/


}


void UIGrid::ClearMoveableRange(void) {

    mImageMoveRange.clear();
}


void UIGrid::ClearAttackRange(void) {

    mImageAttackRange.clear();

}

void UIGrid::AddAttackRange(vector<Point> attackRange)
{
        for (vector<Point>::iterator i=attackRange.begin(); i!=attackRange.end(); i++)
            if(validPoint((*i)))
            {
                mImageAttackRange.push_back( UIImage("yellowCursor.bmp") );
            }


    std::vector<Point>::iterator pointIter;
    std::vector<UIImage>::iterator elementIter;
    Point cursorPos;
    Point gridPoint;
    Point charPoint;
    if (mCurCharacter!=NULL)
    {
         charPoint = mCurCharacter->GetPoint();
    }

    elementIter = mImageAttackRange.begin();

    for (vector<Point>::iterator i=attackRange.begin(); i!=attackRange.end(); i++)
    {
        gridPoint = (*i);
        printf("grid point: %d, %d\n", gridPoint.GetX(), gridPoint.GetY() );
        if ( (validPoint(gridPoint)))
        {
            cursorPos.Set( mCursorStart.GetX() + gridPoint.GetX()*mTotalTileOffset, mCursorStart.GetY() + gridPoint.GetY()*(mTotalTileOffset) );
            (*elementIter).setPos( cursorPos );
            (*elementIter).setVisible( true );
            elementIter++;
        }
    }
    cout<< mImageAttackRange.size() << endl;

}


void UIGrid::AddMoveableRange(vector<Point> moveRange)
{

    //AddRange( moveRange, mImageMoveRange);

    // If more new Blue tiles/cursors are needed more are created

        for (vector<Point>::iterator i=moveRange.begin(); i!=moveRange.end(); i++)
            if(validPoint((*i)))
            {
                mImageMoveRange.push_back( UIImage("blueCursor.bmp") );
            }


    std::vector<Point>::iterator pointIter;
    std::vector<UIImage>::iterator elementIter;
    Point cursorPos;
    Point gridPoint;
    Point charPoint;
    if (mCurCharacter!=NULL)
    {
         charPoint = mCurCharacter->GetPoint();
    }

    elementIter = mImageMoveRange.begin();

    for (vector<Point>::iterator i=moveRange.begin(); i!=moveRange.end(); i++)
    {
        gridPoint = (*i);
        printf("grid point: %d, %d\n", gridPoint.GetX(), gridPoint.GetY() );
        if ( (validPoint(gridPoint)) && ( (!hasCharacter(gridPoint)) || (gridPoint==charPoint) ) )
        {
            cursorPos.Set( mCursorStart.GetX() + gridPoint.GetX()*mTotalTileOffset, mCursorStart.GetY() + gridPoint.GetY()*(mTotalTileOffset) );
            (*elementIter).setPos( cursorPos );
            (*elementIter).setVisible( true );
            elementIter++;
        }
    }

    printf("I've made it past implementing the move squares\n");

}




//============================= ACCESS     ===================================

void UIGrid::setLevel(Level* l)
{
    mLevel = l;
}

//============================= INQUIRY    ===================================

bool UIGrid::validPoint(Point p)
{
    int x = p.GetX();
    int y = p.GetY();

    if ( (x<mNumColumns) && (y<mNumRows) && (x>=0) && (y>=0) )
    {
        return true;
    } else {
        return false;
    }
}

bool UIGrid::hasCharacter(Point p)
{
    int index = findIndex(p);
    if( index != -1 )
    {
        //UITile* temp =
        return mTiles[index].hasCharacter();
    }
    else
    {
        return false;
    }
}
/////////////////////////////// PROTECTED  ///////////////////////////////////


int UIGrid::findIndex(int x, int y)
{
    if (validPoint( Point(x,y) )) {
        return y + mNumRows*x;
    } else {
        return -1;
    }
}

int UIGrid::findIndex(Point p)
{
    if (validPoint( p )) {
        return p.GetY() + mNumRows*p.GetX();
    } else {
        return -1;
    }
}



SDL_Surface* UIGrid::getClassSurface(Character* c, string group)
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
            // you screwed up
            return ResourceManager::GetInstance()->LoadTexture("charTile.bmp");
        }
    }

    else if("Enemy")
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
            // you screwed up
            return ResourceManager::GetInstance()->LoadTexture("charTile.bmp");
        }
    }

    else
    {
        return NULL;
    }

}

vector<Point> UIGrid::RefineMoveRange( vector<Point> moveRange)
{
    std::vector<Point>::iterator pointIter = moveRange.begin();
    std::vector<Point> finalVtr;
    Point gridPoint;
    Point charPoint;
    if (mCurCharacter!=NULL)
        charPoint = mCurCharacter->GetPoint();


    while (pointIter!=moveRange.end())
    {
        gridPoint = (*pointIter);
        //printf("grid point: %d, %d\n", gridPoint.GetX(), gridPoint.GetY() );
        if ( (validPoint(gridPoint)) && ( (!hasCharacter(gridPoint)) || (gridPoint==charPoint) ) )
        {
            finalVtr.push_back( gridPoint );
        }
        pointIter++;
    }

    return finalVtr;

}

/////////////////////////////// PRIVATE    ///////////////////////////////////
