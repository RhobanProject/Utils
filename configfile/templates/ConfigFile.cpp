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

    %INIT%
}
        
void %NAME%::processCommandArgs(int argc, char **argv)
{
    options.processCommandArgs(argc, argv);
}
