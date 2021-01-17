#include <string>
#include <vector>
#include "DeleteTable.h"
#include "Parser.h"
#include "Database.h"
#include "Table.h"
#include "Column.h"

Database* db3 = Database::getInstance();

string DeleteTable::validateDelete(string& str)
{
    commandTableName = Parser::getFirstWord(str);
    str = Parser::removeFirstWord(str);
    if (Parser::getFirstWord(str) != "WHERE")
        return "Invalid Command";
    str = Parser::removeFirstWord(str);

    int pos;
    pos = str.find("=");
    if (pos == std::string::npos)
        return "Invalid Command";
    string nume_col = str.substr(0, pos);
    nume_col = Parser::removeSpaces(nume_col);
    commandArguments.push_back(nume_col);

    str = str.substr(pos + 1, str.size() - pos);

    commandArguments.push_back(str);
    del();
    string ans;
    ans = commandArguments[0] + " " + commandArguments[1];
    return ans;
}

bool DeleteTable::foundInDel(string attr) {
    if (strcmp(attr.c_str(), commandArguments[0].c_str()) == 0) { return true; }
    return false;
}

void DeleteTable::del() {
    Table* tablesInDB = db3->gettables();
    int nbTables = db3->getnbOfTables();
    for (int i = 0;i < nbTables;i++) {
        if (strcmp(tablesInDB[i].getTableName(), commandTableName.c_str()) == 0) {
            Column* columns = tablesInDB[i].getColumns();
            int nbOfRows;
            if (columns[0].getType() == 1) nbOfRows = columns[0].getNbOfInt();
            else if (columns[0].getType() == 2) nbOfRows = columns[0].getNbOfString();
            else nbOfRows = columns[0].getNbOfFloat();
            for (int h = 0;h < nbOfRows;h++) {
                for (int j = 0;j < tablesInDB[i].getNbOfColumns();j++) {
                    if (foundInDel(columns[j].getNameAttr())) {
                        cout << "Row " << columns[j].getNameAttr() << " deleted" << "\n";
                        if (columns[j].getType() == 1)
                            if (to_string(columns[j].getIntValue(h)) == commandArguments[1]) columns[j].sterge(h,1);
                            else if (columns[j].getType() == 2)
                                if (columns[j].getStringValue(h) == commandArguments[1]) columns[j].sterge(h,2);
                                else if (to_string(columns[j].getFloatValue(h)) == commandArguments[1]) columns[j].sterge(h,3);
                    }

                }

            }
        }
        cout << "\n";
    }

}