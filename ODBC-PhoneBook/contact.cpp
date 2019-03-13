#include "contact.h"

#include <sqlext.h>
#include <sqltypes.h>

Contact::Contact() {}

Contact::Contact(std::__cxx11::string firstName, std::__cxx11::string lastName, std::__cxx11::string patronymic, std::__cxx11::string address, std::__cxx11::string comment) {

    strncpy((char*)this->firstName, firstName.c_str(), 64);
    strncpy((char*)this->lastName, lastName.c_str(), 64);
    strncpy((char*)this->patronymic, patronymic.c_str(), 64);

    if (address.empty()) {
        addressIndicator = false;
    } else {
        addressIndicator = true;
        strncpy((char*)this->address, address.c_str(), 64);
    }

    if (comment.empty()) {
        commentIndicator = false;
    } else {
        commentIndicator = true;
        strncpy((char*)this->comment, comment.c_str(), 256);
    }
}

void Contact::bindForInput(SQLHSTMT hstmt) {
    bool flag = true;
    flag = flag && SQLBindCol(hstmt, 1, SQL_C_LONG, &id, sizeof(id), nullptr) == SQL_SUCCESS;
    flag = flag && SQLBindCol(hstmt, 2, SQL_C_CHAR, &firstName, sizeof(firstName), nullptr) == SQL_SUCCESS;
    flag = flag && SQLBindCol(hstmt, 3, SQL_C_CHAR, &lastName, sizeof(lastName), nullptr) == SQL_SUCCESS;
    flag = flag && SQLBindCol(hstmt, 4, SQL_C_CHAR, &patronymic, sizeof(patronymic), nullptr) == SQL_SUCCESS;
    flag = flag && SQLBindCol(hstmt, 5, SQL_C_CHAR, &address, sizeof(address), &addressIndicator) == SQL_SUCCESS;
    flag = flag && SQLBindCol(hstmt, 6, SQL_C_CHAR, &comment, sizeof(comment), &commentIndicator) == SQL_SUCCESS;

    if (!flag) {
        throw "Contact :: bindForinput : Binding failed";
    }
}

void Contact::bindForOutput(SQLHSTMT hstmt) {
    bool flag = true;

    flag = flag && SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                                    64, 0, (SQLPOINTER)this->getFirstName(), 64,
                                    NULL) == SQL_SUCCESS;

    flag = flag && SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                                    64, 0, (SQLPOINTER)this->getLastName(), 64,
                                    NULL) == SQL_SUCCESS;

    flag = flag && SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                                    64, 0, (SQLPOINTER)this->getPatronymic(), 64,
                                    NULL) == SQL_SUCCESS;

    SQLLEN indicator = SQL_NULL_DATA;
    flag = flag && SQLBindParameter(hstmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                                    64, 0, (SQLPOINTER)this->getAddress(), 64,
                                    this->addressIndicator ? NULL : &indicator) == SQL_SUCCESS;

    flag = flag && SQLBindParameter(hstmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                                    256, 0, (SQLPOINTER)this->getComment(), 256,
                                    this->commentIndicator ? NULL : &indicator) == SQL_SUCCESS;

    if (!flag) {
        throw "Contact :: bindForOutput : Binding error";
    }
}

SQLINTEGER Contact::getId() const {
    return this->id;
}

const SQLVARCHAR *Contact::getFirstName() const {
    return this->firstName;
}

const SQLVARCHAR *Contact::getLastName() const {
    return this->lastName;
}

const SQLVARCHAR *Contact::getPatronymic() const {
    return this->patronymic;
}

const SQLVARCHAR *Contact::getAddress() const {
//    return this->addressIndicator ? this->address : NULL;
    return (SQLVARCHAR*)this->address;
}

const SQLVARCHAR *Contact::getComment() const {
//    return this->commentIndicator ? this->comment : nullptr;
    return (SQLVARCHAR*)this->comment;
}

void Contact::setFirstName(std::__cxx11::string newFirstName) {

    strncpy((char*)firstName, newFirstName.c_str(), 64);
}

void Contact::setLastName(std::__cxx11::string newLastName) {

    strncpy((char*)lastName, newLastName.c_str(), 64);
}

void Contact::setPatronymic(std::__cxx11::string newPatronymic) {

    strncpy((char*)patronymic, newPatronymic.c_str(), 64);
}

void Contact::setAddress(std::__cxx11::string newAddress) {

    if (newAddress.empty()) {
        addressIndicator = false;
    } else {
        addressIndicator = true;
    }
    strncpy((char*)address, newAddress.c_str(), 64);
}

void Contact::setComment(std::__cxx11::string newComment) {

    if (newComment.empty()) {
        commentIndicator = false;
    } else {
        commentIndicator = true;
    }
    strncpy((char*)comment, newComment.c_str(), 256);
}

void Contact::print(std::ostream &stream, bool withId) {

    if (withId) {
        stream << id << "\t";
    }

    stream << firstName << "\t" << lastName << "\t" << patronymic << "\t";

    if (addressIndicator == SQL_NULL_DATA) {
        stream << "Нет адреса\t";
    } else {
        stream << address << "\t";
    }

    if (commentIndicator == SQL_NULL_DATA) {
        stream << "Нет комментария";
    } else {
        stream << comment;
    }

    stream << std::endl;
}

void Contact::printDetail(std::ostream &stream) {
    stream << "Имя: " << firstName << std::endl;
    stream << "Фамилия: " << lastName << std::endl;
    stream << "Отчество: " << patronymic << std::endl;

    stream << "Адрес: ";
    if (addressIndicator  == SQL_NULL_DATA) {
        stream << "не указан";
    } else {
        stream << address;
    }
    stream << std::endl;

    stream << "Комментарий: ";
    if (commentIndicator == SQL_NULL_DATA) {
        stream << "не указан";
    } else {
        stream << comment;
    }
    stream << std::endl;
}
