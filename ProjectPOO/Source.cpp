#include "Database.h"
#include "Parser.h"
#include "InsertTable.h"
#include "SelectTable.h"
#include "DeleteTable.h"
#include "UpdateTable.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
    Database* database = Database::getInstance();
    InsertTable* insertTable = new InsertTable;
    DeleteTable* deleteTable = new DeleteTable;
    UpdateTable* updateTable = new UpdateTable;
    SelectTable* selectTable = new SelectTable;

    string input;
    getline(cin, input);


    if (Parser::getFirstWord(input) == "DROP")
    {
        input = Parser::removeFirstWord(input);
        cout << database->validateDrop(input);
    }
    else if (Parser::getFirstWord(input) == "CREATE")
    {
        input = Parser::removeFirstWord(input);
        if (Parser::getFirstWord(input) == "TABLE")
        {
            input = Parser::removeFirstWord(input);
            cout << database->validateCreate(input);
        }
    }
    else if (Parser::getFirstWord(input) == "DISPLAY")
    {
        input = Parser::removeFirstWord(input);
        cout << database->validateDisplay(input);
    }
    else if (Parser::getFirstWord(input) == "INSERT")
    {
        input = Parser::removeFirstWord(input);
        if (Parser::getFirstWord(input) == "INTO")
        {
            input = Parser::removeFirstWord(input);
            cout << insertTable->validateInsert(input);
        }
    }
    else if (Parser::getFirstWord(input) == "DELETE")
    {
        input = Parser::removeFirstWord(input);
        if (Parser::getFirstWord(input) == "FROM")
        {
            input = Parser::removeFirstWord(input);
            cout << deleteTable->validateDelete(input);
        }
    }
    else if (Parser::getFirstWord(input) == "UPDATE")
    {
        input = Parser::removeFirstWord(input);
        cout << updateTable->validateUpdate(input);
    }
    else if (Parser::getFirstWord(input) == "SELECT")
    {
        input = Parser::removeFirstWord(input);
        cout << selectTable->validateSelect(input);
    }
    //string words[200] = { nullptr };


    delete selectTable;
    delete insertTable;
    delete deleteTable;
    delete updateTable;

    return 0;
}
