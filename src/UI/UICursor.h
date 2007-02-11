/**
 * A one line description of the class.
 *
 * #include "UICursor.h"
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

#ifndef UICursor_h
#define UICursor_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UICursor
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UICursor(void);

    /**
     * Copy constructor.
	 *
	 * @param from The value to copy to this object.
	 */
    UICursor(const UICursor& from);

    /**
     * Destructor.
	 */
    ~UICursor(void);

// OPERATORS

    /**
     * Assignment operator.
	 *
	 * @param from The value to assign to this object.
	 *
	 * @return A reference to this object.
	 */
    UICursor&                     operator=(UICursor& from);

// OPERATIONS
// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
    int maxPosition;
    int curPosition;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _UICursor_h_
