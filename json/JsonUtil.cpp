#include <iostream>
#include "JsonUtil.h"

using namespace std;

/**
 * Handle the reading using as and is methods
 */
#define JSON_TYPE(type, testMethod, asMethod)                    \
    void JsonUtil::read(Json::Value &json, type &value)          \
    {                                                            \
        if (!json.  testMethod  ()) {                            \
          throw std::runtime_error("Node should be of type " + string(#type)); \
    }                                                            \
                                                                 \
        value = json.  asMethod  ();                             \
    }                                                            \
                                                                 \
    void JsonUtil::write(Json::Value &json, type &value)         \
    {                                                            \
        json = Json::Value(value);                               \
    } 

#include "json.def"
#undef JSON_TYPE

/**
 * Handle the reading of arrays
 */
#define SUPPORT_ARRAY(type)                                        \
    void JsonUtil::read(Json::Value &json, vector< type > &value)  \
    {                                                              \
        if (!json.isArray()) {                                     \
            throw std::runtime_error("Array excepted");                        \
        }                                                          \
                                                                   \
        value.resize(json.size());                                 \
                                                                   \
        for (unsigned int i=0; i<json.size(); i++) {               \
            JsonUtil::read(json[i], value[i]);                     \
        }                                                          \
    }                                                              \
                                                                   \
    void JsonUtil::write(Json::Value &json, vector< type > &value) \
    {                                                              \
        json = Json::Value(Json::arrayValue);                      \
                                                                   \
        int pos = 0;                                               \
        vector< type >::iterator it;                               \
        for (it=value.begin(); it!=value.end(); it++) {            \
            JsonUtil::write(json[pos++], *it);                     \
        }                                                          \
    }

#define JSON_TYPE(type, X, Y)                                      \
    SUPPORT_ARRAY(type)                                            \
    SUPPORT_ARRAY(vector< type >)                                  \
    SUPPORT_ARRAY(vector< vector< type > >)                        

#include "json.def"
#undef JSON_TYPE
    
void JsonUtil::read(Json::Value &json, vector<bool>::reference value)          
{
    if (!json.isBool()) {
        throw std::runtime_error("Node should be of type bool");
    }                                                            
                                                             
    value = json.asBool();            
}                                                            
                                                             
void JsonUtil::write(Json::Value &json, vector<bool>::reference value)
{                                                            
    json = Json::Value(value);
} 
