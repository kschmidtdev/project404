classTemplateTxt = """/**      
 * A one line description of the class.
 *
 * #include "XX.h"
 *
 * A longer description.
 *  
 * @see something
 *
 * Project 404 2007
 *
 * Authors:
 * Name, Date (Month Day Year), What was done
 */

#ifndef XX_h
#define XX_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class XX
{
public:
// LIFECYCLE

   /**
    * Default constructor.
	*/
   XX(void);

   /**
    * Copy constructor.
	*
	* @param from The value to copy to this object.
	*/
   XX(const XX& from);

   /**
    * Destructor.
	*/
   ~XX(void);

// OPERATORS

   /**
    * Assignment operator.
	*
	* @param from The value to assign to this object.
	*
	* @return A reference to this object.
	*/
   XX&                     operator=(XX& from);  

// OPERATIONS
// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _XX_h_"""

className = raw_input( "Please enter the name of your class: " )

classTemplateTxt = classTemplateTxt.replace( "XX", className )

classfile = open( className + ".h", "w" )

classfile.write( classTemplateTxt )
classfile.close()
