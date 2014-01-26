#ifndef _CONFIGFILE_H
#define _CONFIGFILE_H

#include <map>
#include <vector>
#include <sstream>

#include "CommandArgs.h"
#include "ConfigFileEntry.h"
#include "ConfigFileValue.h"

using namespace std;

namespace YAML {
    class Node;
}

class ConfigFile
{
    public:
        ConfigFile();
        ConfigFile(string filename);
        ConfigFile(string filename, int argc, char *argv[]);
        ~ConfigFile();

        void load(string filename);

        void useCommandArgs(int argc, char **argv);

        const YAML::Node *getNode(string node, string name);
        string readStringIfExists(string node, string name);

        bool read(string node, string name, int value, int &output);
        bool read(string node, string name, double value, double &output);
        bool read(string node, string name, double value, float &output);
        bool read(string node, string name, string value, string &output);
        bool read(string node, string name, bool value, bool &output);

        void write(string node, string name, ConfigFileWriteable *value);

        void write(string node, string name, int value);
        void write(string node, string name, double value);
        void write(string node, string name, float value);
        void write(string node, string name, string value);
        void write(string node, string name, bool value);
        void write(string node, string name, const char *value);

        void save(string filename);

        string helpText;
        void addHelpLine(string help);

        /**
         * Displays the help if the --help or --? is passed
         */
        void help();

        /**
         * Displays the usage
         */
        void usage();

    protected:
        CommandArgs args;
        map<string, vector<ConfigFileEntry*> > entries;
        map<string, map<string, ConfigFileWriteable*> > values; 
        YAML::Node *doc;

        string getFullName(string node, string name);
        const YAML::Node *getYaml(string node);
};

#endif // _CONFIGFILE_H
