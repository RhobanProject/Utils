#ifndef _CONFIGFILE_%NAME%_H
#define _CONFIGFILE_%NAME%_H

#include <string>
#include <yaml-cpp/yaml.h>
%INCLUDES%

using namespace std;

class %NAME%
{
    public:
        %NAME%(string filename);

        %PROTOTYPES%

    protected:
        YAML::Node doc;
};

#endif // _CONFIGFILE_%NAME%_H
