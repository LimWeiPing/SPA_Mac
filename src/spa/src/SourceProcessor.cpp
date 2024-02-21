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

    int currentStatement = 1;

    for (int i = 0; i < tokens.size(); i++) {
        string currentToken;
        currentToken = tokens.at(i);
        char firstCharacter = currentToken.at(0);

        // iterate through the stmtLst and increase the StatementSequence
        if ((currentToken) == "{") {
            currentStatement += 1;
            continue;
        }
        if ((currentToken == ";")) {
            currentStatement += 1;
            continue;
        }

        if (currentToken == "procedure") {
            //procedure not consider a statement
            currentStatement -= 1;
            string procedureName = tokens.at(i+1);
            Database::insertProcedure(procedureName);
            i++;
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

        if (currentToken == "while") {
            string statementType = "while";
            Database::insertStatement(currentStatement, statementType);
            continue;
        }

        if (currentToken == "if") {
            string statementType = "if";
            Database::insertStatement(currentStatement, statementType);
            continue;
        }

        if (currentToken == "then") {
            continue;
        }

        if (currentToken == "else") {
            // else not consider a statement
            currentStatement -= 1;
            continue;
        }

        if (currentToken == "call") {
            string statementType = "call";
            Database::insertStatement(currentStatement, statementType);
            i++;
            continue;
        }

        if (isalpha(firstCharacter)){
            Database::insertVariable(currentToken);
        }

    }

}