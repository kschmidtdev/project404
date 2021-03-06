/**
 * File: Map.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, February 9, 2007 | Initial design
 * Mike Malyuk, February 11 2007 | Removed unused code
 * Mike Malyuk, March 9, 2007    | Added default constructor implementation and GetTiles()
 * Mike Malyuk, March 10, 2007   | Added dijkstras method, added node struct
 * Karl Schmidt, March 10, 2007  | Fixed memory leaks
 * Mike Malyuk, March 14, 2007   | Lazy man's immovables added!
 * Mike Malyuk, March 14, 2007   | Optimized one loop
 * Mike Malyuk, March 14, 2007   | Generalizing all methods to mMaxX and mMaxY
 * Karl Schmidt, March 20 2007   | Major adding of consts and reference usage, rearranging includes
 * Karl Schmidt, March 23 2007   | Added some more correct typedef usage
 * Mike Malyuk, March 26, 2007   | Added AIHelper functions AIAttackOrNot and AIGoWhere for new AI
 */

#include "Map.h"                                // class implemented

#include <util.h>

/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================
struct Node
{
    Point p;
    int weight;
    int pathweight;
    Point lp;
    bool checked;
};

Map::Map()
: mTiles()
{
    /*mTiles.push_back( Tile(Point(0,0), "GRASS"));
    mTiles.push_back( Tile(Point(0,1), "GRASS"));
    mTiles.push_back( Tile(Point(0,2), "GRASS"));
    mTiles.push_back( Tile(Point(0,3), "GRASS"));
    mTiles.push_back( Tile(Point(0,4), "GRASS"));
    mTiles.push_back( Tile(Point(0,5), "GRASS"));
    mTiles.push_back( Tile(Point(0,6), "GRASS"));
    mTiles.push_back( Tile(Point(0,7), "GRASS"));
    mTiles.push_back( Tile(Point(0,8), "GRASS"));
    mTiles.push_back( Tile(Point(0,9), "GRASS"));
    mTiles.push_back( Tile(Point(1,0), "GRASS"));
    mTiles.push_back( Tile(Point(1,1), "ROCK"));
    mTiles.push_back( Tile(Point(1,2), "GRASS"));
    mTiles.push_back( Tile(Point(1,3), "GRASS"));
    mTiles.push_back( Tile(Point(1,4), "GRASS"));
    mTiles.push_back( Tile(Point(1,5), "GRASS"));
    mTiles.push_back( Tile(Point(1,6), "GRASS"));
    mTiles.push_back( Tile(Point(1,7), "GRASS"));
    mTiles.push_back( Tile(Point(1,8), "GRASS"));
    mTiles.push_back( Tile(Point(1,9), "GRASS"));
    mTiles.push_back( Tile(Point(2,0), "ROAD"));
    mTiles.push_back( Tile(Point(2,1), "ROAD"));
    mTiles.push_back( Tile(Point(2,2), "ROAD"));
    mTiles.push_back( Tile(Point(2,3), "ROAD"));
    mTiles.push_back( Tile(Point(2,4), "ROAD"));
    mTiles.push_back( Tile(Point(2,5), "ROAD"));
    mTiles.push_back( Tile(Point(2,6), "ROCK"));
    mTiles.push_back( Tile(Point(2,7), "GRASS"));
    mTiles.push_back( Tile(Point(2,8), "GRASS"));
    mTiles.push_back( Tile(Point(2,9), "GRASS"));
    mTiles.push_back( Tile(Point(3,0), "GRASS"));
    mTiles.push_back( Tile(Point(3,1), "GRASS"));
    mTiles.push_back( Tile(Point(3,2), "GRASS"));
    mTiles.push_back( Tile(Point(3,3), "GRASS"));
    mTiles.push_back( Tile(Point(3,4), "GRASS"));
    mTiles.push_back( Tile(Point(3,5), "ROAD"));
    mTiles.push_back( Tile(Point(3,6), "GRASS"));
    mTiles.push_back( Tile(Point(3,7), "GRASS"));
    mTiles.push_back( Tile(Point(3,8), "GRASS"));
    mTiles.push_back( Tile(Point(3,9), "GRASS"));
    mTiles.push_back( Tile(Point(4,0), "GRASS"));
    mTiles.push_back( Tile(Point(4,1), "GRASS"));
    mTiles.push_back( Tile(Point(4,2), "GRASS"));
    mTiles.push_back( Tile(Point(4,3), "GRASS"));
    mTiles.push_back( Tile(Point(4,4), "GRASS"));
    mTiles.push_back( Tile(Point(4,5), "ROAD"));
    mTiles.push_back( Tile(Point(4,6), "GRASS"));
    mTiles.push_back( Tile(Point(4,7), "GRASS"));
    mTiles.push_back( Tile(Point(4,8), "GRASS"));
    mTiles.push_back( Tile(Point(4,9), "GRASS"));
    mTiles.push_back( Tile(Point(5,0), "WATER"));
    mTiles.push_back( Tile(Point(5,1), "WATER"));
    mTiles.push_back( Tile(Point(5,2), "WATER"));
    mTiles.push_back( Tile(Point(5,3), "WATER"));
    mTiles.push_back( Tile(Point(5,4), "WATER"));
    mTiles.push_back( Tile(Point(5,5), "ROAD"));
    mTiles.push_back( Tile(Point(5,6), "GRASS"));
    mTiles.push_back( Tile(Point(5,7), "GRASS"));
    mTiles.push_back( Tile(Point(5,8), "GRASS"));
    mTiles.push_back( Tile(Point(5,9), "GRASS"));
    mTiles.push_back( Tile(Point(6,0), "GRASS"));
    mTiles.push_back( Tile(Point(6,1), "GRASS"));
    mTiles.push_back( Tile(Point(6,2), "GRASS"));
    mTiles.push_back( Tile(Point(6,3), "GRASS"));
    mTiles.push_back( Tile(Point(6,4), "GRASS"));
    mTiles.push_back( Tile(Point(6,5), "ROAD"));
    mTiles.push_back( Tile(Point(6,6), "WATER"));
    mTiles.push_back( Tile(Point(6,7), "WATER"));
    mTiles.push_back( Tile(Point(6,8), "WATER"));
    mTiles.push_back( Tile(Point(6,9), "WATER"));
    mTiles.push_back( Tile(Point(7,0), "GRASS"));
    mTiles.push_back( Tile(Point(7,1), "GRASS"));
    mTiles.push_back( Tile(Point(7,2), "GRASS"));
    mTiles.push_back( Tile(Point(7,3), "GRASS"));
    mTiles.push_back( Tile(Point(7,4), "ROAD"));
    mTiles.push_back( Tile(Point(7,5), "ROAD"));
    mTiles.push_back( Tile(Point(7,6), "ROAD"));
    mTiles.push_back( Tile(Point(7,7), "ROAD"));
    mTiles.push_back( Tile(Point(7,8), "ROAD"));
    mTiles.push_back( Tile(Point(7,9), "ROAD"));
    mTiles.push_back( Tile(Point(8,0), "GRASS"));
    mTiles.push_back( Tile(Point(8,1), "GRASS"));
    mTiles.push_back( Tile(Point(8,2), "GRASS"));
    mTiles.push_back( Tile(Point(8,3), "GRASS"));
    mTiles.push_back( Tile(Point(8,4), "ROAD"));
    mTiles.push_back( Tile(Point(8,5), "GRASS"));
    mTiles.push_back( Tile(Point(8,6), "GRASS"));
    mTiles.push_back( Tile(Point(8,7), "GRASS"));
    mTiles.push_back( Tile(Point(8,8), "GRASS"));
    mTiles.push_back( Tile(Point(8,9), "GRASS"));
    mTiles.push_back( Tile(Point(9,0), "GRASS"));
    mTiles.push_back( Tile(Point(9,1), "GRASS"));
    mTiles.push_back( Tile(Point(9,2), "GRASS"));
    mTiles.push_back( Tile(Point(9,3), "GRASS"));
    mTiles.push_back( Tile(Point(9,4), "ROAD"));
    mTiles.push_back( Tile(Point(9,5), "GRASS"));
    mTiles.push_back( Tile(Point(9,6), "GRASS"));
    mTiles.push_back( Tile(Point(9,7), "GRASS"));
    mTiles.push_back( Tile(Point(9,8), "GRASS"));
    mTiles.push_back( Tile(Point(9,9), "GRASS"));
    mMaxX = 10;
    mMaxY = 10;*/
}// Map
Map::Map( const TileVec & tiles)
: mMaxX( 10 ),
  mMaxY( 10 )
{
    mTiles.insert( mTiles.end(), tiles.begin(), tiles.end() );
}

Map::~Map()
{
}// ~Map

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
void Map::AddTiles( const Tile & tile )
{
    mTiles.push_back(tile);
}
//============================= INQUIRY    ===================================
const Tile & Map::GetTile( const Point & p )
{
    TileVec::iterator iter = mTiles.begin();
    while( ((*iter).GetPoint()) != p && iter != mTiles.end())
    {
        iter++;
    }
    if(((*iter).GetPoint()) == p)
    {
        return *iter;
    }

    //should throw exception
    else
    {
        return (*mTiles.begin());
    }
}

const TileVec & Map::GetTiles() const
{
    return mTiles;
}

const PointVec Map::GetMovementRange( const vector<Character*> & everyone, const vector<Character*> & enemies, Character* guy)
{
    Node* nodes = new Node[mTiles.size()];
    Node* checked = new Node[mTiles.size()];
    PointVec possiblepoints;
    int maxMove = 0;
    for(vector<Character*>::const_iterator citer = everyone.begin(); citer != everyone.end(); citer++)
    {
        if(((*citer)->GetAttr(Character::AGI)/2) > maxMove)
        {
            maxMove = (*citer)->GetAttr(Character::AGI)/2;
        }
    }
    maxMove = maxMove+10;
    Node something;
    int b = 0;
    for(TileVec::iterator iter = mTiles.begin(); iter != mTiles.end(); iter++)
    {
        if((*iter).GetType().compare("ROCK") == 0)
        {
            something.weight = maxMove;
        }
        else
        {
            something.weight = (*iter).GetWeight();
        }
        something.p = (*iter).GetPoint();
        something.pathweight = -1;
        something.checked = false;
        nodes[b] = something;
        b++;
    }
    for(vector<Character*>::const_iterator citer = enemies.begin(); citer != enemies.end(); citer++)
    {
        if(!((*citer)->IsDead()))
        {
            nodes[(*citer)->GetPoint().GetX()*mMaxX + (*citer)->GetPoint().GetY()].weight = maxMove;
        }
    }
    nodes[guy->GetPoint().GetX()*mMaxX + guy->GetPoint().GetY()].pathweight = 0;
    nodes[guy->GetPoint().GetX()*mMaxX + guy->GetPoint().GetY()].checked = true;
    Node currentNode = nodes[guy->GetPoint().GetX()*mMaxX + guy->GetPoint().GetY()];
    checked[0] = currentNode;
    int indexed = 2;
    for(int i = 0; i < (int)mTiles.size(); i++)
    {
        indexed = indexed - 1;
        int up;
        int down;
        if(checked[i].p.GetY() == 0)
        {
            up = -1;
        }
        else
        {
            up =  ((checked[i].p.GetX())*mMaxX + checked[i].p.GetY() - 1);
        }
        if(checked[i].p.GetY() == mMaxY-1)
        {
            down = mTiles.size();
        }
        else
        {
            down = ((checked[i].p.GetX())*mMaxX + checked[i].p.GetY() + 1);
        }
        int curpathweight =nodes[((checked[i].p.GetX())*mMaxX + checked[i].p.GetY())].pathweight;
        int left =  ((checked[i].p.GetX())*mMaxX + checked[i].p.GetY() - mMaxX);
        int right =  ((checked[i].p.GetX())*mMaxX + checked[i].p.GetY() + mMaxX);
        if(up >= 0)
        {
            if(((curpathweight + nodes[up].weight) < nodes[up].pathweight) || ((curpathweight + nodes[up].weight) > 0 && nodes[up].pathweight == -1))
            {
                int needknow = nodes[up].pathweight;
                nodes[up].pathweight = curpathweight + nodes[up].weight;
                needknow = nodes[up].pathweight;
                nodes[up].lp = checked[i].p;
                if(nodes[up].checked == false)
                {
                    nodes[up].checked = true;
                    checked[i + indexed] = nodes[up];
                    indexed++;
                }
            }
        }
        if(down < (int)mTiles.size())
        {
            if(((curpathweight + nodes[down].weight) < nodes[down].pathweight) || ((curpathweight + nodes[down].weight) > 0 && nodes[down].pathweight == -1))
            {
                int needknow = nodes[down].weight;
                nodes[down].pathweight = curpathweight + nodes[down].weight;
                needknow = nodes[down].pathweight;
                nodes[down].lp = checked[i].p;
                if(nodes[down].checked == false)
                {
                    nodes[down].checked = true;
                    checked[i + indexed] = nodes[down];
                    indexed++;
                }
            }

        }
        if(left >= 0)
        {
            if(((curpathweight + nodes[left].weight) < nodes[left].pathweight) || ((curpathweight + nodes[left].weight) > 0 && nodes[left].pathweight == -1))
            {
                int needknow = nodes[left].pathweight;
                nodes[left].pathweight = curpathweight + nodes[left].weight;
                needknow = nodes[left].pathweight;
                nodes[left].lp = checked[i].p;
                if(nodes[left].checked == false)
                {
                    nodes[left].checked = true;
                    checked[i + indexed] = nodes[left];
                    indexed++;
                }
            }
        }
        if(right < (int)mTiles.size())
        {
            if(((curpathweight + nodes[right].weight) < nodes[right].pathweight) || ((curpathweight + nodes[right].weight) > 0 && nodes[right].pathweight == -1))
            {
                int needknow = nodes[right].pathweight;
                nodes[right].pathweight = curpathweight + nodes[right].weight;
                needknow = nodes[right].pathweight;
                nodes[right].lp = checked[i].p;
                if(nodes[right].checked == false)
                {
                    nodes[right].checked = true;
                    checked[i + indexed] = nodes[right];
                    indexed++;
                }
            }
        }
    }
    cout << "Character Move: " << guy->GetAttr(Character::AGI)/2 << endl;
    for(int i = 0; i < (int)mTiles.size(); i++)
    {
        if(nodes[i].pathweight <= (guy->GetAttr(Character::AGI)/2))
        {
            bool valid = true;
            for(vector<Character*>::const_iterator eiter = everyone.begin(); eiter != everyone.end(); eiter++)
            {
                if(nodes[i].p == (*eiter)->GetPoint() && nodes[i].p != guy->GetPoint())
                {
                    valid = false;
                }
            }
            if(valid)
            {
                possiblepoints.push_back(nodes[i].p);
            }
        }
    }

    delete[] nodes;
    delete[] checked;

    return possiblepoints;

}
//Guy = AI unit, enemies = party
const bool Map::AIAttackOrNot(const vector<Character*>& everyone , const vector<Character*>& enemies, Character* guy)
{
    PointVec myMove = GetMovementRange(everyone, enemies, guy);
    Point storeMyPoint = guy->GetPoint();
    PointVec myAttack;
    for(vector<Point>::iterator mpoint = myMove.begin(); mpoint != myMove.end(); mpoint++)
    {
        guy->Move((*mpoint));
        PointVec temp = guy->CalcAction();
        myAttack.insert( myAttack.end(), temp.begin(), temp.end() );
    }
    guy->Move(storeMyPoint);
    for(vector<Point>::iterator mpoint = myAttack.begin(); mpoint != myAttack.end(); mpoint++)
    {
        if(guy->GetTarget()->GetPoint() == (*mpoint))
        {
            return true;
        }
    }
    return false;
}
const vector<Point> Map::AIGoWhere(const vector<Character*>& everyone, const vector<Character*>& enemies, const vector<Character*>& allies, Character* guy)
{
    //Get my range
    PointVec myMove = GetMovementRange(everyone, enemies, guy);
    Point storeMyPoint = guy->GetPoint();
    PointVec possibleChoice;
    if(guy->GetCharacterClassName() != "Healer")
    {
        for(vector<Point>::iterator mpoint = myMove.begin(); mpoint != myMove.end(); mpoint++)
        {
            guy->Move((*mpoint));
            for(vector<Character*>::const_iterator citer = enemies.begin(); citer != enemies.end(); citer++)
            {
                PointVec temp = guy->CalcAction();
                if( find( temp.begin(), temp.end(), (*citer)->GetPoint() ) != temp.end() )
                {
                    possibleChoice.push_back(guy->GetPoint());
                    guy->Move(storeMyPoint);
                    return possibleChoice;
                }
            }
        }
    }
    guy->Move(storeMyPoint);

    PointVec theirMove;
    PointVec totalAttack;
    //iterate through all of party's members
    for(vector<Character*>::const_iterator citer = enemies.begin(); citer != enemies.end(); citer++)
    {
        if(!((*citer)->IsDead()))//if they are not dead then lets check their attack
        {
            theirMove = GetMovementRange(everyone, allies, (*citer)); //get their move
            Point storeTheirPoint = (*citer)->GetPoint(); //store their cur position

            //for all movement possibilities, calculate their attack.
            for(vector<Point>::iterator mpoint = theirMove.begin(); mpoint != theirMove.end(); mpoint++)
            {
                //store all points of attack
                (*citer)->Move(*mpoint);
                PointVec temp = (*citer)->CalcAction();
                totalAttack.insert( totalAttack.end(), temp.begin(), temp.end() );
            }
            (*citer)->Move(storeTheirPoint);//restore their position
        }
    }
    /*for(vector<Point>::iterator piter = totalAttack.begin(); piter != totalAttack.end(); piter++)
    {
        cout << (*piter).GetX() << ", " << (*piter).GetY() << endl;
    }*/
    //cross reference my movement with theirs, return only points that they can't attack me on.
    for(vector<Point>::iterator piter = myMove.begin(); piter != myMove.end(); piter++)
    {
        bool ok = true;
        if( find( totalAttack.begin(), totalAttack.end(), *piter ) != totalAttack.end() )
        {
            ok = false;
        }
        if(ok)
        {
            //std::cout << (*piter).GetX() << ", " << (*piter).GetY() << std::endl;
            possibleChoice.push_back((*piter));
            totalAttack.push_back((*piter)); //hack to not store same points in return
        }
    }
    return possibleChoice;
}
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
