import sys, os

def createUnitTestTemplate( file ):
    testFileName = file[0:-2] + "Test.h"

    if file.endswith( "Test.h" ):
        print "Ignoring Test file: " + file
    elif os.path.exists( testFileName ):
        print testFileName + " exists, skipping"        
    else:
        print "Creating " + testFileName
        headerFile = open( file, "r" )
        headerFileText = headerFile.readlines()
        headerFile.close()
        
        topTemplate = """#ifndef __SIMPLETEST_H
#define __SIMPLETEST_H

#include <cxxtest/TestSuite.h>

#include <Simple.h>

//
// A generated test suite: Just write tests!
//

class SimpleTest : public CxxTest::TestSuite
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

functions

};


#endif // __SIMPLETEST_H

"""
        topTemplate = topTemplate.replace( "SIMPLETEST", testFileName[0:-2].upper() )
        topTemplate = topTemplate.replace( "SimpleTest", testFileName[0:-2] )
        topTemplate = topTemplate.replace( "Simple.h", file )
      
        functionOutline = """    void testYourFunctionNameHere()
    {
        
    }"""
        topTemplate = topTemplate.replace( "functions", functionOutline )
        
        testFile = open( testFileName, "w" )
        testFile.writelines( topTemplate )
        testFile.close()

def main():
    fileList = os.listdir( "." )

    headerFiles = []
    for file in fileList:
        if file.endswith(".h"):
            print "Found: " + file
            headerFiles.append( file )

    for hFile in headerFiles:
        createUnitTestTemplate( hFile )

main()
