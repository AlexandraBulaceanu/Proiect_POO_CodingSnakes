#include <iostream>
#include <string>
#include "Table.h"
#include "Column.h"
using namespace std;

Column::Column()
{
	this->intValues = nullptr;
	this->floatValues = nullptr;
	this->stringValues = nullptr;
	this->nbOfInt = 0;
	this->nbOfFloat = 0;
	this->nbOfString = 0;
	this->nameAttr = nullptr;

}

Column::Column(int* intValues, float* floatValues, string* stringValues, int nbOfInt, int nbOfFloat, int nbOfString, char* nameAttr)
{
	this->nbOfInt = nbOfInt;
	this->nbOfFloat = nbOfFloat;
	this->nbOfString = nbOfString;
	this->intValues = new int[nbOfInt];
	for (int i = 0; i < nbOfInt; i++)
		this->intValues[i] = intValues[i];
	this->floatValues = new float[nbOfFloat];
	for (int i = 0; i < nbOfFloat; i++)
		this->floatValues[i] = floatValues[i];
	this->stringValues = new string[nbOfString];
	for (int i = 0; i < nbOfString; i++)
		this->stringValues[i] = stringValues[i];
	this->nameAttr = new char[strlen(nameAttr) + 1];
	strcpy_s(this->nameAttr, strlen(nameAttr) + 1, nameAttr);

}

Column::Column(const Column& c)
{
	if (c.intValues != nullptr && c.nbOfInt != 0)
	{
		this->nbOfInt = c.nbOfInt;
		this->intValues = new int[c.nbOfInt];
		for (int i = 0; i < c.nbOfInt; i++)
		{
			this->intValues[i] = c.intValues[i];
		}
	}
	else
	{
		this->intValues = nullptr;
		this->nbOfInt = 0;
	}

	if (c.floatValues != nullptr && c.nbOfFloat != 0)
	{
		this->nbOfFloat = c.nbOfFloat;
		this->floatValues = new float[c.nbOfFloat];
		for (int i = 0; i < c.nbOfFloat; i++)
		{
			this->floatValues[i] = c.floatValues[i];
		}
	}
	else
	{
		this->floatValues = nullptr;
		this->nbOfFloat = 0;
	}

	if (c.stringValues != nullptr && c.nbOfString != 0)
	{
		this->nbOfString = c.nbOfString;
		this->stringValues = new string[c.nbOfString];
		for (int i = 0; i < c.nbOfString; i++)
		{
			this->stringValues[i] = c.stringValues[i];
		}
	}
	else
	{
		this->stringValues = nullptr;
		this->nbOfString = 0;
	}

	if (c.nameAttr != nullptr)
	{
		this->nameAttr = new char[strlen(c.nameAttr) + 1];
		strcpy_s(this->nameAttr, strlen(c.nameAttr) + 1, c.nameAttr);
	}
	else
	{
		this->nameAttr = nullptr;
	}
}

Column& Column::operator=(const Column& c)
{
	if (intValues != nullptr)
	{
		delete[] intValues;
	}
	if (floatValues != nullptr)
	{
		delete[] floatValues;
	}
	if (stringValues != nullptr)
	{
		delete[] stringValues;
	}

	if (nameAttr != nullptr)
	{
		delete[] nameAttr;
	}

	if (c.intValues != nullptr && c.nbOfInt != 0)
	{
		this->nbOfInt = c.nbOfInt;
		this->intValues = new int[c.nbOfInt];
		for (int i = 0; i < c.nbOfInt; i++)
		{
			this->intValues[i] = c.intValues[i];
		}
	}
	else
	{
		this->intValues = nullptr;
		this->nbOfInt = 0;
	}

	if (c.floatValues != nullptr && c.nbOfFloat != 0)
	{
		this->nbOfFloat = c.nbOfFloat;
		this->floatValues = new float[c.nbOfFloat];
		for (int i = 0; i < c.nbOfFloat; i++)
		{
			this->floatValues[i] = c.floatValues[i];
		}
	}
	else
	{
		this->floatValues = nullptr;
		this->nbOfFloat = 0;
	}

	if (c.stringValues != nullptr && c.nbOfString != 0)
	{
		this->nbOfString = c.nbOfString;
		this->stringValues = new string[c.nbOfString];
		for (int i = 0; i < c.nbOfString; i++)
		{
			this->stringValues[i] = c.stringValues[i];
		}
	}
	else
	{
		this->stringValues = nullptr;
		this->nbOfString = 0;
	}

	if (c.nameAttr != nullptr)
	{
		this->nameAttr = new char[strlen(c.nameAttr) + 1];
		strcpy_s(this->nameAttr, strlen(c.nameAttr) + 1, c.nameAttr);
	}
	else
	{
		this->nameAttr = nullptr;
	}
	return *this;
}

Column::~Column()
{
	if (intValues != nullptr)
	{
		delete[] intValues;
	}
	if (floatValues != nullptr)
	{
		delete[] floatValues;
	}
	if (stringValues != nullptr)
	{
		delete[] stringValues;
	}

	if (nameAttr != nullptr)
	{
		delete[] nameAttr;
	}
}

bool Column::operator!()
{
	return (nbOfInt > 0) && (nbOfFloat>0) && (nbOfString>0);
}

Column Column::operator++()
{
	this->nbOfInt++;
	this->nbOfFloat++;
	this->nbOfString++;
	return *this;
}

Column Column::operator++(int i)
{
	Column copy = *this;
	this->nbOfInt++;
	this->nbOfFloat++;
	this->nbOfString++;
	return copy;
}

Column Column::operator+(int valoare)
{
	if (valoare > 0)
	{
		Column copy = *this;
		copy.nbOfInt += valoare;
		copy.nbOfFloat += valoare;
		copy.nbOfString += valoare;
		return copy;
	}
	else
	{
		throw 15;
	}
}

int& Column::operator[](int index)
{
	if (index >= 0 && index < nbOfInt)
	{
		return intValues[index];
	}
}

float& Column::operator[](float index) 
{
	int index1 = (int)index;
	if (index1 >= 0 && index1 < nbOfFloat)
	{
		return floatValues[index1];
	}
}

string& Column::operator[](const string& index)
{
	int index2 = atoi(index.c_str());
	if (index2 >= 0 && index2 < nbOfString)
	{
		return stringValues[index2];
	}

	throw exception("index invalid");
}

explicit Column::operator int()
{
	return nbOfInt;

}

int Column::operator()()
{
	if (nameAttr != nullptr)
	{
		return strlen(nameAttr);
	}

}

int Column::getNbOfInt()
{
	return nbOfInt;
}

int Column::getNbOfFloat()
{
	return nbOfFloat;
}

int Column::getNbOfString()
{
	return nbOfString;
}

int* Column::getIntValues()
{
	if (intValues != nullptr)
	{
		int* copy = new int[nbOfInt];
		for (int i = 0; i < nbOfInt; i++)
		{
			copy[i] = intValues[i];

		}
		return copy;
	}
	else
	{
		return nullptr;
	}
}


void Column::setIntValues(int* intValues, int nbOfInt)
{
	if (intValues != nullptr && nbOfInt != 0)
	{
		this->nbOfInt = nbOfInt;
		if (this->intValues != nullptr)
		{
			delete[] this->intValues;

		}
		this->intValues = new int[nbOfInt];
		for (int i = 0; i < nbOfInt; i++)
		{
			this->intValues[i] = intValues[i];
		}
	}
}

float* Column::getFloatValues()
{
	if (floatValues != nullptr)
	{
		float* copy = new float[nbOfFloat];
		for (int i = 0; i < nbOfFloat; i++)
		{
			copy[i] = floatValues[i];

		}
		return copy;
	}
	else
	{
		return nullptr;
	}
}


void Column::setFloatValues(float* floatValues, int nbOfFloat)
{
	if (floatValues != nullptr && nbOfFloat != 0)
	{
		this->nbOfFloat = nbOfFloat;
		if (this->floatValues != nullptr)
		{
			delete[] this->floatValues;

		}
		this->floatValues = new float[nbOfFloat];
		for (int i = 0; i < nbOfFloat; i++)
		{
			this->floatValues[i] = floatValues[i];
		}
	}
}

string* Column::getStringValues()
{
	if (stringValues != nullptr)
	{
		string* copy = new string[nbOfString];
		for (int i = 0; i < nbOfString; i++)
		{
			copy[i] = stringValues[i];

		}
		return copy;
	}
	else
	{
		return nullptr;
	}
}


void Column::setStringValues(string* stringValues, int nbOfString)
{
	if (stringValues != nullptr && nbOfString != 0)
	{
		this->nbOfString = nbOfString;
		if (this->stringValues != nullptr)
		{
			delete[] this->stringValues;

		}
		this->stringValues = new string[nbOfString];
		for (int i = 0; i < nbOfString; i++)
		{
			this->stringValues[i] = stringValues[i];
		}
	}
}

void Column::setNbOfInt (int nbOfInt)
{
	if (nbOfInt > 0)
	{
		this->nbOfInt = nbOfInt;
	}
}

void Column::setNbOfFloat(int nbOfFloat)
{
	if (nbOfFloat > 0)
	{
		this->nbOfFloat = nbOfFloat;
	}
}

void Column::setNbOfString(int nbOfString)
{
	if (nbOfString > 0)
	{
		this->nbOfString = nbOfString;
	}
}

void Column::setNameAttr(const char* nameAttr)
{
	if (this->nameAttr != nullptr)
		delete[] this->nameAttr;
	this->nameAttr = new char[strlen(nameAttr) + 1];
	strcpy_s(this->nameAttr, strlen(nameAttr) + 1, nameAttr);
}

char* Column::getNameAttr()
{
	return this->nameAttr;
}

int Column::getIntValues(int index)
{
	if (index >= 0 && index < nbOfInt && intValues != nullptr)
	{
		return intValues[index];
	}
}

float Column::getFloatValues(int index)
{
	if (index >= 0 && index < nbOfFloat && floatValues != nullptr)
	{
		return floatValues[index];
	}
}

string Column::getStringValues(int index)
{
	if (index >= 0 && index < nbOfString && stringValues != nullptr)
	{
		return stringValues[index];
	}
}

ostream& operator<<(ostream& out, Column c)
{
	out << "Name Attr: ";
	if (c.getNameAttr() != nullptr)
	{
		out << c.getNameAttr();
	}
	out << endl;
	out << "Number Of Int: " << c.getNbOfInt() << endl;
	out << "Number Of Float: " << c.getNbOfFloat() << endl;
	out << "Number Of String: " << c.getNbOfString() << endl;
	
	out << "Int Values: ";
	if (c.getIntValues() != nullptr)
	{
		for (int i = 0; i < c.getNbOfInt(); i++)
		{
			out << c.getIntValues(i) << " ";
		}
	}

	out << "Float Values: ";
	if (c.getFloatValues() != nullptr)
	{
		for (int i = 0; i < c.getNbOfFloat(); i++)
		{
			out << c.getFloatValues(i) << " ";
		}
	}

	out << "String Values: ";
	if (c.getStringValues() != nullptr)
	{
		for (int i = 0; i < c.getNbOfString(); i++)
		{
			out << c.getStringValues(i) << " ";
		}
	}


	return out;
}

istream& operator>>(istream& in, Column& c)
{
	int el1;
	float el2;
	string el3;
	int nb;
	string buffer;
	in >> buffer;
	cout << "Name Attr: ";
	in >> buffer;
	if (c.getNameAttr() != nullptr)
	{
		delete[] c.getNameAttr();
	}

	c.setNameAttr(buffer.c_str());
	cout << "Number of Int = ";
	in >> nb; c.setNbOfInt(nb);
	cout << "Number of Float = ";
	in >> nb; c.setNbOfFloat(nb);
	cout << "Number of String = ";
	in >> nb; c.setNbOfString(nb);


	for (int i = 0; i < c.getNbOfInt(); i++)
	{
		in >> el1;
		c.getIntValues(i) = el1;

	}

	for (int i = 0; i < c.getNbOfFloat(); i++)
	{
		in >> el2;
		c.getFloatValues(i) = el2;

	}

	for (int i = 0; i < c.getNbOfString(); i++)
	{
		in >> el3;
		c.getStringValues(i) = el3;

	}

	return in;
}

int Column::compara(Column* c)
{
	if (this->nbOfInt < c->nbOfInt)
	{
		return -1;
	}
	else if (this->nbOfInt == c->nbOfInt)
	{
		return 0;
	}
	else return 1;

	if (this->nbOfFloat < c->nbOfFloat)
	{
		return -1;
	}
	else if (this->nbOfFloat == c->nbOfFloat)
	{
		return 0;
	}
	else return 1;

	if (this->nbOfString < c->nbOfString)
	{
		return -1;
	}
	else if (this->nbOfString == c->nbOfString)
	{
		return 0;
	}
	else return 1;
}

bool Column::less(Column& c)
{
	return (this->nbOfInt < c.nbOfInt) && (this->nbOfFloat < c.nbOfFloat) && (this->nbOfString < c.nbOfString);
}

bool Column::operator< (Column& c)
{
	return this->less(c);
}


bool Column::operator==(Column& c)
{

	return this->compara(&c) == 0;
}