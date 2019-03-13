#ifndef CONTACT_H
#define CONTACT_H

#include <sql.h>
#include <iostream>
#include <cstring>

class Contact {

    SQLINTEGER id;
    SQLVARCHAR firstName[64];
    SQLVARCHAR lastName[64];
    SQLVARCHAR patronymic[64];
    SQLVARCHAR address[64];
    SQLVARCHAR comment[256];

    SQLLEN addressIndicator;
    SQLLEN commentIndicator;

public:
    Contact();
    Contact(std::string firstName, std::string lastName, std::string patronymic,
            std::string address, std::string comment);
    void bindForInput(SQLHSTMT hstmt);
    void bindForOutput(SQLHSTMT hstmt);

    SQLINTEGER getId() const;
    const SQLVARCHAR* getFirstName() const;
    const SQLVARCHAR* getLastName() const;
    const SQLVARCHAR* getPatronymic() const;
    const SQLVARCHAR* getAddress() const;
    const SQLVARCHAR* getComment() const;

    void setFirstName(std::string newFirstName);
    void setLastName(std::string newLastName);
    void setPatronymic(std::string newPatronymic);
    void setAddress(std::string newAddress);
    void setComment(std::string newComment);

    void print(std::ostream& stream, bool withId = false);
    void printDetail(std::ostream &stream);
};

#endif // CONTACT_H
