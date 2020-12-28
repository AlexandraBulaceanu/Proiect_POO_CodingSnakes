#include <string>
#include <vector>
#include "InsertTable.h"
#include "Parser.h"

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
    string ans;
    for (int i = 0; i < commandArguments.size(); i++)
        ans += commandArguments[i], ans += "  ";
    return ans;
}