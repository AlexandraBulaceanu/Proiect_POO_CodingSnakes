#include "Database.h"

using namespace std;

Database* Database::instance = nullptr;

Database* Database::getInstance() {
    if (instance == nullptr) {
        instance = new Database();
    }
    return instance;
}
