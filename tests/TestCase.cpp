/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>
#include <string.h>
#include <logging/log.h>
#include "TestCase.h"

using namespace std;

TestCase::TestCase() : assertions(0), assertionsPassed(0)
{
}

void TestCase::run()
{
    assertions = 0;
    assertionsPassed = 0;

    _run();

    cout << endl;
    cout << "-------------------------------" << endl;
#ifdef HAVE_COLORS
    if (assertionsPassed == assertions) {
        cout << T_COLOR_GREEN;
    } else {
        cout << T_COLOR_RED;
    }
#endif
    cout << "Ended, " << assertionsPassed << "/" << assertions << " assertions passed" << endl << endl;

#ifdef HAVE_COLORS
    cout << T_COLOR_RESET;
#endif
}

void TestCase::setPlace(string file, int line, string function)
{
    ostringstream oss;
    oss << file << ":" << line << " in " << function;
    place = oss.str();
}

void TestCase::error(string error)
{
    assertions++;
    cout << "!FAIL " << place << " " << current << ": " << error << endl;
}

void TestCase::pass()
{
    assertions++;
    assertionsPassed++;
    cout << "." << flush;
}

void TestCase::_assertTrue(bool expression)
{
    if (!expression) {
        error("Expression is false");
    } else {
        pass();
    }
}

void TestCase::_assertFalse(bool expression)
{
    if (expression) {
        error("Expression is true");
    } else {
        pass();
    }
}

void TestCase::_assertEquals(string str1, string str2, bool neg)
{
    if ((str1 != str2) xor neg) {
        if (neg) {
            error("String are equals (" + str1 + " == " + str2 + ")");
        } else {
            error("String differs (" + str1 + " != " + str2 + ")");
        }
    } else {
        pass();
    }
}

void TestCase::_assertEquals(char *char1, char *char2, int size)
{
    if (char1 == NULL || char2 == NULL) {
        error("Null pointer");
        return;
    }

    if (memcmp(char1, char2, size) != 0) {
        error("Char* differs");
    } else {
        pass();
    }
}

void TestCase::_assertEquals(int int1, int int2, bool neg)
{
    if ((int1 != int2) xor neg) {
        ostringstream oss;

        if (neg) {
            oss << "Int are equals (" << int1 << " == " << int2 << ")";
        } else {
            oss << "Int differs (" << int1 << " != " << int2 << ")";
        }

        error(oss.str());
    } else {
        pass();
    }
}

void TestCase::_assertEquals(char char1, char char2, bool neg)
{
    if ((char1 != char2) xor neg) {
        ostringstream oss;

        if (neg) {
            oss << "Char are equals (" << char1 << " == " << char2 << ")";
        } else {
            oss << "Char differs (" << char1 << " != " << char2 << ")";
        }

        error(oss.str());
    } else {
        pass();
    }
}

void TestCase::_assertEqualsDelta(float f1, float f2, float delta)
{
    if (abs(f1-f2) > delta) {
        error("Number differs");
    } else {
        pass();
    }
}
