#ifndef _CONFIGFILE_%NAME%_H
#define _CONFIGFILE_%NAME%_H

#include <string>
#include <yaml-cpp/yaml.h>
#include <anyoption.h>
%INCLUDES%

using namespace std;

class %NAME%
{
    public:
        %NAME%(string filename);
        void processCommandArgs(int argc, char **argv);
        void usage();

        %PROTOTYPES%

    protected:
        AnyOption options;
        YAML::Node doc;
};

#endif // _CONFIGFILE_%NAME%_H
