#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include "ConfigFile.h"

using namespace std;

ConfigFile::ConfigFile() : argv(NULL), doc(NULL)
{
}

ConfigFile::ConfigFile(string filename) : argv(NULL)
{
	try
	{
		ifstream fin(filename.c_str());
		YAML::Parser parser(fin);
		doc = new YAML::Node();
		parser.GetNextDocument(*doc);
	}
	catch(YAML::ParserException exception)
	{
		throw string("Failed to parse configuration file " + filename + ":\n\t" + string(exception.what()));
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
	if (doc->size()) {
		const YAML::Node *nod = doc->FindValue(node);

		if (nod && nod->size() != 0) {
			return nod;
		}
	}

	return NULL;
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
	write(node, name, output);
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
	write(node, name, output);
	entries[node].push_back(new ConfigFileEntry("double", name, oss.str()));
}

void ConfigFile::read(string node, string name, double value, float &output)
{
	double tmp;
	read(node, name, value, tmp);
	output = tmp;
}

void ConfigFile::read(string node, string name, string defaultValue, string &output)
{
	try {
		output = readStringIfExists(node, name);
	} catch(...) {
		output = defaultValue;
	}

	write(node, name, output);
	entries[node].push_back(new ConfigFileEntry("string", name, defaultValue));
}

string ConfigFile::readStringIfExists(string node, string name)
{
	string fullName = getFullName(node, name);
	AnyOption options = processOptions(node, name, fullName);
	const YAML::Node *yaml = getYaml(node);
	const YAML::Node *nodeY;

	string output;

	if (char *value = options.getValue(name.c_str())) {
		output = string(value);
	} else if (char *value = options.getValue(fullName.c_str())) {
		output = string(value);
	} else if (yaml && (nodeY = yaml->FindValue(name))) {
		*nodeY >> output;
	} else {
		throw string("Could not find node with path '") + name + "' or '" + fullName + "' in yaml file'";
	}

	return output;
}

void ConfigFile::read(string node, string name, bool defaultValue, bool &output)
{
	string fullName = getFullName(node, name);
	string noName = "no-" + name;
	string fullNoName = "no-" + fullName;
	AnyOption options;
	const YAML::Node *yaml = getYaml(node);;
	const YAML::Node *nodeY;

	options.setFlag(name.c_str());
	options.setFlag(fullName.c_str());
	if (argv != NULL) {
		options.processCommandArgs(argc, argv);
	}

	if (options.getFlag(name.c_str())) {
		output = true;
	} else if (options.getFlag(noName.c_str())) {
		output = false;
	} else if (options.getFlag(fullName.c_str())) {
		output = true;
	} else if (options.getFlag(fullNoName.c_str())) {
		output = false;
	} else if (yaml && (nodeY = yaml->FindValue(name))) {
		*nodeY >> output;
	} else {
		output = defaultValue;
	}

	write(node, name, output);
	entries[node].push_back(new ConfigFileEntry("bool", name, defaultValue ? "true" : "false"));
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
