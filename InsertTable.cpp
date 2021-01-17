#include <string>
#include <vector>
#include "InsertTable.h"
#include "Database.h"
#include "Table.h"
#include "Column.h"
#include "Parser.h"

Database* db = Database::getInstance();


inline bool isInteger(const std::string& s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

    char* p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

string InsertTable::validateInsert(string& str)
{
    commandTableName = Parser::getFirstWord(str);
    str = Parser::removeFirstWord(str);
    if (Parser::getFirstWord(str) != "VALUES")
        return "Invalid Command!";
    str = Parser::removeFirstWord(str);
    //sterg primele spatii
    int place = 0;
    while (place < str.size() && str[place] == ' ')
        place++;
    str = str.substr(place, str.size());
    if (str[0] != '(')
        return "Invalid Command!";
    str = str.substr(1, str.size());

    while (1)
    {
        int pos;
        pos = str.find(",");
        if (pos == std::string::npos)
        {
            pos = str.find(")");
            if (pos == std::string::npos)
                return "Invalid Command!";
            commandArguments.push_back(str.substr(0, pos));
            break;
        }
        commandArguments.push_back(str.substr(0, pos));
        str = str.substr(pos + 1, str.size());
    }
    
    Table* tablesInDB = db->gettables();
    int nbTables = db->getnbOfTables();
    bool exists = 0, ok = 1;
    for (int i = 0;i < nbTables;i++) {
        if (strcmp(tablesInDB[i].getTableName(), commandTableName.c_str()) == 0) {
            exists = 1;
            Column* columns = tablesInDB[i].getColumns();
            int nbCol = tablesInDB[i].getNbOfColumns();
           // cout << nbCol << " ";
            cout << columns[1].getType()<<" ";
            if (commandArguments.size() != nbCol) return "Invalid Command!";
            for (int j = 0;j < tablesInDB[i].getNbOfColumns();j++) {
                int currentType;
                if (isInteger(commandArguments[j]) == 1) currentType = 1;
                else if (atof(commandArguments[j].c_str()) != 0.0) currentType = 3;
                else currentType = 2;
                //cout<<typeid(commandArguments[j].c_str()).name();
                if (columns[j].getType() != currentType) {
                    ok = 0; //cout << j << " "; cout << columns[j].getType() << " "; cout << currentType << "\n"; 
                    break;
                }
            }
        }
    }
    if (exists == 0) { return "Invalid Command! The table does not exist!"; }
    if (ok == 0) { return "Invalid Command! The types do not match!"; }

    insertIntoTable();
    string ans;
    for (int i = 0; i < commandArguments.size(); i++)
        ans += commandArguments[i], ans += "  ";
    return ans;
}

void InsertTable::insertIntoTable() {
    Table* tablesInDB = db->gettables();
    int nbTables = db->getnbOfTables();
    for (int i = 0;i < nbTables;i++) {
        if (strcmp(tablesInDB[i].getTableName(), commandTableName.c_str()) == 0) {
            Column* columns = tablesInDB[i].getColumns();
            int nbCol = tablesInDB[i].getNbOfColumns();
            for (int j = 0;j < tablesInDB[i].getNbOfColumns();j++) {
                if (columns[j].getType() == 1) {
                    int ints = columns[j].getNbOfInt();
                    cout << "ints: "<<ints<<" ";
                    columns[j].setNbOfInt(++ints);
                    cout<<columns[j].getNbOfInt()<<" ";
                    columns[j].addIntElem(atoi(commandArguments[j].c_str()));
                }
                else if (columns[j].getType() == 3) {
                    int floats = columns[j].getNbOfFloat();
                    columns[j].setNbOfFloat(++floats);
                    columns[j].addFloatElem(atof(commandArguments[j].c_str()));
                }
                else {
                    int strings = columns[j].getNbOfString();
                    columns[j].setNbOfString(++strings);
                    columns[j].addStringElem(commandArguments[j]);
                }
            }
        }
    }
}