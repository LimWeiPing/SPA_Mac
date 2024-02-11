#include "SourceProcessor.h"

// method for processing the source program
// This method currently only inserts the procedure name into the database
// using some highly simplified logic.
// You should modify this method to complete the logic for handling all the required syntax.
void SourceProcessor::process(string program) {
	// initialize the database
	Database::initialize();

	// tokenize the program
	Tokenizer tk;
	vector<string> tokens;
	tk.tokenize(program, tokens);

	// This logic is highly simplified based on iteration 1 requirements and 
	// the assumption that the programs are valid.
	string procedureName = tokens.at(1);

	// insert the procedure into the database
	Database::insertProcedure(procedureName);

    int currentStatement = 0;

    for (int i = 2; i < tokens.size(); i++) {
        string currentToken;
        currentToken = tokens.at(i);
        char firstCharacter = currentToken.at(0);

        // iterate through the stmtLst and increase the StatementSequence
        if ((currentToken == "{") && (i >= 2) && (tokens.at(i - 2) == "procedure")) {
            currentStatement += 1;
            continue;
        }
        if (currentToken == ";") {
            currentStatement += 1;
            continue;
        }

        // Constant logic: 1st character is digit then it is a constant
        // insert the constant into the database
        if (isdigit(firstCharacter)) {
            Database::insertConstant(currentToken);
            continue;
        }

        if (currentToken == "=") {
            string statementType = "assign";
            Database::insertStatement(currentStatement, statementType);
            continue;
        }

        if (currentToken == "print") {
            string statementType = "print";
            Database::insertStatement(currentStatement, statementType);
            continue;
        }

        if (currentToken == "read") {
            string statementType = "read";
            Database::insertStatement(currentStatement, statementType);
            continue;
        }

        if (isalpha(firstCharacter) && (i > 1) && (tokens.at(i - 1) != "procedure")){
            Database::insertVariable(currentToken);
        }

    }

}