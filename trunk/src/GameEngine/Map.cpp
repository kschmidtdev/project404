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
 */

#include <util.h>

#include "Map.h"                                // class implemented


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
{
    mTiles.push_back( Tile(Point(0,0), "GRASS"));
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
    mMaxY = 10;
}// Map
Map::Map(vector<Tile> tiles)
:mTiles(tiles)
{
    mMaxX = 10;
    mMaxY = 10;
}
Map::~Map()
{
}// ~Map

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
void Map::AddTiles(Tile tile)
{
    mTiles.push_back(tile);
}
//============================= INQUIRY    ===================================
Tile Map::GetTile(Point p)
{
    vector<Tile>::iterator iter;
    iter = mTiles.begin();
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

vector<Tile> Map::GetTiles()
{
    return mTiles;
}

vector<Point> Map::GetMovementRange(vector<Character*> everyone, vector<Character*> enemies, Character* guy)
{
    Node* nodes = new Node[mTiles.size()];
    Node* checked = new Node[mTiles.size()];
    vector<Point> possiblepoints;
    int maxMove = 0;
    for(vector<Character*>::iterator citer = everyone.begin(); citer != everyone.end(); citer++)
    {
        if(((*citer)->GetAttr(Character::AGI)/2) > maxMove)
        {
            maxMove = (*citer)->GetAttr(Character::AGI)/2;
        }
    }
    maxMove = maxMove+10;
    Node something;
    int b = 0;
    for(vector<Tile>::iterator iter = mTiles.begin(); iter != mTiles.end(); iter++)
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
    for(vector<Character*>::iterator citer = enemies.begin(); citer != enemies.end(); citer++)
    {
        for(int i = 0; i < mTiles.size(); i++)
        {
            if(nodes[i].p == (*citer)->GetPoint())
            {
                nodes[i].weight = maxMove;
            }
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
            up =  ((checked[i].p.GetX())*10 + checked[i].p.GetY() - 1);
        }
        if(checked[i].p.GetY() == 9)
        {
            down = mTiles.size();
        }
        else
        {
            down = ((checked[i].p.GetX())*10 + checked[i].p.GetY() + 1);
        }
        int curpathweight =nodes[((checked[i].p.GetX())*10 + checked[i].p.GetY())].pathweight;
        int left =  ((checked[i].p.GetX())*10 + checked[i].p.GetY() - mMaxX);
        int right =  ((checked[i].p.GetX())*10 + checked[i].p.GetY() + mMaxX);
        //cout << "CurPoint: " << checked[i].p.GetX() << ", " << checked[i].p.GetY() << endl;
        //cout << "CurWeight: " << nodes[((checked[i].p.GetX())*10 + checked[i].p.GetY())].pathweight << endl;
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
            //cout << nodes[i].pathweight << endl;
            bool valid = true;
            for(vector<Character*>::iterator eiter = everyone.begin(); eiter != everyone.end(); eiter++)
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

/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
