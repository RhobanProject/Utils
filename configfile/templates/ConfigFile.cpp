/**
 * /!\
 * Ce fichier a été généré automatiquement
 * Toute modification pourra être perdue
 */
#include <iostream>
#include <fstream>
#include <string>
#include "%NAME%.h"

using namespace std;

%METHODS%
        
%NAME%::%NAME%(string filename)
{
    ifstream fin(filename.c_str());
    YAML::Parser parser(fin);
    parser.GetNextDocument(doc);

    options.setFlag("help");
    options.setFlag("?");

    %INIT%
}

void %NAME%::usage()
{
    cout << "Parameters:\n";
    %USAGE%

    exit(1);
}
        
void %NAME%::processCommandArgs(int argc, char **argv)
{
    options.processCommandArgs(argc, argv);

    if (options.getFlag("help") || options.getFlag("?")) {
        usage();
    }
}
