#include "ConfigFileEntry.h"

using namespace std;

ConfigFileEntry::ConfigFileEntry(string type_, string name_, string defaultValue_)
    : type(type_), name(name_), defaultValue(defaultValue_)
{
}

void ConfigFileEntry::print()
{
    cout << "    " << name << ": " << "type: " << type << ", default: " << defaultValue << endl;
}
