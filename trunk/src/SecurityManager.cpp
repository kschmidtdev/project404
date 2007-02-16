/**
 * File: SecurityManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 15 2007 | Added functionality for loading/saving/verifying users and passwords
 * Karl Schmidt, February 13 2007 | Initial creation of header (stubbed)
 */
#include "SecurityManager.h"                                // class implemented

#include <Logger.h>
#include <util.h>

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
    FILE* passHashFileHandle = NULL;
    passHashFileHandle = fopen( fileName.c_str(), "r" );

    if( passHashFileHandle )
    {
        LogInfo( "Loading username/password hashes from " + fileName );

        char userName[32];
        char password[1024];
        // While we're not at the end of the file...
        while ( !feof( passHashFileHandle ) )
        {
        	// Load in a line of text formatted like "text #" (where # is some integer)
            fscanf( passHashFileHandle, "%s %s\n", userName, password );
            if( userName[0] != '#' ) // Allow for "comments" in the file
            {
                mLoadedPasswords[userName] = password;
                LogInfo( string("Loaded username: ") + userName + string(" with password hash: ") + password );
            }
            else // Seek to the end of the line if you find a comment
            {
                while( fgetc( passHashFileHandle ) != '\n' && !feof( passHashFileHandle ) )
                {
                    fseek( passHashFileHandle, 1, SEEK_CUR );
                }
            }
        }

        fclose( passHashFileHandle );
    }
    else
    {
        // We should never try to open a file that doesn't exist
        tacAssert( false );
        LogWarning( fileName + string(" - File not found") );
    }
}

void SecurityManager::SavePasswordHashFile( const string fileName )
{
    if( mLoadedPasswords.empty() )
    {
        // Nothing to write
        return;
    }

    FILE* passHashFileHandle = NULL;
    passHashFileHandle = fopen( fileName.c_str(), "w" );

    if( passHashFileHandle )
    {
        LogInfo( "Saving username/password hashes to " + fileName );
        for( PasswordHashMapItr i = mLoadedPasswords.begin(); i != mLoadedPasswords.end(); ++i )
        {
            fprintf( passHashFileHandle, "%s %s\n", i->first.c_str(), i->second.c_str() );
        }

        fclose( passHashFileHandle );
    }
    else
    {
        // Unable to write to file for some reason
        tacAssert( false );
        LogWarning( fileName + string(": Unable to write to password file") );
    }
}

bool SecurityManager::VerifyPassword( const string userName, const string password )
{
    if( HashString( userName + password ) == mLoadedPasswords[userName] )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void SecurityManager::AddUser( const string userName, const string password )
{
    tacAssert( userName != "" && password != "" );
    if( userName == "" || password == "" )
    {
        LogError( "Trying to add a user with a blank username or password" );
        return;
    }

    if( mLoadedPasswords.find( userName ) == mLoadedPasswords.end() )
    {
        mLoadedPasswords[userName] = HashString( userName + password );
    }
    else
    {
        LogWarning( "Attempt to add a user that already exists." );
    }
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

string SecurityManager::HashString( const string incoming )
{
    string output = "";
    for( unsigned int i(0); i < incoming.length(); ++i )
    {
        int curDigit = incoming[i];
        output += toString((curDigit * 10) % 2000);
    }
    return output;
}

/////////////////////////////// PRIVATE    ///////////////////////////////////
