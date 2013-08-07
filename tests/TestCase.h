/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef _TESTCASE_H
#define _TESTCASE_H

#include <iostream>
#include <vector>

using namespace std;

typedef void testFunction();

class TestCase
{
    public:
        TestCase();

        void run();
        static double deltaDouble;

    protected:
        string place;
        string current;
        int assertions;
        int assertionsPassed;
        vector<testFunction*> tests;

        void setPlace(string file, int line, string function);
        
        virtual void _run() = 0;

        void addTest(testFunction *function);

#define assertTrue(expression) current = string("assertTrue(") + string(#expression) + string(")"); \
        setPlace(__FILE__, __LINE__, __FUNCTION__); \
        _assertTrue(expression);

        void _assertTrue(bool expression);

#define assertFalse(expression) current = string("assertFalse(") + #expression + ")"; \
        setPlace(__FILE__, __LINE__, __FUNCTION__); \
        _assertFalse(expression);

        void _assertFalse(bool expression);

#define assertEquals(exp1, exp2) current = string("assertEquals(") + #exp1 + ", " + #exp2 + ")"; \
        setPlace(__FILE__, __LINE__, __FUNCTION__); \
        _assertEquals(exp1, exp2);

#define assertNotEquals(exp1, exp2) current = string("assertNotEquals(") + #exp1 + ", " + #exp2 + ")"; \
        setPlace(__FILE__, __LINE__, __FUNCTION__); \
        _assertEquals(exp1, exp2, true);

        void _assertEquals(string str1, string str2, bool neg = false);
        void _assertEquals(int int1, int int2, bool neg = false);
        void _assertEquals(char char1, char char2, bool neg = false);

#define assertEqualsSize(exp1, exp2, size) current = string("assertEqualsSize(") + #exp1 + ", " + #exp2 + ", " + #size ")"; \
        setPlace(__FILE__, __LINE__, __FUNCTION__); \
        _assertEquals(exp1, exp2, size);

        void _assertEquals(char *char1, char *char2, int size);

#define assertEqualsDelta(exp1, exp2, delta) current = string("assertEqualsDelta(") + #exp1 + ", " + #exp2 + ", " + #delta ")"; \
        setPlace(__FILE__, __LINE__, __FUNCTION__); \
        _assertEqualsDelta(exp1, exp2, delta);

        void _assertEqualsDelta(float f1, float f2, float delta);
        void _assertEqualsDelta(double f1, double f2, double delta);

        void error(string error);
        void pass();
};

#endif // _TESTCAST_H
