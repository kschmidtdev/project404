/**
 * File: main.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 11 2007 | Added C call to make console output work
 */

#include <GameRoot.h>
#include <stdio.h>
#include "Level.h"
#include "Knight.h"
int main ( int argc, char** argv )
{
    fflush (stdout); // Enable console output, SDL disables this
    vector<Character*> party;
    vector<Character*> badguys;
    vector<Point> start;
    vector<Tile*> tiles;
    Tile* tile = new Tile(Point(0,0), "GRASS");
    tiles.push_back(tile);
    tile = new Tile(Point(1,0), "GRASS");
    tiles.push_back(tile);
    tile = new Tile(Point(2,0), "GRASS");
    tiles.push_back(tile);
    tile = new Tile(Point(0,1), "GRASS");
    tiles.push_back(tile);
    tile = new Tile(Point(1,1), "GRASS");
    tiles.push_back(tile);
    tile = new Tile(Point(2,1), "GRASS");
    tiles.push_back(tile);
    tile = new Tile(Point(0,2), "GRASS");
    tiles.push_back(tile);
    tile = new Tile(Point(1,2), "GRASS");
    tiles.push_back(tile);
    tile = new Tile(Point(2,2), "GRASS");
    tiles.push_back(tile);
    start.push_back(Point(0,0));
    Knight* knight = new Knight("dumb", 20, NULL, NULL);
    party.push_back(knight);
    Knight* knight2 = new Knight("dumb", 1, NULL, NULL);
    knight2->Move(Point(3,3));
    badguys.push_back(knight2);
    Map* map = new Map(tiles);
    Level bleh = Level(party, badguys, start, map);
    cout << bleh.OnSelect(Point(0,1)) << endl;
    cout << bleh.ReturnState() << endl;
    Character* meh = bleh.OnSelect(Point(0,0));
    cout << meh->GetAttr(Character::AGI) <<endl;
    /*cout << bleh.ReturnState() << endl;
    cout <<bleh.OnSelect(Point(0,1)) << endl;
    cout <<bleh.OnSelect(Point(0,1)) << endl;
    bleh.TakeTurn();
    bleh.TakeTurn();
    cout << bleh.OnSelect(Point(0,1)) << endl;
    cout << bleh.OnSelect(Point(1,1)) << endl;
    cout << bleh.ReturnState() << endl;
    bleh.TakeTurn();
    bleh.TakeTurn();
    */
    cout << bleh.OnSelect(Point(3,2)) << endl;
    cout << bleh.ReturnState() << endl;
    cout << bleh.OnSelect(Point(3,3)) << endl;
    cout << bleh.GetLoseCondition() << endl;
    cout << bleh.GetWinCondition() << endl;
    bleh.TakeTurn();
    bleh.TakeTurn();
    Character* chara = bleh.OnSelect(Point(3,2));
    cout << chara->GetExp() << endl;
    /*bleh.TakeTurn();
    bleh.TakeTurn();
    cout << bleh.OnSelect(Point(3,2)) << endl;
    cout << bleh.OnSelect(Point(3,2)) << endl;
    */
/*
    GameRoot ourGame;

    ourGame.Initialize();

    ourGame.GameLoop();

    ourGame.Shutdown();

    return 0;
    */
}
