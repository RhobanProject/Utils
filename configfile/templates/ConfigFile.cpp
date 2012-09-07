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
}
