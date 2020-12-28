#include <string>
#include <vector>
#include "SelectTable.h"
#include "Parser.h"

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
    string ans;

    for (int i = 0; i < selectArguments.size(); i++)
        ans += selectArguments[i], ans += " ";

    for (int i = 0; i < whereArguments.size(); i++)
        ans += whereArguments[i], ans += " ";
    return ans;
}
