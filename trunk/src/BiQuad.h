/**
 * Class for creating filters on sound
 *
 * #include "BiQuad.h"
 *
 * Class that takes in feed back and forward, generates output.
 *
 * @see something
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, April 1, 2007 | Initial Creation
 */

#ifndef BiQuad_h
#define BiQuad_h

// SYSTEM INCLUDES
//

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//


class BiQuad
{
public:
// LIFECYCLE

    /**
     * Default constructor.
	 */
    BiQuad(void);

    BiQuad(double* B, double* A, int NBCoeff, double G);

    /**
     * Destructor.
	 */
    ~BiQuad(void);


// OPERATIONS
// ACCESS (writing)

void Set(double* B, double* A, int NBCoeff, double G)
{
    mNBCoeff = NBCoeff;
    mG = G;
    for(int i = 0; i < mNBCoeff; i++)
    {
        mA[i] = A[i];
        mB[i] = B[i];
    }
}

double tick(double x)
{
    double y = mG*mB[0]*x + mG*mB[2]*mXstate[1] + mA[1]*mYstate[0] - mA[2]*mYstate[1];
    mXstate[1] = mXstate[0];
    mXstate[0] = x;
    mYstate[1] = mYstate[0];
    mYstate[0] = y;

    return y;
}
// INQUIRY (reading)

protected:
// PROTECTED VARIABLES
private:
// PRIVATE VARIABLES
double* mB;
double* mA;
double mG;
int mNBCoeff;
double *mXstate;
double* mYstate;
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _BiQuad_h_
