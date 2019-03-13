#include "db-service.h"

#include <sqlext.h>

DBService::DBService(): henv(nullptr), hdbc(nullptr) {}

DBService::~DBService() {
    SQLDisconnect(hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
}

bool DBService::initService() {

    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv) == SQL_ERROR) {
        std::cerr << "Error with the first allocation handling" << std::endl;
        return false;
    }

    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, SQL_IS_INTEGER);

    hdbc = nullptr;

    if (SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc) == SQL_ERROR) {
        std::cerr << "Error with the second allocation handling" << std::endl;
        return false;
    }

    if (SQLConnect(hdbc, (SQLTCHAR*)"source", SQL_NTS, (SQLTCHAR*)"bef", SQL_NTS, (SQLTCHAR*)"", SQL_NTS) == SQL_ERROR) {
        std::cerr << "Error with connecting to DB" << std::endl;
        return false;
    }

    return true;
}

std::vector<Contact> DBService::getAllContacts(bool sortById) {

    SQLHSTMT cursor;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &cursor) == SQL_ERROR) {
        throw "DBService :: getAllContacts : Handle allocation error";
    }

    SQLCHAR * request;
    if (sortById) {
        request = (SQLCHAR *)"SELECT id, firstname, lastname, patronymic, address, comment "
                  "FROM contact ORDER BY id ASC";
    } else {
        request = (SQLCHAR *)"SELECT id, firstname, lastname, patronymic, address, comment "
                  "FROM contact ORDER BY firstname, lastname, patronymic ASC";
    }

    if (SQLPrepare(cursor, request, SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: getAllContacts : Preparing error";
    }

    Contact contact;
    try {
        contact.bindForInput(cursor);
    } catch (const char* err) {
        throw err;
    }

    if (SQLExecute(cursor) !=  SQL_SUCCESS) {
        throw "DBService :: getAllContacts : Execution error";
    }

    std::vector<Contact> result;
    while(SQLFetch(cursor) != SQL_NO_DATA) {
        result.push_back(contact);
    }

    SQLCloseCursor(cursor);

    return result;
}

std::vector<Contact> DBService::getContactsByMask(std::__cxx11::string mask) {

    SQLHSTMT cursor;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &cursor) == SQL_ERROR) {
        throw "DBService :: getContactsByMask : Handle allocation error";
    }

    if (SQLPrepare(cursor, (SQLCHAR *) "SELECT id, firstname, lastname, patronymic, address, comment "
                   "FROM contact WHERE firstname LIKE ? OR lastname LIKE ? OR patronymic LIKE ?", SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: getContactsByMask : Preparing error";
    }

    if (SQLBindParameter(cursor, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                         0, 0, (SQLPOINTER)mask.c_str(), SQL_NTS, NULL) != SQL_SUCCESS) {
        throw "DBService :: getContactsByMask : Binding error";
    }

    if (SQLBindParameter(cursor, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                         0, 0, (SQLPOINTER)mask.c_str(), SQL_NTS, NULL) != SQL_SUCCESS) {
        throw "DBService :: getContactsByMask : Binding error";
    }

    if (SQLBindParameter(cursor, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                         0, 0, (SQLPOINTER)mask.c_str(), SQL_NTS, NULL) != SQL_SUCCESS) {
        throw "DBService :: getContactsByMask : Binding error";
    }

    Contact contact;
    try {
        contact.bindForInput(cursor);
    } catch (const char* err) {
        throw err;
    }

    if (SQLExecute(cursor) !=  SQL_SUCCESS) {
        throw "DBService :: getContactsByMask : Execution error";
    }

    std::vector<Contact> result;
    while(SQLFetch(cursor) != SQL_NO_DATA) {
        result.push_back(contact);
    }

    SQLCloseCursor(cursor);

    return result;
}

void DBService::insertOneContact(Contact newContact) {

    SQLHSTMT statement;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &statement) == SQL_ERROR) {
        throw "DBService :: insertOneContact : Handle allocation error";
    }

    if (SQLPrepare(statement, (SQLCHAR*)"INSERT INTO contact "
                   "(firstname, lastname, patronymic, address, comment) "
                   "values(?,?,?,?,?)", SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: insertOneContact : Preparing error";
    }

    try {
        newContact.bindForOutput(statement);
    } catch (const char* err) {
        throw err;
    }

    if (SQLExecute(statement) !=  SQL_SUCCESS) {
        throw "DBService :: insertOneContact : Execution error";
    }

    SQLCloseCursor(statement);
}

Contact DBService::getContactById(int id, bool& ok) {

    SQLHSTMT hstmt;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt) == SQL_ERROR) {
        throw "DBService :: getContactById : Handle allocation error";
    }

    if (SQLPrepare(hstmt, (SQLCHAR *) "SELECT id, firstname, lastname, patronymic, address, comment  FROM contact WHERE id=?", SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: getContactById : Preparing error";
    }

    if (SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
                                        0, 0, &id, 0, NULL) != SQL_SUCCESS) {
        throw "DBService :: getContactById : Binding error";
    }

    Contact contact;
    try {
        contact.bindForInput(hstmt);
    } catch (const char* err) {
        throw err;
    }

    if (SQLExecute(hstmt) !=  SQL_SUCCESS) {
        throw "DBService :: getContactById : Execution error";
    }

    if (SQLFetch(hstmt) != SQL_NO_DATA) {
        ok = false;
    } else {
        ok = true;
    }

    SQLCloseCursor(hstmt);

    return contact;
}

void DBService::deleteContactById(int id) {

    SQLHSTMT hstmt;

    deleteEmailsByOwnerId(id);
    deleteNumbersByOwnerId(id);

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt) == SQL_ERROR) {
        throw "DBService :: deleteContactById : Handle allocation error";
    }

    if (SQLPrepare(hstmt, (SQLCHAR *) "DELETE FROM contact WHERE id=?", SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: deleteContactById : Preparing error";
    }

    if (SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
                                        0, 0, &id, 0, NULL) != SQL_SUCCESS) {
        throw "DBService :: deleteContactById : Binding error";
    }

    if (SQLExecute(hstmt) !=  SQL_SUCCESS) {
        throw "DBService :: deleteContactById : Execution error";
    }

    SQLCloseCursor(hstmt);
}

void DBService::updateContactById(Contact newData, int id) {

    SQLHSTMT statement;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &statement) == SQL_ERROR) {
        throw "DBService :: updateContactById : Handle allocation error";
    }

    if (SQLPrepare(statement, (SQLCHAR*)"UPDATE contact "
                   "SET firstname=?, lastname=?, patronymic=?, address=?, comment=? "
                   "WHERE id=?", SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: updateContactById : Preparing error";
    }

    try {
        newData.bindForOutput(statement);
    } catch (const char* err) {
        throw err;
    }

    if (SQLBindParameter(statement, 6, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
                         0, 0, &id, 0, NULL) != SQL_SUCCESS) {
        throw "DBService :: updateContactById : Binding error";
    }

    if (SQLExecute(statement) !=  SQL_SUCCESS) {
        SQLCloseCursor(statement);
        throw "DBService :: updateContactById : Execution error";
    }

    SQLCloseCursor(statement);
}

std::vector<Email> DBService::getEmailsByOwnerId(int ownerId) {

    SQLHSTMT cursor;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &cursor) == SQL_ERROR) {
        throw "DBService :: getEmailsByOwnerId : Handle allocation error";
    }

    if (SQLPrepare(cursor, (SQLCHAR *) "SELECT id, email_address, email_owner FROM email WHERE email_owner=?", SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: getEmailsByOwnerId : Preparing error";
    }

    if (SQLBindParameter(cursor, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
                         0, 0, &ownerId, 0, NULL) != SQL_SUCCESS) {
        throw "DBService :: getEmailsByOwnerId : Binding error";
    }

    Email email;
    try {
        email.bindForInput(cursor);
    } catch (const char* err) {
        throw err;
    }

    if (SQLExecute(cursor) !=  SQL_SUCCESS) {
        throw "DBService :: getEmailsByOwnerId : Execution error";
    }

    std::vector<Email> result;
    while(SQLFetch(cursor) != SQL_NO_DATA) {
        result.push_back(email);
    }

    SQLCloseCursor(cursor);

    return result;
}

void DBService::insertOneEmail(Email newEmail)
{
    SQLHSTMT statement;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &statement) == SQL_ERROR) {
        throw "DBService :: insertOneEmail : Handle allocation error";
    }

    if (SQLPrepare(statement, (SQLCHAR*)"INSERT INTO email "
                   "(email_address, email_owner) "
                   "values(?,?)", SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: insertOneEmail : Preparing error";
    }

    try {
        int temp;
        newEmail.bindForOutput(statement, temp);
    } catch (const char* err) {
        throw err;
    }

    if (SQLExecute(statement) !=  SQL_SUCCESS) {
        throw "DBService :: insertOneEmail : Execution error";
    }

    SQLCloseCursor(statement);
}

void DBService::deleteEmailById(int id) {

    SQLHSTMT hstmt;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt) == SQL_ERROR) {
        throw "DBService :: deleteEmailById : Handle allocation error";
    }

    if (SQLPrepare(hstmt, (SQLCHAR *) "DELETE FROM email WHERE id=?", SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: deleteEmailById : Preparing error";
    }

    if (SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
                                        0, 0, &id, 0, NULL) != SQL_SUCCESS) {
        throw "DBService :: deleteEmailById : Binding error";
    }

    if (SQLExecute(hstmt) !=  SQL_SUCCESS) {
        throw "DBService :: deleteEmailById : Execution error";
    }

    SQLCloseCursor(hstmt);
}

void DBService::deleteEmailsByOwnerId(int ownerId) {

    SQLHSTMT hstmt;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt) == SQL_ERROR) {
        throw "DBService :: deleteEmailsByOwnerId : Handle allocation error";
    }

    if (SQLPrepare(hstmt, (SQLCHAR *) "DELETE FROM email WHERE email_owner=?", SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: deleteEmailsByOwnerId : Preparing error";
    }

    if (SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
                                        0, 0, &ownerId, 0, NULL) != SQL_SUCCESS) {
        throw "DBService :: deleteEmailsByOwnerId : Binding error";
    }

    SQLRETURN res = SQLExecute(hstmt);
    if (res != SQL_SUCCESS && res != SQL_NO_DATA) {
        throw "DBService :: deleteEmailsByOwnerId : Execution error";
    }

    SQLCloseCursor(hstmt);
}

void DBService::updateEmailById(std::__cxx11::string newEmailAddress, int id) {

    SQLHSTMT statement;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &statement) == SQL_ERROR) {
        throw "DBService :: updateEmailById : Handle allocation error";
    }

    if (SQLPrepare(statement, (SQLCHAR*)"UPDATE email SET email_address=? WHERE id=?",
                   SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: updateEmailById : Preparing error";
    }

    char temp[64];
    strncpy(temp, newEmailAddress.c_str(), 64);

    if (SQLBindParameter(statement, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                         64, 0, (SQLPOINTER)temp, 64, NULL) != SQL_SUCCESS) {
        throw "DBService :: updateEmailById : Binding error";
    }

    if (SQLBindParameter(statement, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
                         0, 0, &id, 0, NULL) != SQL_SUCCESS) {
        throw "DBService :: updateEmailById : Binding error";
    }

    if (SQLExecute(statement) !=  SQL_SUCCESS) {
        throw "DBService :: updateEmailById : Execution error";
    }

    SQLCloseCursor(statement);
}

std::vector<Number> DBService::getNumbersByOwnerId(int ownerId) {

    SQLHSTMT cursor;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &cursor) == SQL_ERROR) {
        throw "DBService :: getNumbersByOwnerId : Handle allocation error";
    }

    if (SQLPrepare(cursor, (SQLCHAR *) "SELECT id, phone_number, number_owner FROM number WHERE number_owner=?", SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: getNumbersByOwnerId : Preparing error";
    }

    if (SQLBindParameter(cursor, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
                         0, 0, &ownerId, 0, NULL) != SQL_SUCCESS) {
        throw "DBService :: getNumbersByOwnerId : Binding error";
    }

    Number number;
    try {
        number.bindForInput(cursor);
    } catch (const char* err) {
        throw err;
    }

    if (SQLExecute(cursor) !=  SQL_SUCCESS) {
        throw "DBService :: getNumbersByOwnerId : Execution error";
    }

    std::vector<Number> result;
    while(SQLFetch(cursor) != SQL_NO_DATA) {
        result.push_back(number);
    }

    SQLCloseCursor(cursor);

    return result;
}

void DBService::insertOneNumber(Number newNumber) {

    SQLHSTMT statement;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &statement) == SQL_ERROR) {
        throw "DBService :: insertOneNumber : Handle allocation error";
    }

    if (SQLPrepare(statement, (SQLCHAR*)"INSERT INTO number (phone_number, number_owner) "
                                        "values(?,?)", SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: insertOneNumber : Preparing error";
    }

    try {
        int temp;
        newNumber.bindForOutput(statement, temp);
    } catch (const char* err) {
        throw err;
    }

    if (SQLExecute(statement) != SQL_SUCCESS) {
        throw "DBService :: insertOneNumber : Execution error";
    }

    SQLCloseCursor(statement);
}

void DBService::deleteNumberById(int id) {

    SQLHSTMT hstmt;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt) == SQL_ERROR) {
        throw "DBService :: deleteNumberById : Handle allocation error";
    }

    if (SQLPrepare(hstmt, (SQLCHAR *) "DELETE FROM number WHERE id=?", SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: deleteNumberById : Preparing error";
    }

    if (SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
                                        0, 0, &id, 0, NULL) != SQL_SUCCESS) {
        throw "DBService :: deleteNumberById : Binding error";
    }

    if (SQLExecute(hstmt) !=  SQL_SUCCESS) {
        throw "DBService :: deleteNumberById : Execution error";
    }

    SQLCloseCursor(hstmt);
}

void DBService::deleteNumbersByOwnerId(int ownerId) {

    SQLHSTMT hstmt;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt) == SQL_ERROR) {
        throw "DBService :: deleteNumbersByOwnerId : Handle allocation error";
    }

    if (SQLPrepare(hstmt, (SQLCHAR *) "DELETE FROM number WHERE number_owner=?", SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: deleteNumbersByOwnerId : Preparing error";
    }

    if (SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
                                        0, 0, &ownerId, 0, NULL) != SQL_SUCCESS) {
        throw "DBService :: deleteNumbersByOwnerId : Binding error";
    }

    SQLRETURN res = SQLExecute(hstmt);
    if (res != SQL_SUCCESS && res != SQL_NO_DATA) {
        throw "DBService :: deleteNumbersByOwnerId : Execution error";
    }

    SQLCloseCursor(hstmt);
}

void DBService::updateNumberById(std::__cxx11::string newPhoneNumber, int id) {

    SQLHSTMT statement;

    if (SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &statement) == SQL_ERROR) {
        throw "DBService :: updateNumberById : Handle allocation error";
    }

    if (SQLPrepare(statement, (SQLCHAR*)"UPDATE number SET phone_number=? WHERE id=?",
                   SQL_NTS) != SQL_SUCCESS) {
        throw "DBService :: updateNumberById : Preparing error";
    }

    char temp[64];
    strncpy(temp, newPhoneNumber.c_str(), 64);

    if (SQLBindParameter(statement, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                         64, 0, (SQLPOINTER)temp, 64, NULL) != SQL_SUCCESS) {
        throw "DBService :: updateNumberById : Binding error";
    }

    if (SQLBindParameter(statement, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
                         0, 0, &id, 0, NULL) != SQL_SUCCESS) {
        throw "DBService :: updateNumberById : Binding error";
    }

    if (SQLExecute(statement) !=  SQL_SUCCESS) {
        throw "DBService :: updateNumberById : Execution error";
    }

    SQLCloseCursor(statement);
}
