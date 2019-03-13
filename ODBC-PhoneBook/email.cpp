#include "email.h"

#include <sqlext.h>
#include <sqltypes.h>

Email::Email() {}

Email::Email(std::__cxx11::string emailAddress, int emailOwner) {
    strncpy((char*)this->emailAddress, emailAddress.c_str(), 64);
    this->emailOwner = emailOwner;
}

void Email::bindForInput(SQLHSTMT hstmt) {

    bool flag = true;
    flag = flag && SQLBindCol(hstmt, 1, SQL_C_LONG, &id, sizeof(id), nullptr) == SQL_SUCCESS;
    flag = flag && SQLBindCol(hstmt, 2, SQL_C_CHAR, &emailAddress, sizeof(emailAddress), nullptr) == SQL_SUCCESS;
    flag = flag && SQLBindCol(hstmt, 3, SQL_C_LONG, &emailOwner, sizeof(emailOwner), nullptr) == SQL_SUCCESS;

    if (!flag) {
        throw "Email :: bindForinput : Binding failed";
    }
}

void Email::bindForOutput(SQLHSTMT hstmt, int &temp){

    temp = this->getEmailOwner();

    bool flag = true;

    flag = flag && SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                                    64, 0, (SQLPOINTER)this->getEmailAddress(), 64,
                                    NULL) == SQL_SUCCESS;

    flag = flag && SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
                                    0, 0, &temp, 0,
                                    NULL) == SQL_SUCCESS;

    if (!flag) {
        throw "Email :: bindForOutput : Binding error";
    }
}

SQLINTEGER Email::getId() const {
    return id;
}

const SQLVARCHAR *Email::getEmailAddress() const {
    return emailAddress;
}

const SQLINTEGER Email::getEmailOwner() const {
    return emailOwner;
}

void Email::setEmailAddress(std::__cxx11::string newEmailAddress) {

    strncpy((char*)emailAddress, newEmailAddress.c_str(), 64);
}

void Email::print(std::ostream &stream, bool withId) {
    if (withId) {
        stream << id << "\t";
    }
    stream << emailAddress << std::endl;
}
