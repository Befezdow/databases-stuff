#include "ui-menu.h"
#include <iostream>

DBService* UIMenu::service = nullptr;

void UIMenu::showMainMenu() {

    if (!UIMenu::service) {
        std::cerr << "Service isn't installed" << std::endl;
    }

    bool exitFlag = false;

    while (!exitFlag) {

        system("clear");

        std::cout << "Главное меню:" << std::endl;
        std::cout << "1. Вывести все контакты" << std::endl;
        std::cout << "2. Поиск контакта" << std::endl;
        std::cout << "3. Добавить контакт" << std::endl;
        std::cout << "4. Изменить контакт" << std::endl;
        std::cout << "5. Удалить контакт" << std::endl;
        std::cout << "6. Выйти из программы" << std::endl;
        std::cout << ">> ";

        int number = 0;
        std::cin >> number;
        std::cin.ignore();
        std::cout << std::endl;

        switch (number) {
            case 1:
                UIMenu::printAllContacts();
                break;
            case 2:
                UIMenu::printMaskedContacts();
                break;
            case 3:
                UIMenu::addContact();
                break;
            case 4:
                UIMenu::showChangeMenu();
                break;
            case 5:
                UIMenu::deleteContact();
                break;
            case 6:
                exitFlag = true;
                break;
            default:
                continue;
        }
    }
}

//void UIMenu::showFindMenu() {

//    bool exitFlag = false;

//    while (!exitFlag) {

//        system("clear");

//        std::cout << "Меню поиска:" << std::endl;
//        std::cout << "1. Поиск по имени" << std::endl;
//        std::cout << "2. Поиск по фамилии" << std::endl;
//        std::cout << "3. Поиск по отчеству" << std::endl;
//        std::cout << "4. Поиск по адресу" << std::endl;
//        std::cout << "5. Поиск по комментарию" << std::endl;
//        std::cout << "6. Выйти в предыдущее меню" << std::endl;
//        std::cout << ">> ";

//        int number = 0;
//        std::cin >> number;
//        std::cin.ignore();
//        std::cout << std::endl;

//        switch (number) {
//            case 1:
//                //Функция поиска по имени
//                break;
//            case 2:
//                //Функция поиска по фамилии
//                break;
//            case 3:
//                //Функция поиска по отчеству
//                break;
//            case 4:
//                //Функция поиска по адресу
//                break;
//            case 5:
//                //Функция поиска по комментарию
//                break;
//            case 6:
//                exitFlag = true;
//                break;
//            default:
//                continue;
//        }
//    }
//}

void UIMenu::showChangeMenu() {

    try {

        std::vector<Contact> vector = UIMenu::service->getAllContacts();

        while (1) {

            system("clear");
            std::cout << "Контакты:" << std::endl;
            for (uint i = 0; i < vector.size(); ++i) {
                std::cout << i + 1 << "\t";
                vector.at(i).print(std::cout);
            }
            std::cout << std::endl;

            uint inp = 0;
            std::cout << "Введите номер контакта (0 - вернуться): ";
            std::cin >> inp;
            std::cin.ignore();
            std::cout << std::endl;
            if (inp == 0) {
                return;
            }

            inp--;

            if (inp >= 0 && inp < vector.size()) {
                bool exitFlag = false;
                while (!exitFlag) {

                    system("clear");
                    vector.at(inp).print(std::cout);
                    std::cout << std::endl;

                    std::cout << "Меню изменения:" << std::endl;
                    std::cout << "1. Изменение имени" << std::endl;
                    std::cout << "2. Изменение фамилии" << std::endl;
                    std::cout << "3. Изменение отчества" << std::endl;
                    std::cout << "4. Изменение адреса" << std::endl;
                    std::cout << "5. Изменение комментария" << std::endl;
                    std::cout << "6. Изменение списка телефонных номеров" << std::endl;
                    std::cout << "7. Изменение списка почтовых адресов" << std::endl;
                    std::cout << "8. Выйти в предыдущее меню" << std::endl;
                    std::cout << ">> ";

                    int inp1 = 0;
                    std::cin >> inp1;
                    std::cin.ignore();
                    std::cout << std::endl;

                    switch (inp1) {
                        case 1:
                            UIMenu::updateContactFirstName(vector[inp]);
                            break;
                        case 2:
                            UIMenu::updateContactLastName(vector[inp]);
                            break;
                        case 3:
                            UIMenu::updateContactPatronymic(vector[inp]);
                            break;
                        case 4:
                            UIMenu::updateContactAddress(vector[inp]);
                            break;
                        case 5:
                            UIMenu::updateContactComment(vector[inp]);
                            break;
                        case 6:
                            UIMenu::showNumberChangeMenu(vector.at(inp).getId());
                            break;
                        case 7:
                            UIMenu::showEmailChangeMenu(vector.at(inp).getId());
                            break;
                        case 8:
                            exitFlag = true;
                            break;
                        default:
                            continue;
                    }
                }
            } else {
                system("clear");
                std::cout << "Контакт не найден" << std::endl;
                std::cin.get();
            }
        }
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::showNumberChangeMenu(int ownerId) {

    bool exitFlag = false;
    while (!exitFlag) {
        system("clear");

        std::cout << "Меню изменения списка телефонных номеров:" << std::endl;
        std::cout << "1. Вывести весь список" << std::endl;
        std::cout << "2. Добавить номер" << std::endl;
        std::cout << "3. Изменить номер" << std::endl;
        std::cout << "4. Удалить номер" << std::endl;
        std::cout << "5. Вернуться" << std::endl;
        std::cout << ">> ";

        int inp = 0;
        std::cin >> inp;
        std::cin.ignore();
        std::cout << std::endl;

        switch (inp) {
            case 1:
                UIMenu::printNumbersByOwnerId(ownerId);
                break;
            case 2:
                UIMenu::addNumberToOwner(ownerId);
                break;
            case 3:
                UIMenu::updateNumberOfOwner(ownerId);
                break;
            case 4:
                UIMenu::deleteNumberOfOwner(ownerId);
                break;
            case 5:
                exitFlag = true;
                break;
            default:
                continue;
        }
    }
}

void UIMenu::showEmailChangeMenu(int ownerId) {

    bool exitFlag = false;
    while (!exitFlag) {
        system("clear");

        std::cout << "Меню изменения списка email адресов:" << std::endl;
        std::cout << "1. Вывести весь список" << std::endl;
        std::cout << "2. Добавить адрес" << std::endl;
        std::cout << "3. Изменить адрес" << std::endl;
        std::cout << "4. Удалить адрес" << std::endl;
        std::cout << "5. Вернуться" << std::endl;
        std::cout << ">> ";

        int inp = 0;
        std::cin >> inp;
        std::cin.ignore();
        std::cout << std::endl;

        switch (inp) {
            case 1:
                UIMenu::printEmailsByOwnerId(ownerId);
                break;
            case 2:
                UIMenu::addEmailToOwner(ownerId);
                break;
            case 3:
                UIMenu::updateEmailOfOwner(ownerId);
                break;
            case 4:
                UIMenu::deleteEmailOfOwner(ownerId);
                break;
            case 5:
                exitFlag = true;
                break;
            default:
                continue;
        }
    }
}

void UIMenu::printAllContacts() {

    try {
        std::vector<Contact> vector = UIMenu::service->getAllContacts();

        if (!vector.empty()) {
            while (1) {

                system("clear");
                std::cout << "Список контактов:" << std::endl;
                for (uint i = 0; i < vector.size(); ++i) {
                    std::cout << i + 1 << "\t";
                    vector.at(i).print(std::cout);
                }

                std::cout << "Подробно - введите номер (0 - вернуться): ";
                uint inp = 0;
                std::cin >> inp;
                std::cin.ignore();
                std::cout << std::endl;

                if (inp == 0) {
                    return;
                }

                inp--;

                if (inp >= 0 && inp < vector.size()) {
                    system("clear");
                    std::vector<Number> numbers = UIMenu::service->getNumbersByOwnerId(vector.at(inp).getId());
                    std::vector<Email> emails = UIMenu::service->getEmailsByOwnerId(vector.at(inp).getId());

                    vector.at(inp).printDetail(std::cout);

                    std::cout << "Телефонные номера:" << std::endl;
                    for (uint i = 0; i < numbers.size(); ++i) {
                        std::cout << "\t";
                        numbers.at(i).print(std::cout);
                    }

                    std::cout << "Email адреса:" << std::endl;
                    for (uint i = 0; i < emails.size(); ++i) {
                        std::cout << "\t";
                        emails.at(i).print(std::cout);
                    }
                } else {
                    system("clear");
                    std::cout << "Контакт не найден" << std::endl;
                }
                std::cin.get();
            }
        } else {
            system("clear");
            std::cout << "Список контактов пуст" << std::endl;
            std::cin.get();
        }
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::printMaskedContacts()
{
    system("clear");

    std::string mask;
    std::cout << "Маска: ";
    std::getline(std::cin, mask);
    mask.insert(0, 1, '%');
    mask.push_back('%');

    try {
        std::vector<Contact> vector = UIMenu::service->getContactsByMask(mask);

        if (!vector.empty()) {
            while (1) {
                system("clear");
                std::cout << "Найденные контакты:" << std::endl;
                for (uint i = 0; i < vector.size(); ++i) {
                    std::cout << i + 1 << "\t";
                    vector.at(i).print(std::cout);
                }

                std::cout << "Подробно - введите номер (0 - вернуться): ";
                uint inp = 0;
                std::cin >> inp;
                std::cin.ignore();
                std::cout << std::endl;

                if (inp == 0) {
                    return;
                }

                inp--;

                if (inp >= 0 && inp < vector.size()) {
                    system("clear");
                    std::vector<Number> numbers = UIMenu::service->getNumbersByOwnerId(vector.at(inp).getId());
                    std::vector<Email> emails = UIMenu::service->getEmailsByOwnerId(vector.at(inp).getId());

                    vector.at(inp).printDetail(std::cout);

                    std::cout << "Телефонные номера:" << std::endl;
                    for (uint i = 0; i < numbers.size(); ++i) {
                        std::cout << "\t";
                        numbers.at(i).print(std::cout);
                    }

                    std::cout << "Email адреса:" << std::endl;
                    for (uint i = 0; i < emails.size(); ++i) {
                        std::cout << "\t";
                        emails.at(i).print(std::cout);
                    }
                } else {
                    system("clear");
                    std::cout << "Контакт не найден" << std::endl;
                }
                std::cin.get();
            }
        } else {
            system("clear");
            std::cout << "Ничего не найдено" << std::endl;
            std::cin.get();
        }
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::addContact() {

    system("clear");

    std::string firstName;
    std::string lastName;
    std::string patronymic;
    std::string address;
    std::string comment;

    std::cout << "Введите данные" << std::endl;

    std::cout << "Имя: ";
    std::getline(std::cin, firstName);

    std::cout << "Фамилия: ";
    std::getline(std::cin, lastName);

    std::cout << "Отчество: ";
    std::getline(std::cin, patronymic);

    std::cout << "Адрес: ";
    std::getline(std::cin, address);

    std::cout << "Комментарий: ";
    std::getline(std::cin, comment);

    Contact contact(firstName, lastName, patronymic, address, comment);
    try {
        UIMenu::service->insertOneContact(contact);
        system("clear");
        std::cout << "Контакт добавлен" << std::endl;
        std::cin.get();
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::deleteContact() {

    try {

        std::vector<Contact> vector = UIMenu::service->getAllContacts();

        while(1) {

            system("clear");
            std::cout << "Контакты:" << std::endl;
            for (uint i = 0; i < vector.size(); ++i) {
                std::cout << i + 1 << "\t";
                vector.at(i).print(std::cout);
            }
            std::cout << std::endl;

            uint inp = 0;
            std::cout << "Введите номер контакта (0 - вернуться): ";
            std::cin >> inp;
            std::cin.ignore();
            std::cout << std::endl;
            if (inp == 0) {
                return;
            }

            inp--;

            if (inp >= 0 && inp < vector.size()) {
                std::cerr << vector.at(inp).getId();
                service->deleteContactById(vector.at(inp).getId());
                system("clear");
                std::cout << "Контакт удален" << std::endl;
                std::cin.get();
                break;
            } else {
                system("clear");
                std::cout << "Контакт не найден" << std::endl;
                std::cin.get();
            }
        }

    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::updateContactFirstName(Contact& contact) {

    std::string newFirstName;
    system("clear");
    std::cout << "Новое имя: ";
    std::getline(std::cin, newFirstName);
    contact.setFirstName(newFirstName);

    try {
        UIMenu::service->updateContactById(contact, contact.getId());
        system("clear");
        std::cout << "Данные обновлены" << std::endl;
        std::cin.get();
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::updateContactLastName(Contact &contact) {

    std::string newLastName;
    system("clear");
    std::cout << "Новая фамилия: ";
    std::getline(std::cin, newLastName);
    contact.setLastName(newLastName);

    try {
        UIMenu::service->updateContactById(contact, contact.getId());
        system("clear");
        std::cout << "Данные обновлены" << std::endl;
        std::cin.get();
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::updateContactPatronymic(Contact &contact) {

    std::string newPatronymic;
    system("clear");
    std::cout << "Новая фамилия: ";
    std::getline(std::cin, newPatronymic);
    contact.setPatronymic(newPatronymic);

    try {
        UIMenu::service->updateContactById(contact, contact.getId());
        system("clear");
        std::cout << "Данные обновлены" << std::endl;
        std::cin.get();
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::updateContactAddress(Contact &contact) {

    std::string newAddress;
    system("clear");
    std::cout << "Новый адрес: ";
    std::getline(std::cin, newAddress);
    contact.setAddress(newAddress);

    try {
        UIMenu::service->updateContactById(contact, contact.getId());
        system("clear");
        std::cout << "Данные обновлены" << std::endl;
        std::cin.get();
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::updateContactComment(Contact &contact) {

    std::string newComment;
    system("clear");
    std::cout << "Новый комментарий: ";
    std::getline(std::cin, newComment);
    contact.setComment(newComment);

    try {
        UIMenu::service->updateContactById(contact, contact.getId());
        system("clear");
        std::cout << "Данные обновлены" << std::endl;
        std::cin.get();
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::printNumbersByOwnerId(int ownerId) {

    try {
        std::vector<Number> vector = service->getNumbersByOwnerId(ownerId);

        system("clear");
        std::cout << "Телефонные номера:" << std::endl;
        for (uint i = 0; i < vector.size(); ++i) {
            vector.at(i).print(std::cout);
        }
        std::cin.get();
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::addNumberToOwner(int ownerId) {

    std::string newPhoneNumber;
    system("clear");
    std::cout << "Введите новый номер: ";
    std::getline(std::cin, newPhoneNumber);

    Number number(newPhoneNumber, ownerId);
    try {
        service->insertOneNumber(number);
        system("clear");
        std::cout << "Номер успешно добавлен";
        std::cin.get();
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::updateNumberOfOwner(int ownerId) {

    try {
        std::vector<Number> vector = service->getNumbersByOwnerId(ownerId);

        system("clear");
        std::cout << "Телефонные номера:" << std::endl;
        for (uint i = 0; i < vector.size(); ++i) {
            std::cout << i + 1 << "\t";
            vector.at(i).print(std::cout);
        }
        std::cout << std::endl;

        uint inp = 0;
        std::cout << "Введите порядковый номер (0 - вернуться): ";
        std::cin >> inp;
        std::cin.ignore();
        std::cout << std::endl;
        if (inp == 0) {
            return;
        }

        inp--;

        if (inp >= 0 && inp < vector.size()) {

            std::string newPhoneNumber;
            system("clear");
            std::cout << "Введите новый номер: ";
            std::getline(std::cin, newPhoneNumber);

            service->updateNumberById(newPhoneNumber, vector.at(inp).getId());
            system("clear");
            std::cout << "Номер успешно обновлен";
            std::cin.get();
        }
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::deleteNumberOfOwner(int ownerId) {

    try {
        std::vector<Number> vector = service->getNumbersByOwnerId(ownerId);

        system("clear");
        std::cout << "Телефонные номера:" << std::endl;
        for (uint i = 0; i < vector.size(); ++i) {
            std::cout << i + 1 << "\t";
            vector.at(i).print(std::cout);
        }
        std::cout << std::endl;

        uint inp = 0;
        std::cout << "Введите порядковый номер (0 - вернуться): ";
        std::cin >> inp;
        std::cin.ignore();
        std::cout << std::endl;
        if (inp == 0) {
            return;
        }

        inp--;

        if (inp >= 0 && inp < vector.size()) {

            service->deleteNumberById(vector.at(inp).getId());
            system("clear");
            std::cout << "Номер успешно удален";
            std::cin.get();
        }
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::printEmailsByOwnerId(int ownerId) {

    try {
        std::vector<Email> vector = service->getEmailsByOwnerId(ownerId);

        system("clear");
        std::cout << "Email адреса:" << std::endl;
        for (uint i = 0; i < vector.size(); ++i) {
            vector.at(i).print(std::cout);
        }
        std::cin.get();
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::addEmailToOwner(int ownerId) {

    std::string newEmailAddress;
    system("clear");
    std::cout << "Введите новый email адрес: ";
    std::getline(std::cin, newEmailAddress);

    Email email(newEmailAddress, ownerId);
    try {
        service->insertOneEmail(email);
        system("clear");
        std::cout << "Email адрес успешно добавлен";
        std::cin.get();
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::updateEmailOfOwner(int ownerId) {

    try {
        std::vector<Email> vector = service->getEmailsByOwnerId(ownerId);

        system("clear");
        std::cout << "Email адреса:" << std::endl;
        for (uint i = 0; i < vector.size(); ++i) {
            std::cout << i + 1 << "\t";
            vector.at(i).print(std::cout);
        }
        std::cout << std::endl;

        uint inp = 0;
        std::cout << "Введите порядковый номер (0 - вернуться): ";
        std::cin >> inp;
        std::cin.ignore();
        std::cout << std::endl;
        if (inp == 0) {
            return;
        }

        inp--;

        if (inp >= 0 && inp < vector.size()) {

            std::string newEmailAddress;
            system("clear");
            std::cout << "Введите новый email адрес: ";
            std::getline(std::cin, newEmailAddress);

            service->updateEmailById(newEmailAddress, vector.at(inp).getId());
            system("clear");
            std::cout << "Email адрес успешно обновлен";
            std::cin.get();
        }
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::deleteEmailOfOwner(int ownerId) {

    try {
        std::vector<Email> vector = service->getEmailsByOwnerId(ownerId);

        system("clear");
        std::cout << "Email адреса:" << std::endl;
        for (uint i = 0; i < vector.size(); ++i) {
            std::cout << i + 1 << "\t";
            vector.at(i).print(std::cout);
        }
        std::cout << std::endl;

        uint inp = 0;
        std::cout << "Введите порядковый номер (0 - вернуться): ";
        std::cin >> inp;
        std::cin.ignore();
        std::cout << std::endl;
        if (inp == 0) {
            return;
        }

        inp--;

        if (inp >= 0 && inp < vector.size()) {

            service->deleteEmailById(vector.at(inp).getId());
            system("clear");
            std::cout << "Email адрес успешно удален";
            std::cin.get();
        }
    } catch (const char* err) {
        throw err;
    }
}

void UIMenu::setService(DBService *service) {

    UIMenu::service = service;
}
