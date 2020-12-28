#define SelectTable_H
#include <string>
#include <vector>
using namespace std;

class SelectTable {
private:
    vector<string> selectArguments;
    vector<string> whereArguments;
    string commandTableName;
public:
    string validateSelect(string& str);
};