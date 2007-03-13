/**
 * A provider of security functionality
 *
 * #include "SecurityManager.h"
 *
 * A provider of security functionality,
 * such as verifying passwords against hashes,
 * encrypting data, decrypting data
 *
 *
 * Project 404 2007
 *
 * Authors:
 * Karl Schmidt, February 15 2007 | Implemented DeleteUser and ChangeUserPassword
 * Karl Schmidt, February 15 2007 | Added HashString function
 * Karl Schmidt, February 13 2007 | Initial creation of header
 * Karl Schmidt, March 11 2007	   | Added file encryption/decryption routines
 * Karl Schmidt, March 12 2007    | Added DecryptFileToString
 */

#ifndef SecurityManager_h
#define SecurityManager_h

// SYSTEM INCLUDES
//
#include <map>
#include <string>

using namespace std;

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

typedef map<string, string> PasswordHashMap;
typedef PasswordHashMap::iterator PasswordHashMapItr;

class SecurityManager
{
public:
// LIFECYCLE

    /**
    * Returns an instance of the SecurityManager
    */
    static SecurityManager* GetInstance();

    /**
    * Destructor.
    */
    virtual ~SecurityManager(void);

    /**
    * Initializes the securitymanager,
    * loads password hash file
    */
    void Initialize();

    /**
    * Shuts the security manager down,
    * performs any necessary cleanup
    */
    void Shutdown();

// OPERATORS
// OPERATIONS

    /**
    * Loads a password hash file into
    * mLoadedPasswords
    */
    void LoadPasswordHashFile( const string fileName );

    /**
    * Saves out mLoadedPasswords
    * to fileName
    */
    void SavePasswordHashFile( const string fileName );

    /**
    * Hashs the incoming password and compares
    * that to the stored password hash for the particular user.
    * Returns true if they are equal, false if they are not
    */
    bool VerifyPassword( const string userName, const string password );

    /**
    * Adds a user and hashs the password and stores them in
    * mLoadedPasswords
    */
    void AddUser( const string userName, const string password );

    /**
    * Deletes a user from mLoadedPasswords
    */
    void DeleteUser( const string userName );

    /**
    * Changes the password of a user in
    * mLoadedPasswords
    */
    void ChangeUserPassword( const string userName, const string newPassword );

    /**
    * Encrypts the incoming file's contents (based on the filename) if it can
    * access the file, and if the outFileName is not specified it will overwrite
    * the incoming file's contents with the encrypted version.
    * It returns the filename of the file it ended up writing the encrypted version to.
    */
    string EncryptFile( const string fileNameToEncrypt, const string hash, const string outFileName = "" );

    /**
    * Decrypts the incoming file's contents (based on the filename) if it can
    * access the file, and if the outFileName is not specified it will overwrite
    * the incoming file's contents with the decrypted version.
    * It returns the filename of the file it ended up writing the decrypted version to.
    */
    string DecryptFile( const string fileNameToDecrypt, const string hash, const string outFileName = "" );

    /**
    * Decrypts the incoming file's contents (based on the filename) if it can
    * access the file.
    * It returns the contents of the file in a decrypted form.
    */
    string DecryptFileToString( const string fileNameToDecrypt, const string hash );

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED METHODS
    /**
     * Default constructor.
	 */
    SecurityManager(void);

    string HashString( const string incoming );

// PROTECTED VARIABLES
    static SecurityManager* _instance;
    PasswordHashMap mLoadedPasswords;
    string mCurrentHashFilename;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _SecurityManager_h_
