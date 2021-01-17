#include <string>
#include <vector>
#include "SelectTable.h"
#include "Parser.h"
#include "Database.h"
#include "Table.h"
#include "Column.h"

Database* db1 = Database::getInstance();

string SelectTable::validateSelect(string& str)
{
    if (Parser::getFirstWord(str) == "ALL")
    {

        selectArguments.push_back("ALL");
        str = Parser::removeFirstWord(str);
    }
    else
    {
        int pos;
        pos = str.find(")");
        if (pos == std::string::npos)
            return "Invalid Command!";

        string args = str.substr(0, pos);
        str = str.substr(pos + 1, str.size());

        args = Parser::removeSpaces(args);

        if (args[0] != '(')
            return "Invalid Command!";
        args = args.substr(1, args.size());

        while (1)
        {
            pos = args.find(",");
            if (pos == std::string::npos)
            {
                selectArguments.push_back(args);
                break;
            }
            selectArguments.push_back(args.substr(0, pos));
            args = args.substr(pos + 1, args.size());
        }
    }
    if (Parser::getFirstWord(str) != "FROM")
        return "Invalid Command!";
    str = Parser::removeFirstWord(str);

    commandTableName = Parser::getFirstWord(str);
    str = Parser::removeFirstWord(str);

    if (str.size() > 0)
    {
        if (Parser::getFirstWord(str) == "WHERE")
        {
            int pos;
            str = Parser::removeFirstWord(str);
            pos = str.find("=");
            if (pos == std::string::npos)
                return "Invalid Command!";

            string nume_col = str.substr(0, pos);
            nume_col = Parser::removeSpaces(nume_col);
            whereArguments.push_back(nume_col);

            str = str.substr(pos + 1, str.size());
            whereArguments.push_back(str);
        }
        else
            return "Invalid Command!";
    }

    Table* tablesInDB = db1->gettables();
    int nbTables = db1->getnbOfTables();
    bool exists = 0, ok = 1;
    for (int i = 0;i < nbTables;i++) {
        if (strcmp(tablesInDB[i].getTableName(), commandTableName.c_str()) == 0) {
            exists = 1;
            Column* columns = tablesInDB[i].getColumns();
            int nbCol = tablesInDB[i].getNbOfColumns();
          
            for (int j = 0;j < tablesInDB[i].getNbOfColumns();j++) {
                //TODO: validate column name really exists in the table
                
            }
        }
    }
    if (exists == 0) { return "Invalid Command! The table does not exist!"; }
    if (ok == 0) { return "Invalid Command! The types do not match!"; }

    select();

    string ans;

    for (int i = 0; i < selectArguments.size(); i++)
        ans += selectArguments[i], ans += " ";

    for (int i = 0; i < whereArguments.size(); i++)
        ans += whereArguments[i], ans += " ";
    return ans;
}

bool SelectTable::foundInSelect(string attr) {
    for (int i = 0;i < selectArguments.size();i++) {
        if (strcmp(attr.c_str(), selectArguments[i].c_str()) == 0) {return true;}
    }
    return false;
}

int SelectTable::getWhereIndex(int i) {
    Table* tablesInDB = db1->gettables();
    Column* columns = tablesInDB[i].getColumns();
    for (int j = 0;j < tablesInDB[i].getNbOfColumns();j++) {
        if (strcmp(columns[j].getNameAttr(), whereArguments[0].c_str()) == 0) return j;
    }
    return -1; //nu l-am gasit
}

void SelectTable::select() {
    Table* tablesInDB = db1->gettables();
    int nbTables = db1->getnbOfTables();
    for (int i = 0;i < nbTables;i++) {
        if (strcmp(tablesInDB[i].getTableName(), commandTableName.c_str()) == 0) {
            if (selectArguments.size() == 1 && strcmp(selectArguments[0].c_str(), "ALL") == 0) {
                if (whereArguments.size() == 0) {
                    db1->show(commandTableName);
                }
            }
                else {
                            cout << "Table " + commandTableName + " ";
                            Column* columns = tablesInDB[i].getColumns();
                            int nbOfRows;
                            if (columns[0].getType() == 1) nbOfRows = columns[0].getNbOfInt();
                            else if (columns[0].getType() == 2) nbOfRows = columns[0].getNbOfString();
                            else nbOfRows = columns[0].getNbOfFloat();
                            for (int h = 0;h < nbOfRows;h++) {
                                for (int j = 0;j < tablesInDB[i].getNbOfColumns();j++) {
                                    if (foundInSelect(columns[j].getNameAttr()) || strcmp(selectArguments[0].c_str(), "ALL") == 0) {
                                        if (whereArguments.size() > 0)
                                        {
                                            int index = getWhereIndex(i);
                                            if (index != -1) {
                                                bool whereOk = 0;
                                                if (columns[j].getType() == 1)
                                                    if (to_string(columns[index].getIntValue(h)) == whereArguments[1]) whereOk = 1;
                                                    else if (columns[index].getType() == 2)
                                                        if (columns[index].getStringValue(h) == whereArguments[1]) whereOk = 1;
                                                        else if (to_string(columns[index].getFloatValue(h)) == whereArguments[1]) whereOk = 1;
                                                if (whereOk) {
                                                    if (columns[j].getType() == 1)
                                                        cout << columns[j].getNameAttr() << "  " + to_string(columns[j].getIntValue(h)) + "  ";
                                                    else if (columns[j].getType() == 2)
                                                        cout << columns[j].getNameAttr() << "  " + columns[j].getStringValue(h) + "  ";
                                                    else cout << columns[j].getNameAttr() << "  " + to_string(columns[j].getFloatValue(h)) + "  ";
                                                }
                                            }
                                        }
                                        else {
                                            if (columns[j].getType() == 1)
                                                cout << columns[j].getNameAttr() << "  " + to_string(columns[j].getIntValue(h)) + "  ";
                                            else if (columns[j].getType() == 2)
                                                cout << columns[j].getNameAttr() << "  " + columns[j].getStringValue(h) + "  ";
                                            else cout << columns[j].getNameAttr() << "  " + to_string(columns[j].getFloatValue(h)) + "  ";
                                        }



                                    }

                                }
                                }
                                cout << "\n";
                            }

                        }
                    }
}
            
           
    
