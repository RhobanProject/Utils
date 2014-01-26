#include <stdlib.h>
#include <iostream>
#include "CommandArgs.h"

CommandArgs::CommandArgs() {}

CommandArgs::CommandArgs(int argc, char *argv[])
{
    process(argc, argv);
}

void CommandArgs::process(int argc, char *argv[])
{
    if (argv != NULL) {
        for (int argnum=1; argnum<argc; argnum++) {
            string arg(argv[argnum]);

            if (arg.size() == 2 && arg[0] == '-') {
                string flag;
                flag = arg[1];
                flags.insert(flag);
            } else if (arg.size() > 3 && arg[0] == '-' && arg[1] == '-') {
                for (unsigned int k=2; k<arg.size(); k++) {
                    if (arg[k] == '=') {
                        string option = arg.substr(2, k-2);
                        string value = arg.substr(k+1);
                        options[option] = value;
                        continue;
                    }
                }

                flags.insert(arg.substr(2));
            } else {
                parts.push_back(arg);
            }
        }
    }
}

bool CommandArgs::hasFlag(string flag)
{
    return (flags.find(flag) != flags.end());
}

bool CommandArgs::hasFlag(char flagChar)
{
    string flag;
    flag = flagChar;

    return hasFlag(flag);
}

bool CommandArgs::hasOption(string option)
{
    return (options.find(option) != options.end());
}

string CommandArgs::getOption(string name, string fallback)
{
    return hasOption(name) ? options[name] : fallback;
}

int CommandArgs::getOptionInt(string name, int fallback)
{
    return hasOption(name) ? atoi(options[name].c_str()) : fallback;
}

double CommandArgs::getOptionDouble(string name, double fallback)
{
    return hasOption(name) ? atof(options[name].c_str()) : fallback;
}

float CommandArgs::getOptionFloat(string name, float fallback)
{
    return hasOption(name) ? atof(options[name].c_str()) : fallback;
}

vector<string> CommandArgs::getParts()
{
    return parts;
}
