#pragma once
#define Table_H
#include "Column.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Table {

public:

	Table();
	Table(char*, Column*, int);
	~Table();
	void setColumns(Column*, int);
	Column* getColumns();
	Column getColumns(int);
	int getNbOfColumns();
	void setNbOfColumns(int);
	char* getTableName();
	void setTableName(const char*);
	bool isCreated();
	void setCreated(bool);


	//friend istream& operator >> (istream&, Table&);
	//friend ostream& operator << (ostream&, Table&);
	bool operator!();
	Table operator+(int);
	Table operator++();
	Table operator++(int);
	Column& operator[](int);
	Table& operator = (const Table&);
	explicit operator int();
	int operator()();
	Table(const Table&);
	int compara(Table*);
	bool operator==(Table&);
	bool operator< (Table&);
	bool less(Table&);


private:
	//vector<Table> tables;
	char* tableName;
	Column* columns;
	int nbOfColumns;
	bool created;

};
