#ifndef __DBNODETEST_H
#define __DBNODETEST_H

#include <cxxtest/TestSuite.h>

#include <../Database/DBNode.h>

//
// A generated test suite: Just write tests!
//

class DBNodeTest : public CxxTest::TestSuite
{
private:
// any variables that could be shared between tests

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

    void testGetName()
    {
        DBNode pDBNode(0, "TestNode");
        TS_ASSERT_EQUALS( pDBNode.GetName(), "TestNode" ); // see if GetName method returns the valid string value.
    }

    void testGetParent()
    {
        DBNode ParentNode(0, "ParentNode");
        DBNode ChildNode(1, "ChildNode");

        ChildNode.SetParent( &ParentNode );

        TS_ASSERT_EQUALS( ChildNode.GetParent(), &ParentNode );
    }

    void testGetFirstChild()
    {
        DBNode ParentNode(0, "ParentNode");
        DBNode ChildNode1(1, "ChildNode1");
        DBNode ChildNode2(2, "ChildNode2");
        DBNode ChildNode3(3, "ChildNode3");

        ParentNode.AddChild( &ChildNode1 );
        ParentNode.AddChild( &ChildNode2 );
        ParentNode.AddChild( &ChildNode3 );

        TS_ASSERT_EQUALS( ParentNode.GetFirstChild(), &ChildNode1 );
    }

    void testGetNextChild()
    {
        DBNode ParentNode( 0, "ParentNode" );
        DBNode ChildNode1( 1, "ChildNode1" );
        DBNode ChildNode2( 2, "ChildNode2" );
        DBNode ChildNode3( 3, "ChildNode3" );

        ParentNode.AddChild( &ChildNode1 );
        ParentNode.AddChild( &ChildNode2 );
        ParentNode.AddChild( &ChildNode3 );

        ParentNode.GetFirstChild(); // GetFirstChild which is ChildNode1.

        TS_ASSERT_EQUALS( ParentNode.GetNextChild(), &ChildNode2 );
    }

    void testGetChild()
    {
        DBNode ParentNode( 0, "ParentNode" );
        DBNode ChildNode1( 1, "ChildNode1" );
        DBNode ChildNode2( 2, "ChildNode2" );
        DBNode ChildNode3( 3, "ChildNode3" );

        ParentNode.AddChild( &ChildNode1 );
        ParentNode.AddChild( &ChildNode2 );
        ParentNode.AddChild( &ChildNode3 );

        TS_ASSERT_EQUALS( ParentNode.GetChild( "ChildNode3" ), &ChildNode3 );
    }

    void testGetFirstAttribute()
    {
        DBNode pNode(0, "Node");
        DBInt pInt1(1, "Ten", 10);
        DBInt pInt2(2, "Hundred", 100);
        DBInt pInt3(3, "One", 1);

        pNode.AddAttribute( &pInt1 );
        pNode.AddAttribute( &pInt2 );
        pNode.AddAttribute( &pInt3 );

        TS_ASSERT_EQUALS( pNode.GetFirstAttribute(), &pInt1 );
    }

    void testGetNextAttribute()
    {
        DBNode pNode(0, "Node");
        DBInt pInt1(1, "Ten", 10);
        DBInt pInt2(2, "Hundred", 100);
        DBInt pInt3(3, "One", 1);

        pNode.AddAttribute( &pInt1 );
        pNode.AddAttribute( &pInt2 );
        pNode.AddAttribute( &pInt3 );

        pNode.GetFirstAttribute(); // GetFirstAttribute which is pInt1.

        TS_ASSERT_EQUALS( pNode.GetNextAttribute(), &pInt2 );
    }

    void testGetAttribute()
    {
        DBNode pNode(0, "Node");
        DBInt pInt1(1, "Ten", 10);
        DBInt pInt2(2, "Hundred", 100);
        DBInt pInt3(3, "One", 1);

        pNode.AddAttribute( &pInt1 );
        pNode.AddAttribute( &pInt2 );
        pNode.AddAttribute( &pInt3 );

        TS_ASSERT_EQUALS( pNode.GetAttribute( "One" ), &pInt3 );
    }

    void testSetParent()
    {
        DBNode ParentNode(0, "Parent");
        DBNode ChildNode(1, "Child");

        ChildNode.SetParent( &ParentNode );

        TS_ASSERT_EQUALS( ChildNode.GetParent(), &ParentNode );
    }

    void testAddChild()
    {
        DBNode ParentNode(0, "Parent");
        DBNode ChildNode(1, "Child");

        ParentNode.AddChild( &ChildNode );

        TS_ASSERT_EQUALS( ParentNode.GetChild( "Child" ), &ChildNode );
    }

    void testAddAttribute()
    {
        DBNode pNode(0, "Node");
        DBInt pInt(1, "Ten", 10);

        pNode.AddAttribute( &pInt );

        TS_ASSERT_EQUALS( pNode.GetAttribute( "Ten" ), &pInt );
    }

};


#endif // __DBNODETEST_H

