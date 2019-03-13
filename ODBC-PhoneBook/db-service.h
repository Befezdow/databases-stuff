#ifndef DBSERVICE_H
#define DBSERVICE_H

#include "contact.h"
#include "email.h"
#include "number.h"
#include <sql.h>
#include <vector>

class DBService {

    SQLHENV henv;
    SQLHDBC hdbc;

public:
    DBService();
    ~DBService();

    bool initService();

    std::vector<Contact> getAllContacts(bool sortById = false);
    std::vector<Contact> getContactsByMask(std::string mask);
    Contact getContactById(int id, bool &ok);
    void insertOneContact(Contact newContact);
    void deleteContactById(int id);
    void updateContactById(Contact newData, int id);

    std::vector<Email> getEmailsByOwnerId(int ownerId);
    void insertOneEmail(Email newEmail);
    void deleteEmailById(int id);
    void deleteEmailsByOwnerId(int ownerId);
    void updateEmailById(std::string newEmailAddress, int id);

    std::vector<Number> getNumbersByOwnerId(int ownerId);
    void insertOneNumber(Number newNumber);
    void deleteNumberById(int id);
    void deleteNumbersByOwnerId(int ownerId);
    void updateNumberById(std::string newPhoneNumber, int id);
};

#endif // DBSERVICE_H
