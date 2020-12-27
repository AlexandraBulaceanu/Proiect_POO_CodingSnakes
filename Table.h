#define Table_H
#include "Column.h"

class Table {


public:

	~Table();
	Column* setColumns( Column*);
	Column* getColumns();
	Column getColumns(int);
	int getNbOfColumns();
	void setNbOfColumns(int);
	char* getTableName();
	void setTableName(const char*);
	bool isCreated();
	void setCreated(bool);


	friend istream& operator >> (istream&, Table&);
	friend ostream& operator << (ostream&, const Table&);
	bool operator!();
	Table operator+(int);
	Table operator++();
	Table operator++(int);
	int& operator[](int);
	Table& operator = (const Table&);
	explicit operator int();
	int operator()();
	Table(const Table&);
	int compara(Table*);
	bool operator==(Table&);
	bool operator< (Table&);
	bool less(Table&);

	Table();
	Table(char*, Column*, int);

private:
	//vector<Table> tables;
	char* tableName;
	Column* columns;
	int nbOfColumns;
	bool created;

};
