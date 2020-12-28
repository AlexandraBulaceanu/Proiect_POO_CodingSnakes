#include <string>
#include <vector>
#include "DeleteTable.h"
#include "Parser.h"

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

    string ans;
    ans = commandArguments[0] + " " + commandArguments[1];
    return ans;
}

