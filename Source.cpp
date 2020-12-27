#include "Database.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
	Database* database = Database::getInstance();

	string words[200] = { nullptr };
	switch (words[0]) {
	case "CREATE":  try {
						if (words[1].compare("TABLE")) {
							validateTableCreation();
						} else if (words[1].compare("INDEX")) {
							validateIndexCreation();
						       } else { throw "not a valid create statement" }
					
					} catch () {}
				    break;
		case "DROP": try {
			             if (words[1].compare("TABLE")) {
							 validateDropTable();
						 }
						 else if (words[1].compare("INDEX")) {
							 validateDropIndex();
						 } else { throw "not a valid drop statement" }
		             } catch () {}
					 break;
		case "DISPLAY": try {
			                validateDisplay();
						} catch () {
						
						}
						break;
		case "INSERT": try {
							validateInsert();
						} catch () {

					    }
						break;
		case "UPDATE":  try {
							validateUpdate();
						} catch () {

					    }
						break;
		case "SELECT": try {
							validateSelect();
						} catch () {

					     }
						break;
		case "DELETE": try {
							validateDelete();
					   } catch () {

					    }
					   break;
		default: cout << "Not a valid user input";

	}
	return 0;
}