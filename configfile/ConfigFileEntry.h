#ifndef _CONFIGFILEENTRY_H
#define _CONFIGFILEENTRY_H

#include <iostream>

using namespace std;

class ConfigFileEntry
{
    public:
        ConfigFileEntry(string type, string name, string defaultValue);

        void print();

        string type;
        string name;
        string defaultValue;
};

#endif // _CONFIGFILEENTRY_H
