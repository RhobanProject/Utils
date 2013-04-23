#ifndef _CONFIG_FILE_VALUE_H
#define _CONFIG_FILE_VALUE_H

#include <iostream>

using namespace std;

namespace YAML {
    class Emitter;
};

class ConfigFileWriteable
{
    public:
        virtual void write(YAML::Emitter *emitter)=0;
};

template <typename T>
class ConfigFileValue : public ConfigFileWriteable
{
    public:
        T value;

        ConfigFileValue(T value_)
        {
            value = value_;
        }

        void write(YAML::Emitter *emitter)
        {
            (*emitter) << value;
        }
};

#endif
