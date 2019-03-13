#ifndef NUMBER_H
#define NUMBER_H

#include <sql.h>
#include <iostream>
#include <cstring>

class Number {
    SQLINTEGER id;
    SQLVARCHAR phoneNumber[12];
    SQLINTEGER numberOwner;

public:
    Number();
    Number(std::string phoneNumber, int numberOwner);

    void bindForInput(SQLHSTMT hstmt);
    void bindForOutput(SQLHSTMT hstmt, int &temp);

    SQLINTEGER getId() const;
    const SQLVARCHAR* getPhoneNumber() const;
    SQLINTEGER getNumberOwner() const;

    void setPhoneNumber(std::string newPhoneNumber);

    void print(std::ostream& stream, bool withId = false);
};

#endif // NUMBER_H
