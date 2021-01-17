#pragma once
#define Column_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Column {

public:
	Column();
	Column(int*, float*, string*, int, int, int, char*);
	~Column();
	Column& operator+=(int);
	Column(const Column& obj);
	bool operator!();
	Column operator++();
	Column operator++(int);
	Column operator+(int);
	int& operator[](int);
	float& operator[](float);
	string& operator[](const string&);
	explicit operator int();
	int operator()();
	int getIntValue(int);
	float getFloatValue(int);
	string getStringValue(int);

	void setIntValues(int*, int);
	int* getIntValues();
	void setFloatValues(float*, int);
	float* getFloatValues();
	void setStringValues(string*, int);
	string* getStringValues();
	void setNbOfInt(int);
	int getNbOfInt();
	void setNbOfFloat(int);
	int getNbOfFloat();
	void setNbOfString(int);
	int getNbOfString();
	void setNameAttr(const char*);
	char* getNameAttr();
	int compara(Column*);
	bool operator==(Column&);
	bool operator< (Column&);
	bool less(Column&);
	int getType();
	void setType(int);

	friend istream& operator >> (istream&, Column&);
	friend ostream& operator << (ostream&, const Column&);
	Column& operator = (const Column&);

	void addIntElem(int);
	void addFloatElem(float);
	void addStringElem(string);

	void setIntValue(int,int);
	void setStringValue(int, string);
	void setFloatValue(int, float);

	void sterge(int,int);

private:
	//vector<Column> Columns;
	int* intValues;
	float* floatValues;
	string* stringValues;
	int nbOfInt;
	int nbOfFloat;
	int nbOfString;
	char* nameAttr;
	int type;//1-integer,2-text,3-float
};
