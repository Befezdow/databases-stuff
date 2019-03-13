#include "ui-menu.h"
#include "db-service.h"

using namespace std;

int main() {

    DBService* service = new DBService;
    if (!service->initService()) {
        return 1;
    }

    UIMenu::setService(service);

    try {
        UIMenu::showMainMenu();
    } catch (const char* err) {
        std::cerr << err << std::endl;
        return 1;
    }

    return 0;
}
