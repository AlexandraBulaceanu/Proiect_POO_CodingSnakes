#define Database_H

class Database {


	public:
		static Database* getInstance();
	private:
		static Database* instance;
		//vector<Table> tables;

};
