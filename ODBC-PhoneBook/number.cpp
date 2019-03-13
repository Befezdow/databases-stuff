#include "number.h"

#include <sqlext.h>
#include <sqltypes.h>

Number::Number() {}

Number::Number(std::__cxx11::string phoneNumber, int numberOwner) {
    strncpy((char*)this->phoneNumber, phoneNumber.c_str(), 12);
    this->numberOwner = numberOwner;
}

void Number::bindForInput(SQLHSTMT hstmt) {

    bool flag = true;
    flag = flag && SQLBindCol(hstmt, 1, SQL_C_LONG, &id, sizeof(id), nullptr) == SQL_SUCCESS;
    flag = flag && SQLBindCol(hstmt, 2, SQL_C_CHAR, &phoneNumber, sizeof(phoneNumber), nullptr) == SQL_SUCCESS;
    flag = flag && SQLBindCol(hstmt, 3, SQL_C_LONG, &numberOwner, sizeof(numberOwner), nullptr) == SQL_SUCCESS;

    if (!flag) {
        throw "Number :: bindForinput : Binding failed";
    }
}

void Number::bindForOutput(SQLHSTMT hstmt, int& temp) {

    temp = this->getNumberOwner();

    bool flag = true;

    flag = flag && SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                                    12, 0, (SQLPOINTER)this->getPhoneNumber(), 12,
                                    NULL) == SQL_SUCCESS;

    flag = flag && SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
                                    0, 0, &temp, 0, NULL) == SQL_SUCCESS;

    if (!flag) {
        throw "Email :: bindForOutput : Binding error";
    }
}

SQLINTEGER Number::getId() const {
    return id;
}

const SQLVARCHAR *Number::getPhoneNumber() const {
    return phoneNumber;
}

SQLINTEGER Number::getNumberOwner() const {
    return numberOwner;
}

void Number::setPhoneNumber(std::__cxx11::string newPhoneNumber) {

    strncpy((char*)phoneNumber, newPhoneNumber.c_str(), 12);
}

void Number::print(std::ostream &stream, bool withId) {
    if (withId) {
        stream << id << "\t";
    }
    stream << phoneNumber << std::endl;
}
