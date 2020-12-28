#include <iostream>
#include <string>
#include "Parser.h"

using namespace std;


    string Parser::removeFrontSpaces(string& str)
    {
        int pos = 0;
        while (str[pos] == ' ' && pos < str.size())
            pos++;
        return str.substr(pos, str.size() - pos);
    }

    string Parser::getFirstWord(string& str)
    {
        int pos = 0;
        while (str[pos] == ' ' && pos < str.size())
            pos++;
        int leng = 0;

        while (str[pos] != ' ' && pos < str.size())
        {
            pos++;
            leng++;
        }
        return str.substr(pos - leng, leng);

    }

    string Parser::removeFirstWord(string& str)
    {

        int pos = 0;
        while (str[pos] == ' ' && pos < str.size())
            pos++;
        int leng = 0;
        while (str[pos] != ' ' && pos < str.size())
        {
            pos++;
            leng++;
        }
        return str.substr(pos, str.size() - pos);
    }

    string Parser::removeSpaces(string& str)
    {
        string ans;
        for (int i = 0; i < str.size(); i++)
            if (str[i] != ' ')
                ans += str[i];
        return ans;
    }

