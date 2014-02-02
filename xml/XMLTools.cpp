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
 * MotorPrimitiveXML.cpp
 *
 *  Created on: 12 mars 2011
 *      Author: hugo
 */

#include "XMLTools.h"
#include <iostream>
#include <sstream>
#include <stdio.h>

using namespace std;
/****************************************************************************/
/* XML Parsing                                                              */
/****************************************************************************/

/* Fixing an issue with local configurations */
extern "C" double strtod_locale_independent(const char* s)
{
     std::istringstream text( s );
     text.imbue(std::locale::classic());
     double result;
     text >> result;
     return result;
}

bool XMLTools::has_child(TiXmlNode *node, const char *name)
{
    return node->FirstChild(name) != NULL;
}

TiXmlNode *XMLTools::get_child(TiXmlNode *node, const char *name)
{
    return node->FirstChild(name);
}

string XMLTools::get_string_element(TiXmlNode * node, const char * id) {
    if(!node) throw string("XMLTools getstringelement null node");
    TiXmlNode * the_father = node->FirstChild( id );
    if(the_father){
        TiXmlNode* the_child = the_father->FirstChild();
        if (the_child)
            return string(the_child->Value());
        else
            return "";
    }
    else
    {
        xml_parse_error(string("Xml parsing: could not find (string) node with label ") + id + " in node " + string(node->Value()));
    }
}

double XMLTools::get_double_element(TiXmlNode * node, const char * id) {
    if(!node) throw string("XMLTools getdoublelement null node");
    TiXmlNode * the_father = node->FirstChild( id );
    if(the_father){
        TiXmlNode* the_child = the_father->FirstChild();
        if (the_child)
        	return strtod_locale_independent(the_child->Value(),0);
        else xml_parse_error(string("Xml parsing: could not read double with label ") + id + " in node " + string(node->Value()));
    }
    else
    {
        xml_parse_error(string("Xml parsing: could not find (double) node with label ") + id + " in node " + string(node->Value()));
    }
}

float XMLTools::get_float_element(TiXmlNode * node, const char * id) {
    if(!node) throw string("XMLTools getdoublelement null node");
    TiXmlNode * the_father = node->FirstChild( id );
    if(the_father){
        TiXmlNode* the_child = the_father->FirstChild();
        if (the_child) return strtod_locale_independent(the_child->Value(),0);
        else xml_parse_error(string("Xml parsing: could not read double with label ") + id + " in node " + string(node->Value()));
    }
    else
    {
        xml_parse_error(string("Xml parsing: could not find (double) node with label ") + id + " in node " + string(node->Value()));
    }
}

float XMLTools::get_float_value(TiXmlNode * node)
{
   	return strtod_locale_independent(node->FirstChild()->Value(), 0);
}

int XMLTools::get_int_element(TiXmlNode * node, const char * id) {
    if(!node) throw string("XMLTools getintelement null node");
    TiXmlNode * the_father = node->FirstChild( id );
    if(the_father){
        TiXmlNode* the_child = the_father->FirstChild();
        if (the_child) return atoi(the_child->Value());
        else xml_parse_error(string("Xml parsing: could not read (int) value for label ") +id + " in node " + string(node->Value()));
    }
    else
    {
        xml_parse_error(string("Xml parsing: could not find (int) node with label  ") + id + " in node " + string(node->Value()));
    }
}

bool XMLTools::get_bool_element(TiXmlNode * node, const char * id) {
    if(!node) throw string("XMLTools getintelement null node");
    TiXmlNode * the_father = node->FirstChild( id );
    if(the_father)
    {
        TiXmlNode* the_child = the_father->FirstChild();
        if (the_child)
        {
            return !strcmp( the_child->Value() , "1") || !strcmp( the_child->Value() , "true");
        }
        else xml_parse_error(string("Xml parsing: could not read (int) value for label ") +id + " in node " + string(node->Value()));
    }
    else
    {
        xml_parse_error(string("Xml parsing: could not find boolean node with label  ") + id + " in node " + string(node->Value()));
    }
}

float * XMLTools::get_float_array_with_3_element(TiXmlNode * node, const char * array_id) {
    if(!node) throw string("XMLTools getfloatarray null node");
    TiXmlNode * the_values = node->FirstChild( array_id );
    if(the_values){
        float * array = (float *)malloc(3 * sizeof(float));
        int i = 0;
        for ( TiXmlNode* child = the_values->FirstChild("float"); child != 0; child = child->NextSibling())
        {
            if(!child)
            {
                xml_parse_error( string("Xml parsing: Error while reading element float array with label ") +array_id + " in node " + string(node->Value()));
            }
            else if(!child->FirstChild())
            {
                xml_parse_error( string("Xml parsing: Error while reading element flaot array with label ") +array_id + " in node " + string(node->Value()));
            }
            else
            {
                array[i] = atof(child->FirstChild()->Value());
                i++;
            }
        }
        return array;
    }
    else
    {
        xml_parse_error(string("Xml parsing: could not find (int) node with label  ") + array_id + " in node " + string(node->Value()));
    }
}

string XMLTools::serialize_double_array(vector<double> data)
{
    ostringstream result;
    for(unsigned int i = 0; i< data.size(); i++ )
        result << "<val>" << data[i] << "</val>";
    return result.str();
}

#ifndef NO_RHOBANMATH
Matrix XMLTools::extract_double_array(TiXmlNode* node, const char * array_id) {
    if(!node) throw string("XMLTools extractdoublearray null node");
    TiXmlNode* the_values = node->FirstChild( array_id );
    if(the_values){
        vector<scalar> tmp;
        for ( TiXmlNode* child = the_values->FirstChild(); child != 0; child = child->NextSibling())
        {
            if(!child)
            {
                xml_parse_error( string("Xml parsing: Error while reading element double array with label ") +array_id + " in node " + string(node->Value()));
            }
            else if(!child->FirstChild())
            {
                xml_parse_error( string("Xml parsing: Error while reading element double array with label ") +array_id + " in node " + string(node->Value()));
            }
            else tmp.push_back(atof(child->FirstChild()->Value()));
        }
        return Matrix(tmp);
    }
    else
    {
        xml_parse_error(string("Xml parsing: Could not find (double array) node with label  ") +array_id + " in node " + string(node->Value()));
    }
}
#endif

vector<string> XMLTools::get_string_array(TiXmlNode* node, const char * array_id)
{
    if(!node) throw string("XMLTools getstring array null node");
    TiXmlNode* the_values = node->FirstChild( array_id );
    if(the_values){
        vector<string> result;
        for ( TiXmlNode* child = the_values->FirstChild(); child != 0; child = child->NextSibling())
        {
            if(!child)
            {
                xml_parse_error( string("Xml parsing: Error while reading element string array with label ") +array_id + " in node " + string(node->Value()));
            }
            else if(!child->FirstChild())
            {
                xml_parse_error( string("Xml parsing: Error while reading element string array with label ") +array_id + " in node " + string(node->Value()));
            }
            else
                result.push_back(child->FirstChild()->Value());
        }
        return result;
    }
    else
    {
        xml_parse_error(string("Xml parsing: Could not find (double array) node with label  ") +array_id + " in node " + string(node->Value()));
    }
}


vector<int> XMLTools::get_int_array(TiXmlNode* node, const char * array_id)
{
    if(!node) throw string("XMLTools getstringarray null node");
    TiXmlNode* the_values = node->FirstChild( array_id );
    if(the_values){
        vector<int> result;
        for ( TiXmlNode* child = the_values->FirstChild(); child != 0; child = child->NextSibling())
        {
            if(!child->FirstChild())
            {
                xml_parse_error( string("Xml parsing: Error while reading element int array with label ") +array_id + " in node " + string(node->Value()));
            }
            else
                result.push_back(atoi(child->FirstChild()->Value()));
        }
        return result;
    }
    else
    {
        xml_parse_error(string("Xml parsing: Could not find (int array) node with label  ") +array_id + " in node " + string(node->Value()));
    }
}

vector<double> XMLTools::get_double_array(TiXmlNode* node, const char * array_id)
{
    if(!node) throw string("XMLTools getstringarray null node");
    TiXmlNode* the_values = node->FirstChild( array_id );
    if(the_values){
        vector<double> result;
        for ( TiXmlNode* child = the_values->FirstChild(); child != 0; child = child->NextSibling())
        {
            if(!child->FirstChild())
            {
                xml_parse_error( string("Xml parsing: Error while reading element int array with label ") +array_id + " in node " + string(node->Value()));
            }
            else
                result.push_back(atof(child->FirstChild()->Value()));
        }
        return result;
    }
    else
    {
        xml_parse_error(string("Xml parsing: Could not find (int array) node with label  ") +array_id + " in node " + string(node->Value()));
    }
}


vector<float> XMLTools::get_float_array(TiXmlNode* node, const char * array_id)
{
    if(!node) throw string("XMLTools getstringarray null node");
    TiXmlNode* the_values = node->FirstChild( array_id );
    if(the_values){
        vector<float> result;
        for ( TiXmlNode* child = the_values->FirstChild(); child != 0; child = child->NextSibling())
        {
            if(!child->FirstChild())
            {
                xml_parse_error( string("Xml parsing: Error while reading element int array with label ") +array_id + " in node " + string(node->Value()));
            }
            else
                result.push_back(atof(child->FirstChild()->Value()));
        }
        return result;
    }
    else
    {
        xml_parse_error(string("Xml parsing: Could not find (int array) node with label  ") +array_id + " in node " + string(node->Value()));
    }
}

TiXmlDocument * XMLTools::stream_to_node(const string xml_stream)
{
    TiXmlDocument * doc = new TiXmlDocument();

    if(!doc->Parse(xml_stream.c_str()))
        throw string("failed to parse xml stream:\n\t") + xml_stream;

    TiXmlNode* firstnode = doc->FirstChild();
    if(!firstnode)
        throw string("no child in the stream.");

    //we remove the declaration
    if(firstnode->Type() == TiXmlNode::TINYXML_DECLARATION)
        doc->RemoveChild(firstnode);

    return doc;
}

TiXmlDocument * XMLTools::file_to_node(string filename)
{
    TiXmlDocument * doc = new TiXmlDocument();

    if(!doc->LoadFile(filename.c_str()))
    {
        stringstream st;
        st << "failed to parse xml file " << filename << " error " << doc->ErrorDesc() << " line " << doc->ErrorRow() << " column " << doc->ErrorCol();
        throw string(st.str());
    }

    TiXmlNode* firstnode = doc->FirstChild();

    if(!firstnode)
        throw string("no child in the stream.");

    if(!firstnode->Value())
        throw string("first node content is empty.");

    //we remove the declaration
    if(firstnode->Type() == TiXmlNode::TINYXML_DECLARATION)
        doc->RemoveChild(firstnode);

    return doc;
}



/*!
 * The xml stream is checked then wrote to a file
 */
void XMLTools::stream_to_file(string filename, const string stream)
{
    TiXmlDocument * doc = stream_to_node(stream);
    if(!doc) throw string("Could not parse stream");

    TiXmlDeclaration decl("1.0", "" , "");
    doc->InsertBeforeChild(doc->FirstChild(), decl);

    try
    {
        XMLTools::node_to_file(filename , doc);
    }
    catch(const string & st)
    {
        delete doc;
        throw st;
    }
    catch(...)
    {
        delete doc;
    }
    delete doc;
}


void XMLTools::node_to_file(string filename, TiXmlDocument * doc)
{
    if(!doc) throw string("XMLTools noetofile null doc");

    if(filename.length()<4 || (filename.substr(filename.length()-4,4)!=".xml"))
        filename += ".xml";

    bool ok =  doc->SaveFile(filename.c_str());

    if(!ok) throw string("Could not save xml to file" + filename);
}


using namespace std;

void Serializable::load_file()
{
    if(filename=="") filename = class_name()+".xml";
    load_file(filename);
}

Serializable::Serializable()
{
    filename="";
}
Serializable::~Serializable()
{}

void Serializable::load_file(string filename_)
{
    TiXmlDocument * doc = XMLTools::file_to_node(filename_);
    if(!doc) throw string("Failed to load file ") + filename_;

    TiXmlNode * node = doc->FirstChild(class_name().c_str());
    if(!node) throw string("Failed to find node with tag ") + class_name()+ " in xml file " + filename_;

    try
    {
        from_xml(node);
    }
    catch(string exc)
    {
        delete doc;
        throw exc;
    }

    filename = filename_;
}

//serializes to an xml strem including class name
string Serializable::to_xml_stream() const
{
    return "<"+ class_name() + ">" + to_xml() + "</"+ class_name() + ">";
}

void Serializable::save_file()
{
    if(filename=="") filename = class_name() + ".xml";
    save_file(filename);
}

void Serializable::save_file(string filename_)
{
    string result = to_xml();
    string cn = class_name();
    //cout << result << endl;
    XMLTools::stream_to_file(filename_, "<"+cn+">"+ result +"</"+cn+">");
    filename = filename_;
}

void Serializable::from_xml(string xml_stream)
{
	TiXmlDocument * doc = 0;
	TiXmlNode * node = 0;

	try
	{
    doc = XMLTools::stream_to_node(xml_stream);
    if(!doc) throw string("Failed to parse xml stream:\n\t") + xml_stream;

    node = doc->FirstChild();
    if(!node) throw string("Failed to find node in xml stream\n\t") + xml_stream;

    from_xml(node);
	}
	catch(string exc)
	{
	    delete doc;
	    cout << "Failed to extract data from xml stream:\n\t" << exc << endl;
		throw string("Failed to extract data from xml stream:\n\t") + exc;
	}

}

void Serializable::pretty_print() const
{
    TiXmlDocument * doc = XMLTools::stream_to_node("<"+class_name() + ">" + to_xml() + "</"+class_name() + ">");
    if(!doc)
    {
        cout << " Failed to turn object to xml doc" << endl;
        return;
    }

    if(filename != "")
        cout << "Filename " << filename << endl;


    cout << endl;
    doc->Print();
    cout << endl;
    delete doc;
}

ostream & operator<< (ostream & os, Serializable & obj)
{
    if(obj.filename != "")
        os << "Filename: " << obj.filename << endl;
    os << endl << obj.to_xml();
    return os;
}

