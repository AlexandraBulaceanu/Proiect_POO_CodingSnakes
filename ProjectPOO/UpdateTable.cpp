#include <string>
#include <vector>
#include "UpdateTable.h"
#include "Parser.h"

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

    string ans;
    for (int i = 0; i < 4; i++)
        ans += commandArguments[i], ans += " ";

    return ans;


}