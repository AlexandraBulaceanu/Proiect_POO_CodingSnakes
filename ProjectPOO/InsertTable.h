#pragma once
#define InsertTable_H
#include <string>
#include <vector>
using namespace std;

class InsertTable {
private:
    string commandTableName;
    vector<string> commandArguments;
public:
    string validateInsert(string& str);
};