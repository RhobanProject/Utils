/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
/*
 * MotorPrimitiveXML.h
 *
 *  Created on: 12 mars 2011
 *      Author: hugo
 */

#include <fstream>
#include <vector>

#ifndef NO_RHOBANMATH
#include "linear_algebra.h"
#endif

#include "TinyXml/tinystr.h"
#include "TinyXml/tinyxml.h"

#ifndef MOTORPRIMITIVEXML_H_
#define MOTORPRIMITIVEXML_H_

#define xml_parse_error(str...)   { throw string(str); }
#define interpretor_error(str...) { throw string(str); }

#define XML_WRITE(result, truc ){ result << "<" << # truc << ">" << truc << "</" <<  # truc << ">"; }
#define XML_WRITE_INT(result, truc){ result << "<" << # truc << ">" << (int) truc << "</" << # truc << ">"; }
#define XML_WRITE_CHAR(result, truc){ result << "<" << # truc << ">" << (int) truc << "</" << # truc << ">"; }
#define XML_WRITE_BOOL(result, truc){ result << "<" << # truc << ">" << ( truc ? "true" : "false") << "</" << # truc << ">"; }
#define	XML_READ_INT(node, truc){ truc = XMLTools::get_int_element(node, # truc); }
#define	XML_READ_BOOL(node, truc){ truc = XMLTools::get_bool_element(node, # truc); }
#define	XML_READ_CHAR(node, truc){ truc = XMLTools::get_int_element(node, # truc); }
#define	XML_READ_DOUBLE(node, truc){ truc = XMLTools::get_double_element(node, # truc); }

using namespace std;
/*****************************************************************************/
/*
*/
namespace XMLTools
{
    string get_string_element(TiXmlNode * node, const char * id);

    vector<string> get_string_array(TiXmlNode * node, const char * id);

    bool has_child(TiXmlNode *node, const char *name);

    TiXmlNode *get_child(TiXmlNode *node, const char *name);

    vector<int> get_int_array(TiXmlNode * node, const char * id);

    double get_double_element(TiXmlNode * node, const char * id);

    float get_float_element(TiXmlNode * node, const char * id);

    int get_int_element(TiXmlNode * node, const char * id);

    bool get_bool_element(TiXmlNode * node, const char * id);

    float * get_float_array_with_3_element(TiXmlNode * node, const char * id);

#ifndef NO_RHOBANMATH
    Matrix extract_double_array(TiXmlNode* node, const char * array_id);
#endif

    string serialize_double_array(vector<double> data);

    /*!
     * @param stream
     * @return a non null node on the second sibling of the stream
     * and throw an exception if no such node
     */
    TiXmlDocument * stream_to_node(const string stream);

    TiXmlDocument * file_to_node(string filename);

    /*!
     * The xml stream is checked then wrote to a file
     */
    void stream_to_file(string filename, const string  stream);

    void node_to_file(string filename, TiXmlDocument * node);


}

class Serializable
{
    public:
        virtual string class_name() const = 0;

        //loads the object from the default file
        //the default filename is the name of the class + .xml
        virtual void load_file();

        //loads the object from a given file
        void load_file(string filename);

        //serializes and saves to a file using default filename
        void save_file();

        //serializes and saves to a file using given filename
        void save_file(string filename);

        //current default filename
        string filename;

        //deserializes from an xml stream
        virtual void from_xml(string xml_stream);

        //deserializes from an xml node
        virtual void from_xml(TiXmlNode *node) { throw string("from_xml not implemented");};

        //serializes to an xml strem excluding class name
        virtual string to_xml() const { throw string("to_xml not implemented");};


        //serializes to an xml strem including class name
        string to_xml_stream() const;

        /*! pretty print */
        void pretty_print() const;

        /*! not so pretty print */
        friend ostream & operator<< (ostream & stream, Serializable & obj);

    protected:
        Serializable();
        virtual ~Serializable();

};

#endif /* MOTORPRIMITIVEXML_H_ */
