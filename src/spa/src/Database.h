#pragma once

#include <string>
#include <vector>
#include "sqlite3.h"

using namespace std;

// The Database has to be a static class due to various constraints.
// It is advisable to just add the insert / get functions based on the given examples.
class Database {
public:
	// method to connect to the database and initialize tables in the database
	static void initialize();

	// method to close the database connection
	static void close();

	// method to insert a procedure into the database
	static void insertProcedure(string procedureName);

	// method to get all the procedures from the database
	static void getProcedures(vector<string>& results);

    // method to insert a constant into the database
    static void insertConstant(string constant);

    // method to get all the constants from the database
    static void getConstant(vector<string>& results);

    // method to insert a variable into the database
    static void insertVariable(string constant);

    // method to get all the variables from the database
    static void getVariable(vector<string>& results);

    // method to insert a statements into the database
    static void insertStatement(int statementSequence, string statementType);

    // method to get all the assignStatement from the database
    static void getStatement(vector<string>& results);

    // method to get all the assignStatement from the database
    static void getAssignStatement(vector<string>& results);

    // method to get all the printStatement from the database
    static void getPrintStatement(vector<string>& results);

    // method to get all the readStatement from the database
    static void getReadStatement(vector<string>& results);

private:
	// the connection pointer to the database
	static sqlite3* dbConnection; 
	// a vector containing the results from the database
	static vector<vector<string>> dbResults; 
	// the error message from the database
	static char* errorMessage;
	// callback method to put one row of results from the database into the dbResults vector
	// This method is called each time a row of results is returned from the database
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
};
