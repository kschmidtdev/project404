#ifndef __UIELEMENTTEST_H
#define __UIELEMENTTEST_H

#include <cxxtest/TestSuite.h>

#include <UIElement.h>

//
// A generated test suite: Just write tests!
//

class UIElementTest : public CxxTest::TestSuite
{
protected:
    UIElement* testElement;
// any variables that could be shared between tests

// Unit Tests:
public:

    // Called before all unit tests in this suite, remove if not needed
    virtual void setUp()
    {
        testElement = new UIElement();
    }

    // Called after all unit tests in this suite, remove if note needed
    virtual void tearDown()
    {
        delete testElement;
    }

    void testElementGettersSetters()
    {
        Point p3(3,3);
        Point p0;

        // position initialized properly
        TS_ASSERT_EQUALS( testElement->GetPos(), p0 );

        // Test type a of set position
        testElement->SetPos(p3);
        TS_ASSERT_EQUALS( testElement->GetPos(), p3 );

        // Test other type of set position
        int x = 4;
        int y = 4;
        testElement->SetPos( x, y );
        TS_ASSERT_EQUALS( testElement->GetPos(), Point(x,y) );

        // Testing default visibility status
        TS_ASSERT_EQUALS( testElement->GetVisible(), true );

        // Testing default visibility setter
        testElement->SetVisible(false);
        TS_ASSERT_EQUALS( testElement->GetVisible(), false );

        // This line should only be in for UIElement
        TS_ASSERT( testElement->GetElement() == NULL );
    }



};


#endif // __UIELEMENTTEST_H

