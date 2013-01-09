#ifndef _CONFIGFILE_H
#define _CONFIGFILE_H

#include <map>
#include <vector>
#include <sstream>
#include <yaml-cpp/yaml.h>
#include <anyoption.h>

#include "ConfigFileEntry.h"

using namespace std;

class ConfigFile
{
    public:
        ConfigFile(string filename);

        void useCommandArgs(int argc, char **argv);

        void read(string node, string name, int value, int &output);
        void read(string node, string name, double value, double &output);
        void read(string node, string name, string value, string &output);

        void help();

    protected:
        map<string, vector<ConfigFileEntry*> > entries;
        YAML::Node doc;

        int argc;
        char **argv;

        string getFullName(string node, string name);
        AnyOption processOptions(string node, string name, string fullName);
        const YAML::Node *getYaml(string node);
};

#endif // _CONFIGFILE_H
