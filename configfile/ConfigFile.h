#ifndef _CONFIGFILE_H
#define _CONFIGFILE_H

#include <map>
#include <vector>
#include <sstream>
#include <anyoption.h>

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
        ~ConfigFile();

        void useCommandArgs(int argc, char **argv);

		const YAML::Node *getNode(string node, string name)  const;

        void read(string node, string name, int value, int &output);
		void read(string node, string name, double value, double &output);
		void read(string node, string name, double value, float &output);
		void read(string node, string name, string value, string &output);
		void read(string node, string name, bool value, bool &output);

        void write(string node, string name, ConfigFileWriteable *value);

        void write(string node, string name, int value);
        void write(string node, string name, double value);
        void write(string node, string name, float value);
        void write(string node, string name, string value);
        void write(string node, string name, bool value);
        void write(string node, string name, const char *value);

        void save(string filename);

		string readStringIfExists(string node, string name)  const;
		string readStringIfExists(string node) const;

        string helpText;
        void addHelpLine(string help);
        void help();

    protected:
        map<string, vector<ConfigFileEntry*> > entries;
        map<string, map<string, ConfigFileWriteable*> > values; 
        YAML::Node *doc;

        int argc;
        char **argv;

		string getFullName(const string node, const string name) const;
		void processOptions(AnyOption options, const string node, const string name, string fullName)  const;
		const YAML::Node *getYaml(string node) const;
};

#endif // _CONFIGFILE_H
