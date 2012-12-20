/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include <iostream>
#include <string>

#include <vector>
#include <timing/sleep.h>
#include <logging/log.h>

#include <tests/TestCase.h>
#include <timing/sleep.h>
#include <graph/Curve.h>
#include <graph/Graph.h>

using namespace std;

#define TEST_LOG(...) LOG(1, 1, "test", __VA_ARGS__)

class CurveTest : public TestCase
{
    public:
        void testCurve()
        {
            vector<pair<double, double> > vals;
            int i;
            Graph graph;
            Curve *curve = graph.addCurve("test");

            // Adding 10 values
            for (i=0; i<10; i++) {
                curve->push(i*0.1);
                ms_sleep(100);
            }

            // Getting values for 1sec
            vals = curve->getValues(1.1);
            assertEquals(vals.size(), 10);

            // Getting values for 0.5sec
            vals = curve->getValues(0.51);
            assertEquals(vals.size(), 5);

            curve->garbageCollect(0.51);
            
            // Getting values for 1sec
            vals = curve->getValues(1.1);
            assertEquals(vals.size(), 5);

            for (vector<pair<double, double> >::iterator it = vals.begin(); it != vals.end(); it++) {
                pair<double, double> p = *it;
                assertEqualsDelta(p.first, p.second, 0.01);
            }
        }

    protected:
        void _run()
        {
            testCurve();
        }
};
