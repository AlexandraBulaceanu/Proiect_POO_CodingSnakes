#include <iostream>
#include <string>
#include "Table.h"
#include "Column.h"
using namespace std;

	Table::Table() 
	{
		this->created = true;
		this->nbOfColumns = 0;
		this->columns = nullptr;
		this->tableName = nullptr;

	}

	Table::Table(char* tableName, Column* columns, int nbOfColumns)
	{
		this->tableName = new char[strlen(tableName) + 1];
		strcpy_s(this->tableName, strlen(tableName) + 1, tableName);
		this->nbOfColumns = nbOfColumns;
		this->columns = new Column[nbOfColumns];
		for (int i = 0; i < nbOfColumns; i++)
			this->columns[i] = columns[i];

	}

	Table::Table(const Table& t) 
	{
		if (t.columns != nullptr && t.nbOfColumns != 0)
		{
			this->nbOfColumns = t.nbOfColumns;
			this->columns = new int[t.nbOfColumns];
			for (int i = 0; i < t.nbOfColumns; i++)
			{
				this->columns[i] = t.columns[i];
			}
		}
		else
		{
			this->columns = nullptr;
			this->nbOfColumns = 0;
		}
		if (t.tableName != nullptr)
		{
			this->tableName = new char[strlen(t.tableName) + 1];
			strcpy_s(this->tableName, strlen(t.tableName) + 1, t.tableName);
		}
		else
		{
			this->tableName = nullptr;
		}
	}

	Table& Table::operator=(const Table& t)
	{
		if (columns != nullptr)
		{
			delete[] columns;
		}
		if (tableName != nullptr)
		{
			delete[] tableName;
		}
		
		if (t.columns != nullptr && t.nbOfColumns != 0)
		{
			this->nbOfColumns = t.nbOfColumns;
			this->columns = new int[t.nbOfColumns];
			for (int i = 0; i < t.nbOfColumns; i++)
			{
				this->columns[i] = t.columns[i];
			}
		}
		else
		{
			this->columns = nullptr;
			this->nbOfColumns = 0;
		}
		if (t.tableName != nullptr)
		{
			this->tableName = new char[strlen(t.tableName) + 1];
			strcpy_s(this->tableName, strlen(t.tableName) + 1, t.tableName);
		}
		else
		{
			this->tableName = nullptr;
		}
		return *this;
	}

	Table::~Table()
	{
		if (columns != nullptr)
		{
			delete[] columns;
		}
		if (tableName != nullptr)
		{
			delete[] tableName;
		}
	}
	
	bool Table::operator!()
	{
		return nbOfColumns > 0;
	}

	Table Table::operator++()
	{
		this->nbOfColumns++;
		return *this;
	}

	Table Table::operator++(int i)
	{
		Table copy = *this;
		this->nbOfColumns++;
		return copy;
	}

	Table Table::operator+(int valoare)
	{
		if (valoare > 0)
		{
			Table copy = *this;
			copy.nbOfColumns += valoare;
			return copy;
		}
		else
		{
			throw 15;
		}
	}

	int& Table::operator[](int index)
	{
		if (index >= 0 && index < nbOfColumns)
		{
			return columns[index];
		}
	
		throw exception("index invalid");
	}

	explicit Table::operator int()
	{
		return nbOfColumns;
	}

	int Table::operator()()
	{
		if (tableName != nullptr)
		{
			return strlen(tableName);
		}
		
	}

	int Table::getNbOfColumns()
	{
		return nbOfColumns;
	}

	void Table::setNbOfColumns(int nbOfColumns)
	{
		if (nbOfColumns > 0)
		{
			this->nbOfColumns = nbOfColumns;
		}
	}

	Column* Table::getColumns()
	{
		if (columns != nullptr)
		{
			Column* copy = new Column[nbOfColumns];
			for (int i = 0; i <nbOfColumns; i++)
			{
				copy[i] = columns[i];

			}
			return copy;
		}
		else
		{
			return nullptr;
		}
	}


	void Table::setColumns(Column* columns, int nbOfColumns)
	{
		if (columns != nullptr && nbOfColumns != 0)
		{
			this->nbOfColumns = nbOfColumns;
			if (this->columns != nullptr)
			{
				delete[] this->columns;

			}
			this->columns = new Column[nbOfColumns];
			for (int i = 0; i < nbOfColumns; i++)
			{
				this->columns[i] = columns[i];
			}
		}
	}

	bool Table::isCreated() 
	{
		return this->created;
	}

	void Table::setCreated(bool created)
	{
		this->created = created;
	}

	void Table::setTableName(const char* tableName)
	{
		if (this->tableName != nullptr)
			delete[] this->tableName;
		this->tableName = new char[strlen(tableName) + 1];
		strcpy_s(this->tableName, strlen(tableName) + 1, tableName);
	}

	char* Table::getTableName()
	{
		return this->tableName;
	}

	Column Table::getColumns(int index)
	{
		if (index >= 0 && index < nbOfColumns && columns != nullptr)
		{
			return columns[index];
		}
	}

	ostream& operator<<(ostream& out, Table t)
	{
		out << "Table Name: ";
		if (t.getTableName() != nullptr)
		{
			out << t.getTableName();
		}
		out << endl;
		out << "Number Of Columns: " << t.getNbOfColumns() << endl;
		out << "Columns: ";
		if (t.getColumns() != nullptr)
		{
			for (int i = 0; i < t.getNbOfColumns(); i++)
			{
				out << t.getColumns(i) << " ";
			}
		}
		return out;
	}

	istream& operator>>(istream& in, Table& t)
	{
		Column el;
		int nb;
		string buffer;
		in >> buffer;
		cout << "Tabel Name: ";
		in >> buffer;
		if (t.getTableName() != nullptr)
		{
			delete[] t.getTableName();
		}
		//t.setTableName() = new char[buffer.length() + 1];
		//strcpy_s(t.getTableName(), buffer.length() + 1, buffer.c_str());
		t.setTableName(buffer.c_str());
		cout << "Number of Columns = ";
		//in >> t.getNbOfColumns();
		in >> nb; t.setNbOfColumns(nb);
	/*	if (t.getTableName() != nullptr)
		{
			delete[] t.getTableName();
		}
		if (t.getNbOfColumns() > 0)
		{
			t.getTableName() = new int[t.getNbOfColumns()];
			for (int i = 0; i < t.getNbOfColumns(); i++)
			{
				cout << "note[" << i << "] = ";
				in >> t.getTableName(i);
			}
		}
		else
		{
			t.getNbOfColumns() = 0;
			t.getTableName() = nullptr;
		} */
		for (int i = 0; i < t.getNbOfColumns(); i++) 
		{
			in >> el;
			t.getColumns(i) = el;	

		}
		return in;
	}

	int Table::compara(Table* t)
	{
		if (this->nbOfColumns < t->nbOfColumns)
		{
			return -1;
		}
		else if (this->nbOfColumns == t->nbOfColumns)
		{
			return 0;
		}
		else return 1;
	}

	bool Table::less(Table& t) 
	{
		return this->nbOfColumns < t.nbOfColumns;
	}

	bool Table::operator< (Table& t)
	{
		return this->less(t);
	}


	bool Table::operator==(Table& t)
	{
		
		return this->compara(&t) == 0;
	}

	