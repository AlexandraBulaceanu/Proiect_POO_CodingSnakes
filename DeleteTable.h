#pragma once
#define DeleteTable_H
#include <string>
#include <vector>
using namespace std;

class DeleteTable {
private:
    string commandTableName;
    vector<string> commandArguments;
public:
    string validateDelete(string& str);
    void del();
    bool foundInDel(string);
};