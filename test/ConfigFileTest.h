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

#include <configfile/ConfigFile.h>

using namespace std;
using namespace Rhoban;

class ConfigFileTest : public TestCase
{
    public:
        void testConfigFile(ConfigFile *config = NULL)
        {
            string svalue;
            bool free = false;
            bool bvalue;
            int ivalue;
            float fvalue;
            int uvalue;

            if (!config) {
                config = new ConfigFile("config.yml");
                free = true;
            }

            config->read("test", "bvalue", true, bvalue);
            config->read("test", "ivalue", 0, ivalue);
            config->read("test", "fvalue", 3.24, fvalue);
            config->read("test", "svalue", "d", svalue);
            config->read("test", "uvalue", 44, uvalue);

            assertEquals(bvalue, false);
            assertEqualsDelta(fvalue, (float)1.23, 0.0001);
            assertEquals(ivalue, 10);
            assertEquals(svalue, "Hello");
            assertEquals(uvalue, 44);

            if (free) {
                delete config;
            }
        }

        void testConfigFileWrite()
        {
            ConfigFile config;
            string hello("Hello");
            config.write("test", "bvalue", false);
            config.write("test", "ivalue", 10);
            config.write("test", "fvalue", 1.23);
            config.write("test", "svalue", hello);
            config.save("out.yml");

            ConfigFile reading("out.yml");
            testConfigFile(&reading);
        }

    protected:
        void _run()
        {
            testConfigFile();
            testConfigFileWrite();
        }
};
