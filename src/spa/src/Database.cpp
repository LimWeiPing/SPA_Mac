#include "Database.h"

sqlite3* Database::dbConnection;
vector<vector<string>> Database::dbResults;
char* Database::errorMessage;

// method to connect to the database and initialize tables in the database
void Database::initialize() {
	// open a database connection and store the pointer into dbConnection
	sqlite3_open("database.db", &dbConnection);

	// drop the existing procedure table (if any)
	string dropProcedureTableSQL = "DROP TABLE IF EXISTS procedures";
	sqlite3_exec(dbConnection, dropProcedureTableSQL.c_str(), NULL, 0, &errorMessage);

	// create a procedure table
	string createProcedureTableSQL = "CREATE TABLE procedures ( procedureName VARCHAR(255) PRIMARY KEY);";
	sqlite3_exec(dbConnection, createProcedureTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing constants table (if any)
    string dropConstantTableSQL = "DROP TABLE IF EXISTS constants";
    sqlite3_exec(dbConnection, dropConstantTableSQL.c_str(), NULL, 0, &errorMessage);

    // create a constants table
    string createConstantTableSQL = "CREATE TABLE constants ( constantValue VARCHAR(255) PRIMARY KEY);";
    sqlite3_exec(dbConnection, createConstantTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing variables table (if any)
    string dropVariableTableSQL = "DROP TABLE IF EXISTS variables";
    sqlite3_exec(dbConnection, dropVariableTableSQL.c_str(), NULL, 0, &errorMessage);

    // create a constants table
    string createVariableTableSQL = "CREATE TABLE variables ( variableName VARCHAR(255) PRIMARY KEY);";
    sqlite3_exec(dbConnection, createVariableTableSQL.c_str(), NULL, 0, &errorMessage);

    // drop the existing statements table (if any)
    string dropStatementTableSQL = "DROP TABLE IF EXISTS statements";
    sqlite3_exec(dbConnection, dropStatementTableSQL.c_str(), NULL, 0, &errorMessage);

    // create a statements table
    string createStatementTableSQL = "CREATE TABLE statements ( statementSequence int PRIMARY KEY, statementType VARCHAR(255));";
    sqlite3_exec(dbConnection, createStatementTableSQL.c_str(), NULL, 0, &errorMessage);

    // initialize the result vector
	dbResults = vector<vector<string>>();
}

// method to close the database connection
void Database::close() {
	sqlite3_close(dbConnection);
}

// method to insert a procedure into the database
void Database::insertProcedure(string procedureName) {
	string insertProcedureSQL = "INSERT INTO procedures ('procedureName') VALUES ('" + procedureName + "');";
	sqlite3_exec(dbConnection, insertProcedureSQL.c_str(), NULL, 0, &errorMessage);
}

// method to get all the procedures from the database
void Database::getProcedures(vector<string>& results){
	// clear the existing results
	dbResults.clear();

	// retrieve the procedures from the procedure table
	// The callback method is only used when there are results to be returned.
	string getProceduresSQL = "SELECT * FROM procedures;";
	sqlite3_exec(dbConnection, getProceduresSQL.c_str(), callback, 0, &errorMessage);

	// postprocess the results from the database so that the output is just a vector of procedure names
	for (vector<string> dbRow : dbResults) {
		string result;
		result = dbRow.at(0);
		results.push_back(result);
	}
}

// method to insert a constant into the database
void Database::insertConstant(string constantValue) {
    string insertConstantSQL = "INSERT INTO constants ('constantValue') VALUES ('" + constantValue + "');";
    sqlite3_exec(dbConnection, insertConstantSQL.c_str(), NULL, 0, &errorMessage);
}

// method to get all the constants from the database
void Database::getConstant(vector<string>& results) {
    // clear the existing results
    dbResults.clear();

    // retrieve the constants from the constants table
    // The callback method is only used when there are results to be returned.
    string getConstantSQL = "SELECT * FROM constants;";
    sqlite3_exec(dbConnection, getConstantSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to insert a variable into the database
void Database::insertVariable(string variableName) {
    string insertVariableSQL = "INSERT INTO variables ('variableName') VALUES ('" + variableName + "');";
    sqlite3_exec(dbConnection, insertVariableSQL.c_str(), NULL, 0, &errorMessage);
}

// method to get all the variables from the database
void Database::getVariable(vector<string>& results) {
    // clear the existing results
    dbResults.clear();

    // retrieve the variables from the variables table
    // The callback method is only used when there are results to be returned.
    string getVariableSQL = "SELECT * FROM variables;";
    sqlite3_exec(dbConnection, getVariableSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to insert a Statement into the database
void Database::insertStatement(int statementSequence, string statementType) {
    string insertStatementSQL = "INSERT INTO statements ('statementSequence', 'statementType') VALUES ('" + to_string(statementSequence) + "' , '" + statementType + "');";
    sqlite3_exec(dbConnection, insertStatementSQL.c_str(), NULL, 0, &errorMessage);
}

// method to get all the Statement from the database
void Database::getStatement(vector<string>& results) {
    // clear the existing results
    dbResults.clear();

    // retrieve the statement from the statement table
    // The callback method is only used when there are results to be returned.
    string getStatementSQL = "SELECT statementSequence FROM statements;";
    sqlite3_exec(dbConnection, getStatementSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to get all the assignStatement from the database
void Database::getAssignStatement(vector<string>& results) {
    // clear the existing results
    dbResults.clear();

    // retrieve the assignStatement from the statement table
    // The callback method is only used when there are results to be returned.
    string getAssignStatementSQL = "SELECT statementSequence FROM statements WHERE statementType == 'assign';";
    sqlite3_exec(dbConnection, getAssignStatementSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to get all the printStatement from the database
void Database::getPrintStatement(vector<string>& results) {
    // clear the existing results
    dbResults.clear();

    // retrieve the printStatement from the statement table
    // The callback method is only used when there are results to be returned.
    string getPrintStatementSQL = "SELECT statementSequence FROM statements WHERE statementType == 'print';";
    sqlite3_exec(dbConnection, getPrintStatementSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// method to get all the readStatement from the database
void Database::getReadStatement(vector<string>& results) {
    // clear the existing results
    dbResults.clear();

    // retrieve the readStatement from the statement table
    // The callback method is only used when there are results to be returned.
    string getReadStatementSQL = "SELECT statementSequence FROM statements WHERE statementType == 'read';";
    sqlite3_exec(dbConnection, getReadStatementSQL.c_str(), callback, 0, &errorMessage);

    // postprocess the results from the database so that the output is just a vector of procedure names
    for (vector<string> dbRow : dbResults) {
        string result;
        result = dbRow.at(0);
        results.push_back(result);
    }
}

// callback method to put one row of results from the database into the dbResults vector
// This method is called each time a row of results is returned from the database
int Database::callback(void* NotUsed, int argc, char** argv, char** azColName) {
	NotUsed = 0;
	vector<string> dbRow;

	// argc is the number of columns for this row of results
	// argv contains the values for the columns
	// Each value is pushed into a vector.
	for (int i = 0; i < argc; i++) {
		dbRow.push_back(argv[i]);
	}

	// The row is pushed to the vector for storing all rows of results 
	dbResults.push_back(dbRow);

	return 0;
}
