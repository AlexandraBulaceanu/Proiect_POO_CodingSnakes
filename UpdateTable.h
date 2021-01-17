#pragma once
#define UpdateTable_H
#include <string>
#include <vector>
using namespace std;

class UpdateTable {
private:
    string commandTableName;
    vector<string> commandArguments;
public:
    string validateUpdate(string& str);
    void update();
    bool foundInUpdate(string);
};