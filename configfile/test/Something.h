#ifndef _SOMETHING_H
#define _SOMETHING_H

#include <string>

using namespace std;

class Something
{
    public:
        void print();

        /**
         * Parameter(my-int, 1, "An int parameter")
         */
        int intParam;

        /**
         * Parameter(my-string, "Hellow", "A simple string")
         */
        string stringParam;

        /**
         * Parameter(my-float, 1.23, "A float")
         */ 
        float floatParam;

        /**
         * Parameter(my-bool, false, "A boolean")
         */
        bool boolParam;
};

#endif // _SOMETHING_H
