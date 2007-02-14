/**
 * File: SecurityManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 13 2007 | Initial creation of header (stubbed)
 */
#include "SecurityManager.h"                                // class implemented


/////////////////////////////// PUBLIC ///////////////////////////////////////

//============================= LIFECYCLE ====================================

SecurityManager* SecurityManager::_instance = 0;

SecurityManager* SecurityManager::GetInstance()
{
    if( !_instance )
    {
        _instance = new SecurityManager();
    }
    return _instance;
}

SecurityManager::~SecurityManager()
{
    // stub
}// ~SecurityManager

void SecurityManager::Initialize()
{

}

void SecurityManager::Shutdown()
{

}

//============================= OPERATORS ====================================
//============================= OPERATIONS ===================================

void SecurityManager::LoadPasswordHashFile( const string fileName )
{
    // stub
}

void SecurityManager::SavePasswordHashFile( const string fileName = "" )
{
    // stub
}

bool SecurityManager::VerifyPassword( const string userName, const string password )
{
    // stub
    return false;
}

void SecurityManager::AddUser( const string userName, const string password )
{
    // stub
}

void SecurityManager::DeleteUser( const string userName )
{
    // stub
}

//============================= ACCESS     ===================================
//============================= INQUIRY    ===================================
/////////////////////////////// PROTECTED  ///////////////////////////////////

SecurityManager::SecurityManager()
{
    // stub
}// SecurityManager

/////////////////////////////// PRIVATE    ///////////////////////////////////
