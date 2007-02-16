#include <cstdlib>

//#include <SDL/SDL.h>
//#include "sdlrenderer.h"
#include "Knight.h"
#include "WeaponItem.h"
#include "ArmorItem.h"
#include <string>
#include <iostream>
using namespace std;
int main ( int argc, char** argv )
{
    //Create a Knight
    Knight guy("guy", 1, NULL, NULL);

    //Test his get methods
    cout << "Test Getters:" << endl;
    cout << "GetClassName(): " << guy.GetClassName() << endl;
    cout << "GetHP(): " << guy.GetHP() << endl;
    cout << "GetMaxHP(): " << guy.GetMaxHP() << endl;
    cout << "GetAttr(Character::POW): " << guy.GetAttr(Character::POW) << endl;
    cout << "GetAttr(Character::AGI): " << guy.GetAttr(Character::AGI) << endl;
    cout << "GetName(): " << guy.GetName() << endl;
    cout << "GetPoint(): " << guy.GetPoint().GetX() <<", " << guy.GetPoint().GetY() << endl;

    //Test leveling up
    cout << "LEVELLING UP" << endl;
    guy.LevelUp();
    cout << "GetHP(): " << guy.GetHP() << endl;
    cout << "GetMaxHP(): " << guy.GetMaxHP() << endl;
    cout << "GetAttr(Character::POW): " << guy.GetAttr(Character::POW) << endl;
    cout << "GetAttr(Character::AGI): " << guy.GetAttr(Character::AGI) << endl;

    //Test moving
    cout << "Moving to point 3,3" << endl;
    guy.Move(Point(3,3));
    cout << "GetPoint().GetX() .GetY(): " << guy.GetPoint().GetX() <<", " << guy.GetPoint().GetY() << endl;

    //Test Setting
    cout << "SetHP(5)" << endl;
    guy.SetHP(5);
    cout << "GetHP(): " << guy.GetHP() << endl;

    cout << "ArmorItem: UBERSHIELD" << endl;
    ArmorItem* uber = new ArmorItem("UBERSHIELD", 3);

    cout << "ArmorItem: UBERSWORD" << endl;
    WeaponItem* uberuber = new WeaponItem("UBERSWORD", 3);

    cout << "GetAttr(): " << uber->GetAttr() << endl;
    cout << "GetName(): " << uber->GetName() << endl;
    cout << "GetAttr(): " << uberuber->GetAttr() << endl;
    cout << "GetName(): " << uberuber->GetName() << endl;

    cout << "Setting armor to unit" << endl;
    guy.SetArmor(uber);
    guy.SetWeapon(uberuber);
    cout << "GetAttr(): " << guy.GetArmor()->GetAttr()<<endl;
    cout << "GetAttr(): " << guy.GetArmor()->GetName()<<endl;
    cout << "GetAttr(): " << guy.GetWeapon()->GetAttr()<<endl;
    cout << "GetAttr(): " << guy.GetWeapon()->GetName()<<endl;

    //Check that power is subtracted by old weapon and added for new
    cout << "Prove that character power will be reset properly when assigning a worse weapon" << endl;
    cout << "(for character)GetAttr(): " << guy.GetAttr(Character::POW) << endl;
    cout << "Creating Weak sword" << endl;
    WeaponItem* uberano = new WeaponItem("WEAK", 1);
    guy.SetWeapon(uberano);
    cout << "(for character)GetAttr(): " << guy.GetAttr(Character::POW) << endl;

    return 0;
}
