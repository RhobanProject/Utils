#ifndef _COMMAND_ARGS_H
#define _COMMAND_ARGS_H

#include <string>
#include <set>
#include <map>
#include <vector>

using namespace std;

class CommandArgs
{
    public:
        CommandArgs();
        CommandArgs(int argc, char *argv[]);
        virtual void process(int argc, char *argv[]);

        // Testing if a flag or an option is present
        bool hasFlag(string flag);
        bool hasFlag(char flag);
        bool hasOption(string option);

		void setFlag(string flag);
		void setOption(string name, string value);
		void setOptionInt(string name, int value);
		void setOptionDouble(string name, double value);
		void setOptionFloat(string name, float value);

        // Getting a n option
        string getOption(string name, string fallback="");
        int getOptionInt(string name, int fallback=0);
        double getOptionDouble(string name, double fallback=0);
        float getOptionFloat(string name, float fallback=0);
        
        // Getting parts
        vector<string> getParts();

    protected:
        set<string> flags;
        map<string, string> options;
        vector<string> parts;
};

#endif 
