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

#include <timing/sleep.h>
#include <logging/log.h>

#include <tests/TestCase.h>

#include <observer/Observer.h>
#include <observer/Subject.h>

using namespace std;
using namespace Rhoban;

#define TEST_LOG(...) LOG(1, 1, "test", __VA_ARGS__)

class MyObserver : public Observer
{
    public:
        void notify(string event)
        {
            lastNotified = event;
        }

        string lastNotified;
};

class ObserverTest : public TestCase
{
    public:
        void testObserver()
        {
            MyObserver observer;
            Subject subject;

            subject.registerObserver("test", &observer);
            subject.registerObserver("test2", &observer);

            subject.notifyObservers("test");
            assertEquals(observer.lastNotified, "test");

            subject.notifyObservers("test2");
            assertEquals(observer.lastNotified, "test2");
        }

    protected:
        void _run()
        {
            testObserver();
        }
};
