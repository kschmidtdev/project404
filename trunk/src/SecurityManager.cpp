/**
 * File: SecurityManager.cpp
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 15 2007 | Implemented DeleteUser and ChangeUserPassword
 * Karl Schmidt, February 15 2007 | Added functionality for loading/saving/verifying users and passwords
 * Karl Schmidt, February 13 2007 | Initial creation of header (stubbed)
 * Karl Schmidt, March 11 2007	  | Added file encryption/decryption routines
 */

#include <util.h>

#include "SecurityManager.h"                                // class implemented

#include <Logger.h>

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
    if( _instance )
    {
        delete _instance;
        _instance = NULL;
    }
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
        //tacAssert( false );
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
    tacAssert( userName != "" );
    if( userName == "" )
    {
        LogError( "Trying to delete a user with a blank username" );
        return;
    }

    PasswordHashMapItr itr = mLoadedPasswords.find( userName );
    if( itr == mLoadedPasswords.end() )
    {
        LogWarning( "Attempt to delete a user that doesn't exist." );
    }
    else
    {
        mLoadedPasswords.erase( itr );
    }
}

void SecurityManager::ChangeUserPassword( const string userName, const string newPassword )
{
    tacAssert( userName != "" && newPassword != "" );
    if( userName == "" || newPassword == "" )
    {
        LogError( "Trying to add a change a password with a blank username or password" );
        return;
    }

    if( mLoadedPasswords.find( userName ) == mLoadedPasswords.end() )
    {
        LogWarning( "Attempt to change a user's password for a user that doesn't exist." );
    }
    else
    {
        mLoadedPasswords[userName] = HashString( userName + newPassword );
    }
}

string SecurityManager::EncryptFile( const string fileNameToEncrypt, const string hash, const string outFileName )
{
    // Make sure we're not trying to open clearly invalid files
    tacAssert( fileNameToEncrypt != "" );
    tacAssert( hash != "" );

    // If an outOutFileName was not specified or is blank, then make the output
    // file result in the same file we are reading from
    string resultOutFileName("");
    if( outFileName == "" )
    {
        resultOutFileName = fileNameToEncrypt;
    }
    else
    {
        resultOutFileName = outFileName;
    }

    // Our buffer that will hold the entire file's contents for encrypting
    char* buffer = NULL;
    // The size (in # of elements) of that buffer
    int bufferSize = 0;

    // Open the file
    FILE *fileToRead = NULL;
    fileToRead = fopen( fileNameToEncrypt.c_str(), "rb" );
    if( fileToRead != NULL )
    {
        // Seek to the end to get the size of the file
        fseek( fileToRead, 0, SEEK_END );
        bufferSize = ftell( fileToRead );
        // Rewind it back to the beginning for the actual reading of the data
        rewind( fileToRead );

        LogInfo( string("Reading: ") + toString( bufferSize ) + string(" elements from ") + fileNameToEncrypt );

        // We want this file to not be empty
        tacAssert( bufferSize > 0 );
        // Allocate memory for the buffer
        buffer = new char[bufferSize];
        tacAssert( buffer != NULL );
        if( buffer == NULL )
        {
            LogError( string("Unable to allocate enough memory for  ") + fileNameToEncrypt );
            fclose( fileToRead );
            return "";
        }

        // Read it "one" big element, of size bufferSize (the whole file at once)
        int copyResult = fread( buffer, 1, bufferSize, fileToRead );
        tacAssert( copyResult == bufferSize );
        if( copyResult != bufferSize )
        {
            LogError( string("Reading error ") + fileNameToEncrypt );
            fclose( fileToRead );
            return "";
        }

        fclose( fileToRead );
    }
    else
    {
        // Unable to read to file for some reason
        tacAssert( false );
        LogError( string("Unable to read file to encrypt ") + fileNameToEncrypt );
        return "";
    }

    // Do encrypting here
    int hashLength = hash.size();
    // I am just doing this because it is probably faster
    const char * hashBuffer = hash.c_str();

    // Go through all the elements, and XOR each with an element in the hash
    // Skip through the buffer by the size of the hash
    for( int i = 0; i < bufferSize; i += hashLength )
    {
        // Go through this chunk XORing each element with the corresponding element
        // in the hash, make sure we're not stepping out of the total buffer size
        // (if the hashLength happens to be uneven)
        for( int j = 0; j < hashLength && i+j < bufferSize; ++j )
        {
            // This commented code was used as a debugging tool
            //LogInfo( string("Turning: ") + toString(buffer[i+j]) + string(" into: ") + toString(static_cast<char>(buffer[i+j] xor hashBuffer[j])) + string(" (hashing against: ") + toString( hashBuffer[j] ) );
            buffer[i+j] = buffer[i+j] xor hashBuffer[j];
        }
    }

    // Open the file we're writing this new encrypted version to
    FILE *fileToWrite = NULL;
    fileToWrite = fopen( resultOutFileName.c_str(), "wb" );
    if( fileToWrite != NULL )
    {
        // Attempt to write back to the file in one go, and if it didn't write that one
        // go we fail
        if( fwrite( buffer, bufferSize, 1, fileToWrite ) != 1 )
        {
            tacAssert( false );
            LogError( string("Error writing file out ") + resultOutFileName );
            fclose( fileToWrite );
            delete buffer;
            return "";
        }
        fclose( fileToWrite );
    }

    // Clean up our allocated memory
    delete[] buffer;

    return resultOutFileName;
}

string SecurityManager::DecryptFile( const string fileNameToDecrypt, const string hash, const string outFileName )
{
    // Make sure we're not trying to open clearly invalid files
    tacAssert( fileNameToDecrypt != "" );
    tacAssert( hash != "" );

    // If an outOutFileName was not specified or is blank, then make the output
    // file result in the same file we are reading from
    string resultOutFileName("");
    if( outFileName == "" )
    {
        resultOutFileName = fileNameToDecrypt;
    }
    else
    {
        resultOutFileName = outFileName;
    }

    // Our buffer that will hold the entire file's contents for decrypting
    char* buffer = NULL;
    // The size (in # of elements) of that buffer
    int bufferSize = 0;

    // Open the file
    FILE *fileToRead = NULL;
    fileToRead = fopen( fileNameToDecrypt.c_str(), "rb" );
    if( fileToRead != NULL )
    {
        // Seek to the end to get the size of the file
        if( fseek( fileToRead, 0, SEEK_END ) != 0 )
        {
            tacAssert( false );
            LogError( string("Unabled to seek to end of file ") + fileNameToDecrypt );
            fclose( fileToRead );
            return "";
        }

        bufferSize = ftell( fileToRead );
        // Rewind it back to the beginning for the actual reading of the data
        rewind( fileToRead );

        LogInfo( string("Reading: ") + toString( bufferSize ) + string(" elements from ") + fileNameToDecrypt );

        // We want this file to not be empty
        tacAssert( bufferSize > 0 );
        if( bufferSize < 1 )
        {
            LogError( string("File is empty?  ") + fileNameToDecrypt );
            fclose( fileToRead );
            return "";
        }

        // Allocate memory for the buffer
        buffer = new char[bufferSize];
        tacAssert( buffer != NULL );
        if( buffer == NULL )
        {
            LogError( string("Unable to allocate enough memory for  ") + fileNameToDecrypt );
            fclose( fileToRead );
            return "";
        }

        // Read it "one" big element, of size bufferSize (the whole file at once)
        int copyResult = fread( buffer, 1, bufferSize, fileToRead );
        tacAssert( copyResult == bufferSize );
        if( copyResult != bufferSize )
        {
            LogError( string("Reading error ") + fileNameToDecrypt );
            fclose( fileToRead );
            return "";
        }

        fclose( fileToRead );
    }
    else
    {
        // Unable to read to file for some reason
        tacAssert( false );
        LogError( string("Unable to read file to decrypt ") + fileNameToDecrypt );
        return "";
    }

    // Do decrypting here
    int hashLength = hash.size();
    // I am just doing this because it is probably faster
    const char * hashBuffer = hash.c_str();

    // Go through all the elements, and XOR each with an element in the hash
    // Skip through the buffer by the size of the hash
    for( int i = 0; i < bufferSize; i += hashLength )
    {
        // Go through this chunk XORing each element with the corresponding element
        // in the hash, make sure we're not stepping out of the total buffer size
        // (if the hashLength happens to be uneven)
        for( int j = 0; j < hashLength && i+j < bufferSize; ++j )
        {
            // This commented code was used as a debugging tool
            //LogInfo( string("Turning: ") + toString(buffer[i+j]) + string(" into: ") + toString(static_cast<char>(buffer[i+j] xor hashBuffer[j])) + string(" (hashing against: ") + toString( hashBuffer[j] ) );
            buffer[i+j] = buffer[i+j] xor hashBuffer[j];
        }
    }

    // Open the file we're writing this new decrypted version to
    FILE *fileToWrite = NULL;
    fileToWrite = fopen( resultOutFileName.c_str(), "wb" );
    if( fileToWrite != NULL )
    {
        // Attempt to write back to the file in one go, and if it didn't write that one
        // go we fail
        if( fwrite( buffer, sizeof(char), bufferSize, fileToWrite ) != static_cast<unsigned int>( bufferSize ) )
        {
            tacAssert( false );
            LogError( string("Error writing file out ") + resultOutFileName );
            fclose( fileToWrite );
            delete buffer;
            return "";
        }
        fclose( fileToWrite );
    }

    // Clean up our allocated memory
    delete[] buffer;

    return resultOutFileName;
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
        output += toString((curDigit * (1 + i + curDigit/2)) % 2000);
    }
    return output;
}

/////////////////////////////// PRIVATE    ///////////////////////////////////
