#ifndef _GENERIC_FACTORY_H
#define _GENERIC_FACTORY_H

#include <map>
#include <iostream>
#include <string>

template<typename T>
class Creator
{
    public:
        virtual T *create()=0;
};

template<typename T, typename Q>
class Instanciator : public Creator<T>
{
    public:
        T *create()
        {
            return new Q;
        }
};

template<typename T>
class GenericFactory
{
    public:
        virtual ~GenericFactory()
        {
            typename std::map<std::string, Creator<T>* >::iterator it;

            for (it=types.begin(); it!=types.end(); it++) {
                delete it->second;
            }
        }

        template<typename Q>
        void registerType(std::string type)
        {
            erase(type);
            types[type] = new Instanciator<T, Q>;
        }

        void erase(std::string type)
        {
            if (hasType(type)) {
                delete types[type];
                types.erase(type);
            }
        }

        bool hasType(std::string type)
        {
            return types.find(type) != types.end();
        }

        T *create(std::string type)
        {
           if (hasType(type)) {
            return types[type]->create();
           }

           return NULL;
        }

    protected:
        std::map<std::string, Creator<T>* > types;
};

#endif
