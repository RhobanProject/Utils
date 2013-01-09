#include "ConfigFile.h"

using namespace std;

ConfigFile::ConfigFile(string filename) : argv(NULL)
{
    ifstream fin(filename.c_str());
    YAML::Parser parser(fin);
    parser.GetNextDocument(doc);
}

string ConfigFile::getFullName(string node, string name)
{
    ostringstream fullOpt;
    fullOpt << node << "." << name;

    return fullOpt.str();
}

AnyOption ConfigFile::processOptions(string node, string name, string fullName)
{
    AnyOption options;
    options.setOption(name.c_str());
    options.setOption(fullName.c_str());
    if (argv != NULL) {
        options.processCommandArgs(argc, argv);
    }

    return options;
}

const YAML::Node *ConfigFile::getYaml(string node)
{
    if (doc.size()) {
        const YAML::Node *nod = doc.FindValue(node);

        if (nod->size() != 0) {
            return nod;
        }
    }

    return NULL;
}

void ConfigFile::useCommandArgs(int argc_, char **argv_)
{
    argc = argc_;
    argv = argv_;
}

void ConfigFile::read(string node, string name, int defaultValue, int &output)
{
    string fullName = getFullName(node, name);
    AnyOption options = processOptions(node, name, fullName);
    const YAML::Node *yaml = getYaml(node);;
    const YAML::Node *nodeY;

    if (char *value = options.getValue(name.c_str())) {
        output = atoi(value);
    } else if (char *value = options.getValue(fullName.c_str())) {
        output = atoi(value);
    } else if (yaml && (nodeY = yaml->FindValue(name))) {
        *nodeY >> output;
    } else {
        output = defaultValue;
    }

    ostringstream oss;
    oss << defaultValue;
    entries[node].push_back(new ConfigFileEntry("int", name, oss.str()));
}

void ConfigFile::read(string node, string name, double defaultValue, double &output)
{
    string fullName = getFullName(node, name);
    AnyOption options = processOptions(node, name, fullName);
    const YAML::Node *yaml = getYaml(node);;
    const YAML::Node *nodeY;

    if (char *value = options.getValue(name.c_str())) {
        output = atof(value);
    } else if (char *value = options.getValue(fullName.c_str())) {
        output = atof(value);
    } else if (yaml && (nodeY = yaml->FindValue(name))) {
        *nodeY >> output;
    } else {
        output = defaultValue;
    }

    ostringstream oss;
    oss << defaultValue;
    entries[node].push_back(new ConfigFileEntry("double", name, oss.str()));
}

void ConfigFile::read(string node, string name, string defaultValue, string &output)
{
    string fullName = getFullName(node, name);
    AnyOption options = processOptions(node, name, fullName);
    const YAML::Node *yaml = getYaml(node);;
    const YAML::Node *nodeY;

    if (char *value = options.getValue(name.c_str())) {
        output = string(value);
    } else if (char *value = options.getValue(fullName.c_str())) {
        output = string(value);
    } else if (yaml && (nodeY = yaml->FindValue(name))) {
        *nodeY >> output;
    } else {
        output = defaultValue;
    }

    entries[node].push_back(new ConfigFileEntry("string", name, defaultValue));
}

void ConfigFile::help()
{
    if (argv == NULL) {
        return;
    }

    AnyOption options;
    options.setFlag("help");
    options.setFlag("?");
    options.processCommandArgs(argc, argv);

    if (options.getFlag("help") || options.getFlag("?")) {
        map<string, vector<ConfigFileEntry*> >::iterator it;
        vector<ConfigFileEntry*>::iterator vit;
        vector<ConfigFileEntry*> *vector;

        cout << "Help for configuration:" << endl << endl;

        for (it=entries.begin(); it!=entries.end(); it++) {
            vector = &(*it).second;
            cout << (*it).first << ":" << endl;
            for (vit=vector->begin(); vit!=vector->end(); vit++) {
                (*vit)->print();
            }
            cout << endl;
        }
        exit(0);
    }
}
