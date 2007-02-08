classTemplateTxt = """/**
 * File: XX.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date | Work Done
 */
#include "XX.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

XX::XX()
{
}// XX

XX::XX(const XX&)
{
}// XX

XX::~XX()
{
}// ~XX


//============================= OPERATORS ====================================

XX& 
XX::operator=(XX&);
{
   return *this;

}// =

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////"""

className = raw_input( "Please enter the name of your class: " )

classTemplateTxt = classTemplateTxt.replace( "XX", className )

classfile = open( className + ".cpp", "w" )

classfile.write( classTemplateTxt )
classfile.close()
