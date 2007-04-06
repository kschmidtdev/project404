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
 * Karl Schmidt, March 11 2007	  | Added file encryption/decryption routines
 * Karl Schmidt, March 12 2007    | Added DecryptFileToString
 * Karl Schmidt, March 15 2007    | Made std::string params refs, added GetUserHash
 * Karl Schmidt, March 20 2007    | Took out potentially bad using namespace std;
 * Karl Schmidt, March 25 2007    | Added some helper functions other subsystems needed
 */

#ifndef SecurityManager_h
#define SecurityManager_h

// SYSTEM INCLUDES
//
#include <map>
#include <string>
#include <vector>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// FORWARD REFERENCES
//

typedef std::map<std::string, std::string> PasswordHashMap;
typedef PasswordHashMap::iterator PasswordHashMapItr;
typedef PasswordHashMap::const_iterator PasswordHashMapConstItr;

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
    void LoadPasswordHashFile( const std::string & fileName );

    /**
    * Saves out mLoadedPasswords
    * to fileName
    */
    void SavePasswordHashFile( const std::string & fileName );

    /**
    * Hashs the incoming password and compares
    * that to the stored password hash for the particular user.
    * Returns true if they are equal, false if they are not
    */
    bool VerifyPassword( const std::string & userName, const std::string & password );

    /**
    * Adds a user and hashs the password and stores them in
    * mLoadedPasswords
    */
    void AddUser( const std::string & userName, const std::string & password );

    /**
    * Deletes a user from mLoadedPasswords
    */
    void DeleteUser( const std::string & userName );

    /**
    * Changes the password of a user in
    * mLoadedPasswords
    */
    void ChangeUserPassword( const std::string & userName, const std::string & newPassword );

    /**
    * Encrypts the incoming file's contents (based on the filename) if it can
    * access the file, and if the outFileName is not specified it will overwrite
    * the incoming file's contents with the encrypted version.
    * It returns the filename of the file it ended up writing the encrypted version to.
    */
    std::string EncryptFile( const std::string & fileNameToEncrypt, const std::string & hash, const std::string & outFileName = "" );

    /**
    * Decrypts the incoming file's contents (based on the filename) if it can
    * access the file, and if the outFileName is not specified it will overwrite
    * the incoming file's contents with the decrypted version.
    * It returns the filename of the file it ended up writing the decrypted version to.
    */
    std::string DecryptFile( const std::string & fileNameToDecrypt, const std::string & hash, const std::string & outFileName = "" );

    /**
    * Decrypts the incoming file's contents (based on the filename) if it can
    * access the file.
    * It returns the contents of the file in a decrypted form.
    */
    std::string DecryptFileToString( const std::string & fileNameToDecrypt, const std::string & hash );

    /**
    * Finds the user in the list of loaded users, and
    * returns their hash, if no user is found a blank std::string is returned
    */
    const std::string GetUserHash( const std::string & userName );

    /**
    * Returns a vector of strings that represent all the loaded usernames
    */
    const std::vector< std::string > GetListOfLoadedUsernames() const;

    /**
    * Returns the number of usernames currently loaded
    */
    const int GetNumOfUsers() const;

    void ChangeUserHash( const std::string & userName, const std::string & newHash );

// ACCESS (writing)
// INQUIRY (reading)

protected:
// PROTECTED METHODS
    /**
     * Default constructor.
	 */
    SecurityManager(void);

    std::string HashString( const std::string & incoming );

// PROTECTED VARIABLES
    static SecurityManager* _instance;
    PasswordHashMap mLoadedPasswords;
    std::string mCurrentHashFilename;

private:
// PRIVATE VARIABLES
};

// INLINE METHODS
//

// EXTERNAL REFERENCES
//

#endif  // _SecurityManager_h_
