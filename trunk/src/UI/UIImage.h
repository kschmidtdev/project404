/**
 * An extension of UIElement that represents a single image
 *
 * #include "UIImage.h"
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

#ifndef UIImage_h
#define UIImage_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//
#include <UIElement.h>

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class UIImage : public UIElement
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    UIImage(void);

    /**
     * constructor involving loading bitmap file for image
	 */
    UIImage(const string filename);

    /**
     * Destructor.
	 */
    ~UIImage(void);

// OPERATORS



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

#endif  // _UIImage_h_
