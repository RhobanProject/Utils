#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include <util.h>
#include <stdlib.h>
#include "ConfigFile.h"

using namespace std;

ConfigFile::ConfigFile() : doc(NULL)
{}

ConfigFile::ConfigFile(string filename)
{
    load(filename);
}

ConfigFile::ConfigFile(string filename, int argc, char *argv[])
{
    load(filename);
    useCommandArgs(argc, argv);
}

void ConfigFile::load(string filename)
{
    try {
        ifstream fin(filename.c_str());
        YAML::Parser parser(fin);
        doc = new YAML::Node();
        parser.GetNextDocument(*doc);
    } catch(YAML::ParserException e) {
        throw string("Failed to parse configuration file " + filename + ":\n\t" + string(e.what()));
    }
}

ConfigFile::~ConfigFile()
{
    map<string, map<string, ConfigFileWriteable*> >::iterator it;

    for (it = values.begin(); it != values.end(); it++) {
        map<string, ConfigFileWriteable*> subMap = (*it).second;
        map<string, ConfigFileWriteable*>::iterator sit;

        for (sit = subMap.begin(); sit != subMap.end(); sit++) {
            delete (*sit).second;
        }
    }

    map<string, vector<ConfigFileEntry*> >::iterator eit;

    for (eit = entries.begin(); eit != entries.end(); eit++) {
        vector<ConfigFileEntry*> vect = (*eit).second;
        vector<ConfigFileEntry*>::iterator vit;

        for (vit = vect.begin(); vit != vect.end(); vit++) {
            delete (*vit);
        }
    }

    if (doc != NULL) {
        delete doc;
    }
}

string ConfigFile::getFullName(const string node, const string name)
{
    ostringstream fullOpt;
    fullOpt << node << "." << name;

    return fullOpt.str();
}

void ConfigFile::write(string node, string name, ConfigFileWriteable *value)
{
    if (values.find(node) != values.end() && values[node].find(name) != values[node].end()) {
        delete values[node][name];
    }

    values[node][name] = value;
}

void ConfigFile::write(string node, string name, int value)
{
    write(node, name, new ConfigFileValue<int>(value));
}

void ConfigFile::write(string node, string name, double value)
{
    write(node, name, new ConfigFileValue<double>(value));
}

void ConfigFile::write(string node, string name, float value)
{
    write(node, name, new ConfigFileValue<float>(value));
}

void ConfigFile::write(string node, string name, const char* value)
{
    string temp(value);
    write(node, name, new ConfigFileValue<string>(temp));
}

void ConfigFile::write(string node, string name, string value)
{
    write(node, name, new ConfigFileValue<string>(value));
}

void ConfigFile::write(string node, string name, bool value)
{
    write(node, name, new ConfigFileValue<bool>(value));
}

const YAML::Node *ConfigFile::getYaml(string node)
{
    const YAML::Node *nod = doc;
    vector<string> parts;
    split(node, '.', parts);
    vector<string>::iterator it;

    for (it=parts.begin(); it!=parts.end(); it++) {
        if (nod != NULL && nod->size()) {
            nod = nod->FindValue(*it);

            if (!nod || nod->size() == 0) {
                nod = NULL;
            }
        } else {
            nod = NULL;
            break;
        }
    }

    return nod;
}

void ConfigFile::save(string filename)
{
    map<string, map<string, ConfigFileWriteable*> >::iterator it;
    YAML::Emitter emitter;

    for (it = values.begin(); it != values.end(); it++) {
        string section = (*it).first;
        emitter << YAML::BeginMap;
        emitter << YAML::Key << section << YAML::Value;

        emitter << YAML::BeginMap;
        map<string, ConfigFileWriteable*> subMap = (*it).second;
        map<string, ConfigFileWriteable*>::iterator sit;

        for (sit = subMap.begin(); sit != subMap.end(); sit++) {
            string key = (*sit).first;
            ConfigFileWriteable *writeable = (*sit).second;
            emitter << YAML::Key << key << YAML::Value;
            writeable->write(&emitter);
        }
        emitter << YAML::EndMap;
        emitter << YAML::EndMap;
        emitter << YAML::Newline;
    }

    ofstream outputFile;
    outputFile.open(filename.c_str());
    outputFile << emitter.c_str();
    outputFile.close();
}

void ConfigFile::useCommandArgs(int argc, char **argv)
{
    args.process(argc, argv);
}

bool ConfigFile::read(string node, string name, int defaultValue, int &output)
{
    bool result = true;
    string fullName = getFullName(node, name);
    const YAML::Node *yaml = getYaml(node);
    const YAML::Node *nodeY;

    if (args.hasOption(name)) {
        output = args.getOptionInt(name);
    } else if (args.hasOption(fullName)) {
        output = args.getOptionInt(fullName);
    } else if (yaml && (nodeY = yaml->FindValue(name))) {
        *nodeY >> output;
    } else {
        result = false;
        output = defaultValue;
    }

    ostringstream oss;
    oss << defaultValue;
    write(node, name, output);
    entries[node].push_back(new ConfigFileEntry("int", name, oss.str()));

    return result;
}

bool ConfigFile::read(string node, string name, double defaultValue, double &output)
{
    bool result = true;
    string fullName = getFullName(node, name);
    const YAML::Node *yaml = getYaml(node);;
    const YAML::Node *nodeY;

    if (args.hasOption(name)) {
        output = args.getOptionDouble(name);
    } else if (args.hasOption(fullName)) {
        output = args.getOptionDouble(fullName);
    } else if (yaml && (nodeY = yaml->FindValue(name))) {
        *nodeY >> output;
    } else {
        result = false;
        output = defaultValue;
    }

    ostringstream oss;
    oss << defaultValue;
    write(node, name, output);
    entries[node].push_back(new ConfigFileEntry("double", name, oss.str()));

    return result;
}

bool ConfigFile::read(string node, string name, double value, float &output)
{
    double tmp;
    bool result = read(node, name, value, tmp);
    output = tmp;

    return result;
}

bool ConfigFile::read(string node, string name, string defaultValue, string &output)
{
    bool result = true;

    try {
        output = readStringIfExists(node, name);
    } catch(...) {
        // cout << "Using default value '" << defaultValue << "' for parameter '" << node << "' '" << name << "'" << endl;
        output = defaultValue;
        result = false;
    }

    write(node, name, output);
    entries[node].push_back(new ConfigFileEntry("string", name, defaultValue));

    return result;
}

string ConfigFile::readStringIfExists(string node, string name)
{
    string fullName = getFullName(node, name);
    const YAML::Node *yaml = getYaml(node);
    const YAML::Node *nodeY;

    string output;

    if (args.hasOption(name)) {
        output = args.getOption(name);
    } else if (args.hasOption(fullName)) {
        output = args.getOption(fullName);
    } else if (yaml && (nodeY = yaml->FindValue(name))) {
        *nodeY >> output;
    } else {
        throw string("Could not find node with path '") + name + "' or '" + fullName + "' in yaml file'";
    }

    return output;
}

bool ConfigFile::read(string node, string name, bool defaultValue, bool &output)
{
    bool result = true;
    string fullName = getFullName(node, name);
    string noName = "no-" + name;
    string fullNoName = "no-" + fullName;
    const YAML::Node *yaml = getYaml(node);;
    const YAML::Node *nodeY;

    if (args.hasFlag(name)) {
        output = true;
    } else if (args.hasFlag(noName)) {
        output = false;
    } else if (args.hasFlag(fullName)) {
        output = true;
    } else if (args.hasFlag(fullNoName)) {
        output = false;
    } else if (yaml && (nodeY = yaml->FindValue(name))) {
        *nodeY >> output;
    } else {
        result = false;
        output = defaultValue;
    }

    write(node, name, output);
    entries[node].push_back(new ConfigFileEntry("bool", name, defaultValue ? "true" : "false"));

    return result;
}

void ConfigFile::addHelpLine(string help)
{
    helpText = helpText + help + "\n";
}

void ConfigFile::help()
{
    if (args.hasFlag("help") || args.hasFlag("?")) {
        usage();
        exit(0);
    }
}

void ConfigFile::usage()
{
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
    cout << helpText << endl;
}
