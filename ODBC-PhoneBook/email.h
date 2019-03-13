#ifndef EMAIL_H
#define EMAIL_H

#include <sql.h>
#include <iostream>
#include <cstring>

class Email {

    SQLINTEGER id;
    SQLVARCHAR emailAddress[64];
    SQLINTEGER emailOwner;

public:
    Email();
    Email(std::string emailAddress, int emailOwner);

    void bindForInput(SQLHSTMT hstmt);
    void bindForOutput(SQLHSTMT hstmt, int& temp);

    SQLINTEGER getId() const;
    const SQLVARCHAR* getEmailAddress() const;
    const SQLINTEGER getEmailOwner() const;

    void setEmailAddress(std::string newEmailAddress);

    void print(std::ostream& stream, bool withId = false);
};


#endif // EMAIL_H
