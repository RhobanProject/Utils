/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iterator>

#include "file_mngt.h"
#include "util.h"

int store_in_file(char * name, ui8 * src, int size) {

    FILE * f;

    if ((f=fopen(name, "w")) == NULL) {
        printf("Erreur d'ouverture en ecriture\n");
        return 0;
    }

    int i;
    for (i=0; i<size; i++)
        fputc(src[i], f);

    fclose(f);
    return 1;

}

int read_file(char * name, ui8 * dest, int size) {

    FILE * f;

    if ((f=fopen(name, "r")) == NULL) {
        printf("Erreur d'ouverture en lecture\n");
        return 0;
    }

    int i;
    for (i=0; i<size; i++)
        dest[i] = fgetc(f);

    fclose(f);
    return 1;

}

string file_to_string(string path)
{
    ifstream in_file(path.c_str());
    string contents(istreambuf_iterator<char>(in_file), 
            (istreambuf_iterator<char>()) );
    in_file.close();

    return contents;
}

bool file_exists(string path)
{
    ifstream ifile(path.c_str());
    return ifile.is_open();
}

void file_put_contents(string path, string contents)
{
    ofstream ofile(path.c_str());

    if (ofile) {
        ofile << contents;
        ofile.close();
    }
}

string file_get_contents(string path)
{
    std::ifstream ifs(path.c_str());
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
            (std::istreambuf_iterator<char>()    ) );
    return content;
}
