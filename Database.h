#define Database_H
#include <string>
#include <vector>
using namespace std;

class Database {


public:
	static Database* getInstance();
	string validateCreate(string& str);
	string validateDrop(string& str);
	string validateDisplay(string& str);
private:
	int commandType; /// 1 pt create, 2 pt drop, 3 pt display
	vector<string> commandParams; /// vector de string de parametrii
	string commandTableName;
	static Database* instance;
	//vector<Table> tables;

};
