#include <iostream>
#include "Database.h"
#include "Parser.h"

using namespace std;

Database* Database::instance = nullptr;

Database* Database::getInstance() {
    if (instance == nullptr) {
        instance = new Database();
    }
    return instance;
}

string Database::validateDrop(string& str)
{
    //string ans = "Comanda Invalida";
    if (Parser::getFirstWord(str) == "TABLE")
    {
        str = Parser::removeFirstWord(str);
        //commandParams.push_back(Parser::getFirstWord(str));
        commandTableName = Parser::getFirstWord(str);
        str = Parser::removeFirstWord(str);
        if ((Parser::getFirstWord(str)).size() == 0)
            return commandTableName;

    }
    return "Invalid Command!";
}

string Database::validateCreate(string& str)
{
    commandTableName = Parser::getFirstWord(str);
    str = Parser::removeFirstWord(str);
    str = Parser::removeSpaces(str);

    /// daca primele cuvinte sunt ifnotexists, le eliminam
    if (str.substr(0, 11) == "IFNOTEXISTS")
        str = str.substr(11, str.size() - 11);

    ///trebuie sa inceapa acum cu 2 paranteze, sa avem((
    if (str.substr(0, 2) != "((")
        return "Invalid command!";
    str = str.substr(2, str.size());

    while (1)
    {
        int pos;
        pos = str.find(",");
        if (pos == std::string::npos)
            return "Invalid command!";

        commandParams.push_back(str.substr(0, pos)); ///punem denumirea in tabel
        str = str.substr(pos + 1, str.size()); ///scamap de denumire si de prima virgula

        pos = str.find(",");
        if (pos == std::string::npos)
            return "Invalid command!";

        if (str.substr(0, pos) == "text" || str.substr(0, pos) == "integer" || str.substr(0, pos) == "float")
        {
            commandParams.push_back(str.substr(0, pos));
        }
        else
            return "Invalid command!";

        str = str.substr(pos + 1, str.size()); ///scapam de al doilea parametru si de prima virgula

        ///vedem daca avem numai cifre acum, ca suntem la dimensiune

        pos = str.find(",");
        if (pos == std::string::npos)
            return "Invalid command!";
        ///verificam daca sunt numai cifre

        for (int i = 0; i < pos; i++)
        {
            if (str[i] < '0' || str[i] > '9')
            {
                cout << i << " " << (str[i] <= '0') << "\n";return "Invalid command!5";
            }
        }
        commandParams.push_back(str.substr(0, pos)); ///punem nr in tabel
        str = str.substr(pos + 1, str.size());///. scapam de numar

        pos = str.find(")"); ///cautam finalul perechii
        if (pos == std::string::npos)
            return "Invalid command!";

        if (commandParams[commandParams.size() - 2] == "text")
        {
            commandParams.push_back(str.substr(0, pos)); ///punem string in tabel
            str = str.substr(pos + 1, str.size()); /// scapam de string si paranteza
        }
        if (commandParams[commandParams.size() - 2] == "integer")
        {
            for (int i = 0; i < pos; i++)
            {
                if (str[i] < '0' || str[i] > '9')
                    return "Invalid command!";
            }
            commandParams.push_back(str.substr(0, pos)); ///punem string in tabel
            str = str.substr(pos + 1, str.size()); /// scapam de string si paranteza
        }
        if (commandParams[commandParams.size() - 2] == "float")
        {
            for (int i = 0; i < pos; i++)
            {
                if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '.')
                    return "Invalid command!";
            }
            commandParams.push_back(str.substr(0, pos)); ///punem string in tabel
            str = str.substr(pos + 1, str.size()); /// scapam de string si paranteza
        }

        if (str[0] == ')')
            break;
        if (str[0] != ',' || str[1] != '(')
            return "Invalid command!";
        str = str.substr(2, str.size());

    }
    string ans;
    for (int i = 0; i < commandParams.size(); i += 4)
    {
        ans += commandParams[i];
        ans += " ";
        ans += commandParams[i + 1];
        ans += " ";
        ans += commandParams[i + 2];
        ans += " ";
        ans += commandParams[i + 3];
        ans += "\n";
    }
    return ans;
}



string Database::validateDisplay(string& str)
{
    if (Parser::getFirstWord(str) == "TABLE")
    {
        str = Parser::removeFirstWord(str);
        //commandParams.push_back(Parser::getFirstWord(str));
        commandTableName = Parser::getFirstWord(str);
        str = Parser::removeFirstWord(str);
        if ((Parser::getFirstWord(str)).size() == 0)
            return commandTableName;

    }
    return "Invalid Command!";
}
