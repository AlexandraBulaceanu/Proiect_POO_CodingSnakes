#pragma once
#define Database_H
#include <string>
#include <vector>
#include "Table.h"
#include <fstream>

using namespace std;

class Database {


public:
	static Database* getInstance();
	string validateCreate(string& str);
	string validateDrop(string& str);
	string validateDisplay(string& str);
	void createTable();

	~Database();
	//void adaugaTable(Table*);

	//friend istream& operator >> (istream&, Database&);
	//friend ostream& operator << (ostream&, Database&);
	Database& operator = (const Database&);
	Database(const Database&);
	bool operator!();
	Database operator++();
	Database operator++(int);
	Database operator+(int);
	Table& operator[](int);
	explicit operator int();
	int operator()();

	int getnbOfTables();
	void setnbOfTables(int);
	Table* gettables();
	void settables(vector<Table>&);
	void setname(const char*);
	char* getname();
	Table gettables(int);
	int compara(Database*);
	bool less(Database&);
	bool operator< (Database&);
	bool operator==(Database&);
	void createFileForTable();
	void addTable(Table&);
	void show(string);
	void deleteTable();

private:
	static Database* instance;
	//vector<Table> tables;
	char* name;
	Table* tables;
	int nbOfTables;

	Database();
	Database(char*, Table*, int);

	int commandType; /// 1 pt create, 2 pt drop, 3 pt display
	vector<string> commandParams; /// vector de string de parametrii
	string commandTableName;

};
