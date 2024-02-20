TIC2003 Static Program Analyzer (SPA) Prototype
(Built upon MAC_M1_StartupSPASolution)

Overview
This prototype is a simplified yet fully operational mini-SPA designed for static analysis of programs written in SIMPLE, a simplified programming language. It allows users to enter a source program and queries in a subset of PQL (Program Query Language) to parse the source program, build design abstractions in the database, evaluate the queries, and display the results.

Build
This program is built upon MAC_M1_StartupSPASolution.
Programs Used: CLion 2023.3.3 + CMake 3.28.1 + Xcode 15.2

Components
The prototype is structured into several key components, each implemented in separate C++ source files for modularity:

1) Database: Manages database operations, including initialization, data insertion, and query execution.
2) QueryProcessor: Evaluates PQL queries against the data stored in the database.
3) SourceProcessor: Parses SIMPLE programs and populates the database with extracted design abstractions.

Initialization: The database is initialized to ensure a clean slate for analysis.
Processing Source Programs: The SourceProcessor parses SIMPLE programs and populate the database with program constructs.
Evaluating Queries: The QueryProcessor then processes the PQL queries to analyze the SIMPLE program based on the design abstractions stored in the database.
Viewing Results: Query results are displayed, showing the analysis outcome based on the input queries.

Compiling and Running of AutoTester
Utilize the integrated AutoTester to automate testing with queries written in PQL and source written in SIMPLE.
1) Compile AutoTester: Build 'autotester' in CLion.
2) Run -> Edit Configurations -> CMake Application -> autotester
3) Input the following in the 'Program arguments' section: Source.txt Queries.txt output.xml
4) Based on your path file, point the 'Working directory' to the 'tests' folder, where the Source.txt and Queries.txt are found.
5) Save and run the Autotester. After running it, an output.xml is produced.

Contributions
Lim Wei Ping (A0227000A)
Teo Jun Hao (A0227157A)