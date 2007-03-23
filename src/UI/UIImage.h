/**
 * An extension of UIElement that represents a single image
 *
 * #include "UIImage.h"
 *
 * An extension of UIElement that represents a single image.
 *
 * Project 404 2007
 *
 * Authors:
 * Andrew Osborne, February 11 2007 | Initial Creation
 * Karl Schmidt, March 22 2007      | Correcting include orders and paths
 */

#ifndef UIImage_h
#define UIImage_h

// SYSTEM INCLUDES
//
#include <string>

// PROJECT INCLUDES
//
#include <UI/UIElement.h>

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
    UIImage(const std::string & filename);

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
