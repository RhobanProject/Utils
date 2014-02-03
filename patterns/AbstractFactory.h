#include <map>
#include <iostream>
#include <string>

using namespace std;

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
class AbstractFactory
{
    public:
        virtual ~AbstractFactory()
        {
            typename map<string, Creator<T>* >::iterator it;

            for (it=types.begin(); it!=types.end(); it++) {
                delete it->second;
            }
        }

        template<typename Q>
        void registerType(string type)
        {
            if (hasType(type)) {
                delete types[type];
                types.erase(type);
            }

            types[type] = new Instanciator<T, Q>;
        }

        bool hasType(string type)
        {
            return types.find(type) != types.end();
        }

        T *create(string type)
        {
           if (hasType(type)) {
            return types[type]->create();
           }

           return NULL;
        }

    protected:
        map<string, Creator<T>* > types;
};
