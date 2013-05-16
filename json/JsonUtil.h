#ifndef _UTILS_JSON_UTIL_H
#define _UTILS_JSON_UTIL_H

#include <vector>
#include <iostream>
#include <json/json.h>

using namespace std;

class JsonUtil
{
    public:
        #define SUPPORT_TYPE(supportedType) \
            static void read(Json::Value &json, supportedType &value); \
            static void write(Json::Value &json, supportedType &value);

        // Supported types
        #define JSON_TYPE(type, X, Y)                   \
            SUPPORT_TYPE(type)                          \
            SUPPORT_TYPE(vector< type >)                \
            SUPPORT_TYPE(vector< vector< type > >)      \
            SUPPORT_TYPE(vector< vector< vector< type > > >)

        #include "json.def"
        #undef JSON_TYPE

        static void read(Json::Value &json, vector<bool>::reference value);
        static void write(Json::Value &json, vector<bool>::reference value);
};

#endif
