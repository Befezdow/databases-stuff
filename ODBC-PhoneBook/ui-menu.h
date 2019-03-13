#ifndef UIMENU_H
#define UIMENU_H

#include "db-service.h"

class UIMenu {
    static DBService* service;

//    static void showFindMenu();
    static void showChangeMenu();
    static void showNumberChangeMenu(int ownerId);
    static void showEmailChangeMenu(int ownerId);

    static void printAllContacts();
    static void printMaskedContacts();
    static void addContact();
    static void deleteContact();

    static void updateContactFirstName(Contact& contact);
    static void updateContactLastName(Contact& contact);
    static void updateContactPatronymic(Contact& contact);
    static void updateContactAddress(Contact& contact);
    static void updateContactComment(Contact& contact);

    static void printNumbersByOwnerId(int ownerId);
    static void addNumberToOwner(int ownerId);
    static void updateNumberOfOwner(int ownerId);
    static void deleteNumberOfOwner(int ownerId);

    static void printEmailsByOwnerId(int ownerId);
    static void addEmailToOwner(int ownerId);
    static void updateEmailOfOwner(int ownerId);
    static void deleteEmailOfOwner(int ownerId);

public:
    static void setService(DBService* service);
    static void showMainMenu();
};

#endif // UIMENU_H
