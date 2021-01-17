#include <iostream>
#include "Database.h"
#include "Parser.h"
#include "Table.h"
#include "Column.h"
#include <string>
#include <fstream>

using namespace std;

int ok = 1;

Database* Database::instance = nullptr;

Database* Database::getInstance() {
	if (instance == nullptr) {
		instance = new Database();
	}
	return instance;
}

string Database::validateDrop(string& str)
{
	//string ans = "Comanda Invalida";
	if (Parser::getFirstWord(str) == "TABLE")
	{
		str = Parser::removeFirstWord(str);
		//commandParams.push_back(Parser::getFirstWord(str));
		commandTableName = Parser::getFirstWord(str);
		str = Parser::removeFirstWord(str);
		if ((Parser::getFirstWord(str)).size() == 0)
		{
			return commandTableName;
			deleteTable();
		}

	}
	return "Invalid Command!";
}

void Database::deleteTable() {
	int i;
	for ( i = 0; i < nbOfTables; i++)
		if (strcmp(tables[i].getTableName(),commandTableName.c_str())==0)
			break;

	// If x found in array 
	if (i < nbOfTables)
	{
		// reduce size of array and move all 
		// elements on space ahead 
		nbOfTables--;
		for (int j = i; j < nbOfTables; j++)
			tables[j] = tables[j + 1];
		cout << "Tabela " + commandTableName + " a fost stearsa cu succes!";
	} else { cout << "Tabela " + commandTableName + " nu exista in baza de date!"; }
}

string Database::validateCreate(string& str)
{
	commandTableName = Parser::getFirstWord(str);
	str = Parser::removeFirstWord(str);
	str = Parser::removeSpaces(str);

	/// daca primele cuvinte sunt ifnotexists, le eliminam
	if (str.substr(0, 11) == "IFNOTEXISTS")
		str = str.substr(11, str.size() - 11);

	///trebuie sa inceapa acum cu 2 paranteze, sa avem((
	if (str.substr(0, 2) != "((")
		return "Invalid command!";
	str = str.substr(2, str.size());

	while (1)
	{
		int pos;
		pos = str.find(",");
		if (pos == std::string::npos)
			return "Invalid command!";

		commandParams.push_back(str.substr(0, pos)); ///punem denumirea in tabel
		str = str.substr(pos + 1, str.size()); ///scapam de denumire si de prima virgula

		pos = str.find(",");
		if (pos == std::string::npos)
			return "Invalid command!";

		if (str.substr(0, pos) == "text" || str.substr(0, pos) == "integer" || str.substr(0, pos) == "float")
		{
			commandParams.push_back(str.substr(0, pos));
		}
		else
			return "Invalid command!";

		str = str.substr(pos + 1, str.size()); ///scapam de al doilea parametru si de prima virgula

		///vedem daca avem numai cifre acum, ca suntem la dimensiune

		pos = str.find(",");
		if (pos == std::string::npos)
			return "Invalid command!";
		///verificam daca sunt numai cifre

		for (int i = 0; i < pos; i++)
		{
			if (str[i] < '0' || str[i] > '9')
			{
				cout << i << " " << (str[i] <= '0') << "\n";return "Invalid command!5";
			}
		}
		commandParams.push_back(str.substr(0, pos)); ///punem nr in tabel
		str = str.substr(pos + 1, str.size());///. scapam de numar

		pos = str.find(")"); ///cautam finalul perechii
		if (pos == std::string::npos)
			return "Invalid command!";

		if (commandParams[commandParams.size() - 2] == "text")
		{
			commandParams.push_back(str.substr(0, pos)); ///punem string in tabel
			str = str.substr(pos + 1, str.size()); /// scapam de string si paranteza
		}
		if (commandParams[commandParams.size() - 2] == "integer")
		{
			for (int i = 0; i < pos; i++)
			{
				if (str[i] < '0' || str[i] > '9')
					return "Invalid command!";
			}
			commandParams.push_back(str.substr(0, pos)); ///punem string in tabel
			str = str.substr(pos + 1, str.size()); /// scapam de string si paranteza
		}
		if (commandParams[commandParams.size() - 2] == "float")
		{
			for (int i = 0; i < pos; i++)
			{
				if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '.')
					return "Invalid command!";
			}
			commandParams.push_back(str.substr(0, pos)); ///punem string in tabel
			str = str.substr(pos + 1, str.size()); /// scapam de string si paranteza
		}

		if (str[0] == ')')
			break;
		if (str[0] != ',' || str[1] != '(')
			return "Invalid command!";
		str = str.substr(2, str.size());

	}
	string ans;
	for (int i = 0; i < commandParams.size(); i += 4)
	{
		ans += commandParams[i];
		ans += " ";
		ans += commandParams[i + 1];
		ans += " ";
		ans += commandParams[i + 2];
		ans += " ";
		ans += commandParams[i + 3];
		ans += "\n";
	}

	this->createTable();
	ans += "Introduceti noua comanda: ";
	ans += "\n";
	commandParams.clear();
	if (ok == 1) return ans;
	else return " ";
}

void Database::createTable() {
	vector<Column> columns;
	
	for (int i = 0;i < nbOfTables; i++) {
		
		char* name = tables[i].getTableName();

		if (strcmp(name, commandTableName.c_str())==0)
		{
			cout << "Operatia nu se poate efectua! Exista deja un tabel cu denumirea " + commandTableName;
			ok = 0;
			return;
		}
	}
	Table table;
	table.setTableName(commandTableName.c_str());
	int nbCol = commandParams.size() / 4;
	table.setNbOfColumns(nbCol);
	int k = 0;
	int ints = 0, floats = 0, strings = 0;
	for (int i = 0;i < nbCol;i++) {
		Column coloana;
		coloana.setNameAttr(commandParams[k].c_str());
		if (strcmp(commandParams[k + 1].c_str(),"integer") == 0) {
			ints++;
			coloana.setNbOfInt(ints);
		}else if (strcmp(commandParams[k + 1].c_str(),"float") == 0) {
			floats++;
			coloana.setNbOfInt(floats);
		}
		else if (strcmp(commandParams[k + 1].c_str(),"text") == 0) {
			strings++;
			coloana.setNbOfInt(strings);
		}
		k += 4;
		columns.push_back(coloana);
	}
	table.setColumns(columns);
	this->nbOfTables++;
	vector<Table> aux; aux.push_back(table);
	if (nbOfTables == 1) this->settables(aux);
	else this->addTable(table);
	cout << "Tabela " + commandTableName + " s-a creat cu succes! Aceasta are "+to_string(nbCol)+" coloane:"+"\n";
}

string Database::validateDisplay(string& str)
{
	if (Parser::getFirstWord(str) == "TABLE")
	{
		str = Parser::removeFirstWord(str);
		//commandParams.push_back(Parser::getFirstWord(str));
		commandTableName = Parser::getFirstWord(str);
		str = Parser::removeFirstWord(str);
		if ((Parser::getFirstWord(str)).size() == 0)
		{
			show();
			return commandTableName;
		}
		

	}
	return "Invalid Command!";
}
void Database::show() {
	
}

void Database::createFileForTable() {

	std::ofstream outfile("test.txt");

	outfile << "inceput faza 2!" << std::endl;

	outfile.close();
	
}




Database::Database()
{
	this->nbOfTables = 0;
	this->tables = nullptr;
	this->name = nullptr;

}

Database::Database(char* name, Table* tables, int nbOfTables)
{
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
	this->nbOfTables = nbOfTables;
	this->tables = new Table[nbOfTables];
	for (int i = 0; i < nbOfTables; i++)
		this->tables[i] = tables[i];

}

Database::Database(const Database& d)
{
	if (d.tables != nullptr && d.nbOfTables != 0)
	{
		this->nbOfTables = d.nbOfTables;
		this->tables = new Table[d.nbOfTables];
		for (int i = 0; i < d.nbOfTables; i++)
		{
			this->tables[i] = d.tables[i];
		}
	}
	else
	{
		this->tables = nullptr;
		this->nbOfTables = 0;
	}
	if (d.name != nullptr)
	{
		this->name = new char[strlen(d.name) + 1];
		strcpy_s(this->name, strlen(d.name) + 1, d.name);
	}
	else
	{
		this->name = nullptr;
	}
}

Database& Database::operator=(const Database& d)
{
	if (tables != nullptr)
	{
		delete[] tables;
	}
	if (name != nullptr)
	{
		delete[] name;
	}

	if (d.tables != nullptr && d.nbOfTables != 0)
	{
		this->nbOfTables = d.nbOfTables;
		this->tables = new Table[d.nbOfTables];
		for (int i = 0; i < d.nbOfTables; i++)
		{
			this->tables[i] = d.tables[i];
		}
	}
	else
	{
		this->tables = nullptr;
		this->nbOfTables = 0;
	}
	if (d.name != nullptr)
	{
		this->name = new char[strlen(d.name) + 1];
		strcpy_s(this->name, strlen(d.name) + 1, d.name);
	}
	else
	{
		this->name = nullptr;
	}
	return *this;
}

Database::~Database()
{
	if (tables != nullptr)
	{
		delete[] tables;
	}
	if (name != nullptr)
	{
		delete[] name;
	}
}

void Database::addTable(Table& table) {
	this->tables[nbOfTables] = table;
}

bool Database::operator!()
{
	return nbOfTables > 0;
}

Database Database::operator++()
{
	this->nbOfTables++;
	return *this;
}

Database Database::operator++(int i)
{
	Database copy = *this;
	this->nbOfTables++;
	return copy;
}

Database Database::operator+(int valoare)
{
	if (valoare > 0)
	{
		Database copy = *this;
		copy.nbOfTables += valoare;
		return copy;
	}
	else
	{
		throw 15;
	}
}

Table& Database::operator[](int index)
{
	if (index >= 0 && index < nbOfTables)
	{
		return tables[index];
	}

	throw exception("index invalid");
}

Database::operator int()
{
	return nbOfTables;
}

int Database::operator()()
{
	if (name != nullptr)
	{
		return strlen(name);
	}

}

int Database::getnbOfTables()
{
	return nbOfTables;
}

void Database::setnbOfTables(int nbOfTables)
{
	if (nbOfTables > 0)
	{
		this->nbOfTables = nbOfTables;
	}
}

Table* Database::gettables()
{
	if (tables != nullptr)
	{
		Table* copy = new Table[nbOfTables];
		for (int i = 0; i < nbOfTables; i++)
		{
			copy[i] = tables[i];

		}
		return copy;
	}
	else
	{
		return nullptr;
	}
}


void Database::settables(vector<Table>& tables)
{
	if (tables.size() != 0)
	{
		this->nbOfTables = tables.size();
		if (this->tables != nullptr)
		{
			delete[] this->tables;

		}
		this->tables = new Table[100];
		for (int i = 0; i < this->nbOfTables; i++)
		{
			this->tables[i] = tables[i];
		}
	}
}


void Database::setname(const char* name)
{
	if (this->name != nullptr)
		delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
}

char* Database::getname()
{
	return this->name;
}

Table Database::gettables(int index)
{
	if (index >= 0 && index < nbOfTables && tables != nullptr)
	{
		return tables[index];
	}
}

/*
ostream& operator<<(ostream& out, Database& d)
{
	out << " Name: ";
	if (d.getname() != nullptr)
	{
		out << d.getname();
	}
	out << endl;
	out << "Number Of tables: " << d.getnbOfTables() << endl;
	out << "tables: ";
	if (d.gettables() != nullptr)
	{
		for (int i = 0; i < d.getnbOfTables(); i++)
		{
			//out << (Table)d.gettables(i) << " ";
		}
	}
	return out;
}

istream& operator>>(istream& in, Database& d)
{
	Table el;
	int nb;
	string buffer;
	in >> buffer;
	cout << "Name: ";
	in >> buffer;
	if (d.getname() != nullptr)
	{
		delete[] d.getname();
	}
	//t.setname() = new char[buffer.length() + 1];
	//strcpy_s(t.getname(), buffer.length() + 1, buffer.c_str());
	d.setname(buffer.c_str());
	cout << "Number of tables = ";
	//in >> t.getnbOfTables();
	in >> nb; d.setnbOfTables(nb);
	/*	if (t.getname() != nullptr)
		{
			delete[] t.getname();
		}
		if (t.getnbOfTables() > 0)
		{
			t.getname() = new int[t.getnbOfTables()];
			for (int i = 0; i < t.getnbOfTables(); i++)
			{
				cout << "note[" << i << "] = ";
				in >> t.getname(i);
			}
		}
		else
		{
			t.getnbOfTables() = 0;
			t.getname() = nullptr;
		} 
	for (int i = 0; i < d.getnbOfTables(); i++)
	{
		in >> el;
		d.gettables(i) = el;

	}
	return in;
}
*/
int Database::compara(Database* d)
{
	if (this->nbOfTables < d->nbOfTables)
	{
		return -1;
	}
	else if (this->nbOfTables == d->nbOfTables)
	{
		return 0;
	}
	else return 1;
}

bool Database::less(Database& d)
{
	return this->nbOfTables < d.nbOfTables;
}

bool Database::operator< (Database& d)
{
	return this->less(d);
}


bool Database::operator==(Database& d)
{

	return this->compara(&d) == 0;
}
