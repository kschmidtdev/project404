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
 * Karl Schmidt, February 15 2007 | Added HashString function
 * Karl Schmidt, February 13 2007 | Initial creation of header
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

    void LoadPasswordHashFile( const string fileName );

    void SavePasswordHashFile( const string fileName );

    bool VerifyPassword( const string userName, const string password );

    void AddUser( const string userName, const string password );

    void DeleteUser( const string userName );

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
