/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef _RUNTESTS_H
#define _RUNTESTS_H

#include <iostream>

using namespace std;

/**
 * Helper pour lancer des tests 
 */
template<class T>
void runTests(string message)
{
    T tests;
    cout << "===== " << message << endl;
    tests.run();
}

#endif // _RUNTESTS_H
