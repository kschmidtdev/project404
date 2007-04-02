/**
 * File: BiQuad.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Mike Malyuk, April 1, 2007 | Initial Creation
 */
#include "BiQuad.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

BiQuad::BiQuad(void)
{
    //A and B are of length 3
    mB = new double[3];
    mA = new double[3];
    mXstate = new double[2];
    mYstate = new double[2];
    mXstate[0] = 0;
    mYstate[0] = 0;
    mXstate[1] = 0;
    mYstate[1] = 0;
}// BiQuad

BiQuad::BiQuad(double* B, double* A, int NBCoeff, double G):mG(G), mNBCoeff(NBCoeff)
{
    //A and B are of length 3
    mB = new double[3];
    mA = new double[3];
    mXstate = new double[2];
    mYstate = new double[2];
    for(int i = 0; i < mNBCoeff; i++)
    {
        mA[i] = A[i];
        mB[i] = B[i];
    }
    mXstate[0] = 0;
    mYstate[0] = 0;
    mXstate[1] = 0;
    mYstate[1] = 0;
}// BiQuad

BiQuad::~BiQuad()
{
    delete[] mB;
    delete[] mA;
    delete[] mXstate;
    delete[] mYstate;
}// ~BiQuad

//============================= OPERATIONS ===================================
//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

/////////////////////////////// PRIVATE    ///////////////////////////////////
