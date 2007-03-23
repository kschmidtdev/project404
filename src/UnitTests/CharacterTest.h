#ifndef __CHARACTERTEST_H
#define __CHARACTERTEST_H

#include <cxxtest/TestSuite.h>

#include <GameEngine/Character.h>
#include <GameEngine/ArmorItem.h>
#include <GameEngine/WeaponItem.h>
//
// A generated test suite: Just write tests!
//

class CharacterTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests
    Character character;
    Character meh;

// Unit Tests:
public:

    // Called before all unit tests in this suite, remove if not needed
    void setUp()
    {

    }

    // Called after all unit tests in this suite, remove if note needed
    void tearDown()
    {

    }

    void TestingSettersGetters()
    {
    ArmorItem aitem("Ubershield", 3);
    WeaponItem witem("Mehsword", 1);
    ArmorItem a2item("blehshield", 1);
    WeaponItem w2item("UBERSWORDOFDEATH!!!11111", 3);
    //move, set HP and enable items
    character.Move(Point(3,3));
    character.SetHP(5);
    character.SetArmor(&aitem);
    character.SetWeapon(&witem);

    //Point should be moved
    TS_ASSERT_EQUALS(character.GetPoint(), Point(3,3));
    //HP up 90
    TS_ASSERT_EQUALS(character.GetHP(), 5);
    //POW DEF up by amount in item
    TS_ASSERT_EQUALS(character.GetAttr(Character::POW), 1);
    TS_ASSERT_EQUALS(character.GetAttr(Character::DEF), 3);
    //POW DEF changed when items changed AGI still 0
    character.SetArmor(&a2item);
    character.SetWeapon(&w2item);
    TS_ASSERT_EQUALS(character.GetAttr(Character::POW), 3);
    TS_ASSERT_EQUALS(character.GetAttr(Character::DEF), 1);
    TS_ASSERT_EQUALS(character.GetAttr(Character::AGI), 3);
    //Gain +1 on all atributes
    character.LevelUp();
    TS_ASSERT_EQUALS(character.GetAttr(Character::POW), 4);
    TS_ASSERT_EQUALS(character.GetAttr(Character::AGI), 4);
    TS_ASSERT_EQUALS(character.GetAttr(Character::DEF), 2);
    //Character should be exhausted
    character.Exhaust();
    TS_ASSERT_EQUALS(character.GetExhaust(), true);
    //Character should invigorate
    character.Invigorate();
    TS_ASSERT_EQUALS(character.GetExhaust(), false);
    //Character should exhaust and be dead
    character.MakeDead();
    TS_ASSERT_EQUALS(character.GetExhaust(), true);
    TS_ASSERT_EQUALS(character.IsDead(), true);
    //Check names
    TS_ASSERT_EQUALS(character.GetName(), "GENERIC");
    TS_ASSERT_EQUALS(character.GetCharacterClassName(), "base");
    TS_ASSERT_EQUALS(character.GetArmor()->GetName(), "blehshield");
    TS_ASSERT_EQUALS(character.GetArmor()->GetAttr(), 1);
    TS_ASSERT_EQUALS(character.GetWeapon()->GetName(), "UBERSWORDOFDEATH!!!11111");
    TS_ASSERT_EQUALS(character.GetWeapon()->GetAttr(), 3);

    }

    void TestCalcAction()
    {
        vector<Point> points = character.CalcAction();
        vector<Point>::iterator iter;
        iter = points.begin();
        TS_ASSERT_EQUALS((*iter), Point(2, 3));
        iter++;
        TS_ASSERT_EQUALS((*iter), Point(4, 3));
        iter++;
        TS_ASSERT_EQUALS((*iter), Point(3, 2));
        iter++;
        TS_ASSERT_EQUALS((*iter), Point(3, 4));
        iter++;
        TS_ASSERT_EQUALS(iter, points.end());
    }

    void TestAttack()
    {
        Character joeshmoe;
        joeshmoe.LevelUp();
        WeaponItem weapon("RIDICULOUS", 500);
        joeshmoe.SetWeapon( &weapon );
        //SetHp is only used in Attack and Heal
        meh.SetHP(1);
        joeshmoe.Attack(&meh);
        //demonstrate exp
        TS_ASSERT_EQUALS(joeshmoe.GetLevel(), 2);
        TS_ASSERT_EQUALS(joeshmoe.GetExp(), 50);
        //illustrate level up
        meh.SetHP(1);
        joeshmoe.Attack(&meh);
        TS_ASSERT_EQUALS(joeshmoe.GetLevel(), 3);
        TS_ASSERT_EQUALS(joeshmoe.GetExp(), 0);
        //show damage doesn't kill always
        //show Max different from Cur
        meh.SetHP(10);
        joeshmoe.Attack(&meh);
        int power = joeshmoe.GetAttr(Character::POW);

        //now with random, should not have hp higher than this value
        TS_ASSERT_LESS_THAN_EQUALS(meh.GetHP(), 10 - (power-2))
        TS_ASSERT_EQUALS(meh.GetMaxHP(), 10);
    }

};


#endif // __CHARACTERTEST_H

