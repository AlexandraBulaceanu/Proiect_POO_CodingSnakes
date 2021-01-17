#include <string>
#include <vector>
#include "UpdateTable.h"
#include "Parser.h"
#include "Database.h"
#include "Table.h"
#include "Column.h"

Database* db2 = Database::getInstance();

string UpdateTable::validateUpdate(string& str)
{

    commandTableName = Parser::getFirstWord(str);
    str = Parser::removeFirstWord(str);

    if (Parser::getFirstWord(str) != "SET")
        return "Invalid Command!";
    str = Parser::removeFirstWord(str);

    string nume_col;
    int pos;
    pos = str.find("=");

    if (pos == std::string::npos)
        return "Invalid Command!";

    nume_col = str.substr(0, pos);
    nume_col = Parser::removeSpaces(nume_col);

    commandArguments.push_back(nume_col);
    str = str.substr(pos + 1, str.size());

    string value;
    value = Parser::getFirstWord(str);

    commandArguments.push_back(value);
    str = Parser::removeFirstWord(str);

    if (Parser::getFirstWord(str) != "WHERE")
        return "Invalid Input!";

    str = Parser::removeFirstWord(str);

    pos = str.find("=");

    if (pos == std::string::npos)
        return "Invalid Command!";

    nume_col = str.substr(0, pos);
    nume_col = Parser::removeSpaces(nume_col);

    commandArguments.push_back(nume_col);
    str = str.substr(pos + 1, str.size());

    //    string value;
    value = Parser::getFirstWord(str);

    commandArguments.push_back(value);

    update();

    string ans;
    for (int i = 0; i < 4; i++)
        ans += commandArguments[i], ans += " ";

    return ans;


}

bool UpdateTable::foundInUpdate(string attr) {
    for (int i = 0;i < commandArguments.size();i++) {
        if (strcmp(attr.c_str(), commandArguments[i].c_str()) == 0) { return true; }
    }
    return false;
}



void UpdateTable::update() {
    Table* tablesInDB = db2->gettables();
    int nbTables = db2->getnbOfTables();
    for (int i = 0;i < nbTables;i++) {
        if (strcmp(tablesInDB[i].getTableName(), commandTableName.c_str()) == 0) {
                Column* columns = tablesInDB[i].getColumns();
                int nbOfRows;
                if (columns[0].getType() == 1) nbOfRows = columns[0].getNbOfInt();
                else if (columns[0].getType() == 2) nbOfRows = columns[0].getNbOfString();
                else nbOfRows = columns[0].getNbOfFloat();
                for (int h = 0;h < nbOfRows;h++) {
                    for (int j = 0;j < tablesInDB[i].getNbOfColumns();j++) {
                        if (foundInUpdate(columns[j].getNameAttr())) {
                            cout << "Row " << columns[j].getNameAttr() << " updated" << "\n";
                            if (columns[j].getType() == 1)
                                columns[j].setIntValue(h, atoi(commandArguments[1].c_str()));
                                else if (columns[j].getType() == 2)
                                columns[j].setStringValue(h, commandArguments[1]);
                                else columns[j].setFloatValue(h, atof(commandArguments[1].c_str()));
                            }

                        }

                    }
                }
                cout << "\n";
            }

        }
    
