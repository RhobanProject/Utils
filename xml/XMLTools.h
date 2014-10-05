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

#include <stdexcept>
#include <type_traits>

#ifndef MOTORPRIMITIVEXML_H_
#define MOTORPRIMITIVEXML_H_

using namespace std;

#define xml_parse_error(str,...)   { throw runtime_error(str); }
#define interpretor_error(str,...) { throw runtime_error(str); }

#define XML_WRITE_GENERIC(result, value, label ){ result << "<" << # label << ">" << value << "</" <<  # label << ">" << endl; }

#define XML_WRITE(result, truc )		XML_WRITE_GENERIC(result, truc, truc)
#define XML_WRITE_INT(result, truc)		XML_WRITE_GENERIC(result, (int) truc, truc)
#define XML_WRITE_CHAR(result, truc)	XML_WRITE_GENERIC(result, (int) truc, truc)
#define XML_WRITE_BOOL(result, truc)	XML_WRITE_GENERIC(result, ( truc ? "true" : "false"), truc)
#define XML_WRITE_DOUBLE(result, truc)  result.precision(100); XML_WRITE(result, truc)
#define XML_WRITE_STRING(result, truc ) XML_WRITE(result, truc )

#define XML_WRITE_STRING_ARRAY(result, truc){ \
	result << "<" << # truc << ">"; \
	for(int i = 0 ; i < truc.size(); i++) \
		result << "<string>" << truc[i] << "</string>"; \
	result << "</" << # truc << ">"; \
}

#define XML_WRITE_SERIALIZABLE(result, truc) {                                \
	result << "<" << # truc << ">" << truc.to_xml() << "</" << # truc << ">"; \
}

#define	XML_READ_GENERIC(node, variable, label){ variable = XMLTools::get_double_element(node, # label); }

#define	XML_READ_INT(node, truc){ try{ truc = XMLTools::get_int_element(node, # truc); } catch(...){}}
#define	XML_READ_INT_ARRAY(node, truc){try{  truc = XMLTools::get_int_array(node, # truc); } catch(...){} }
#define	XML_READ_BOOL(node, truc){ try{ truc = XMLTools::get_bool_element(node, # truc); } catch(...){} }
#define	XML_READ_CHAR(node, truc){ try{ truc = XMLTools::get_int_element(node, # truc); } catch(...){} }
#define	XML_READ_DOUBLE(node, truc){try{  truc = XMLTools::get_double_element(node, # truc); } catch(...){} }
#define	XML_READ_DOUBLE_ARRAY(node, truc){try{  truc = XMLTools::get_double_array(node, # truc); } catch(...){} }
#define	XML_READ_FLOAT(node, truc){ try{ truc = XMLTools::get_float_element(node, # truc); } catch(...){} }
#define	XML_READ_FLOAT_ARRAY(node, truc){try{  truc = XMLTools::get_float_array(node, # truc); } catch(...){} }
#define	XML_READ_STRING(node, truc){ try{ truc = XMLTools::get_string_element(node, # truc); } catch(...){} }
#define	XML_READ_STRING_ARRAY(node, truc){try{  truc = XMLTools::get_string_array(node, # truc); } catch(...){} }
#define XML_READ_SERIALIZABLE(node, truc)           \
  { \
try{ \
	\
    TiXmlNode * child;                              \
    if ((child = node->FirstChild(# truc)) != 0 ) \
	  truc.from_xml(child);                         \
	}\
	catch (...){}\
  }

#define XML_READ_MAP(node, truc, keytype, valuetype) {try{ truc = XMLTools::get_map<keytype,valuetype>(node, # truc); } catch(...){} }
#define XML_READ_VECTOR(node, truc, valuetype) {try{ truc = XMLTools::get_array<valuetype>(node, # truc); } catch(...){} }

/*****************************************************************************/
/*
*/
namespace XMLTools
{
	float get_float_value(TiXmlNode * node);
	double get_double_value(TiXmlNode * node);
	int get_int_value(TiXmlNode * node);
	string get_string_value(TiXmlNode * node);



	template <typename T> struct is_vector { static const bool value = false; };
	template <typename T> struct is_vector< std::vector<T> > { static const bool value = true; };

	// metafunction to extract what type a vector is specialised on
	// vector_type<vector<T>>::type == T
	template <class T>
	struct vector_type
	{
	private:
		template <class T>
		struct ident
		{
			typedef T type;
		};

		template <class C>
		static ident<C> test(vector<C>);

		static ident<void> test(...);

		typedef decltype(test(T())) vec_type;
	public:
		typedef typename vec_type::type type;
	};

	template < typename T >
//	const typename enable_if< is_not_vector<T>::value , T>::type
	T get_value(TiXmlNode * node);

	template <>
	float get_value<float>(TiXmlNode * node){ return get_float_value(node); };

	template <>
	int get_value<int>(TiXmlNode * node){ return get_int_value(node); };

	template <>
	string get_value<string>(TiXmlNode * node){ return get_string_value(node); };

	template <>
	double get_value<double>(TiXmlNode * node){ return get_double_value(node); };


	template <typename T>
	const typename enable_if<is_vector<T>::value, T>::type
		get_value(TiXmlNode * node)
	{
		T result;
		if (!node) throw string("XMLTools getstringarray null node");
		for (TiXmlNode* child = node; child != 0; child = child->NextSibling())
			if (!child->FirstChild())
				xml_parse_error(string("Xml parsing: Error while reading element int array with label ") + array_id + " in node " + string(node->Value()));
			else
				result.push_back(get_value< vector_type<T>::type >(child->FirstChild()));
		return result;
	}

	
	template < typename T>
	const typename enable_if<!is_vector<T>::value, T>::type
	get_element(TiXmlNode * node, const char * id)
	{
		if (!node) throw runtime_error("XMLTools getstringelement null node");
		TiXmlNode * the_father = node->FirstChild(id);
		if (the_father)
		{
			TiXmlNode* the_child = the_father->FirstChild();
			if (the_child)
				return get_value<T>(the_child);
			else
				xml_parse_error(string("XMLTools null child node"));
		}
		else
			xml_parse_error(string("Xml parsing: could not find node with label ") + id + " in node " + string(node->Value()));
	}


	template <typename T>
	const typename enable_if<is_vector<T>::value, T>::type
		get_element(TiXmlNode * node, const char * id)
	{
		if (!node) throw runtime_error("XMLTools getstringelement null node");
		TiXmlNode * the_father = node->FirstChild(id);
		if (the_father)
		{
			TiXmlNode* the_child = the_father->FirstChild();
			if (the_child)
			{
				T result;
				if (!node) throw string("XMLTools getstringarray null node");
				for (TiXmlNode* child = node; child != 0; child = child->NextSibling())
					if (!child->FirstChild())
					{
					xml_parse_error(string("Xml parsing: Error while reading element int array with label ") + string(id) + " in node " + string(node->Value()));
					}
					else
						result.push_back(get_value< vector_type<T>::type >(child->FirstChild()));
				return result;
			}
			else
				xml_parse_error(string("XMLTools null child node"));
		}
		else
			xml_parse_error(string("Xml parsing: could not find node with label ") + id + " in node " + string(node->Value()));
	}


	float get_float_element(TiXmlNode * node, const char * id){ return get_element<float>(node, id); };
	double get_double_element(TiXmlNode * node, const char * id){ return get_element<double>(node, id); };
	int get_int_element(TiXmlNode * node, const char * id){ return get_element<int>(node, id); };
	bool get_bool_element(TiXmlNode * node, const char * id){ return get_element<bool>(node, id); };
	string get_string_element(TiXmlNode * node, const char * id){ return get_element<string>(node, id); };

	

    bool has_child(TiXmlNode *node, const char *name);

    TiXmlNode *get_child(TiXmlNode *node, const char *name);



	vector<float> get_float_array(TiXmlNode * node, const char * id){ return get_element< vector<float> >(node, id); }
	vector<int> get_int_array(TiXmlNode * node, const char * id){ return get_element< vector<int> >(node, id); }
	vector<string> get_string_array(TiXmlNode * node, const char * id){ return get_element< vector<string> >(node, id); }
	vector<double> get_double_array(TiXmlNode * node, const char * id){ return get_element< vector<double> >(node, id); }

	template <typename T, typename U>
	map<T, U> get_map(TiXmlNode * node, const char * id)
	{
		if (!node) throw string("XMLTools getstringarray null node");
		TiXmlNode* the_values = node->FirstChild(array_id);
		if (the_values){
			map<T,U> result;
			for (TiXmlNode* child = the_values->FirstChild(); child != 0; child = child->NextSibling())
			{
				TiXmlNode* key = child->FirstChild();
				if (!key)
					xml_parse_error(string("Xml parsing: Error while reading map key with label ") + array_id + " in node " + string(node->Value()));
				TiXmlNode* value = key->NextSibling();
				if (!value)
					xml_parse_error(string("Xml parsing: Error while reading map value with label ") + array_id + " in node " + string(node->Value()));
				else
					result[get_element<T>(key)] = get_element<U>(value);
			}
			return result;
		}
		else
		{
			xml_parse_error(string("Xml parsing: Could not find (int array) node with label  ") + array_id + " in node " + string(node->Value()));
		}
	}

	float * get_float_array_with_3_element(TiXmlNode * node, const char * array_id);

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
        virtual void from_xml(TiXmlNode *node) {
          (void) node;//Suppress unused warning
          throw string("from_xml not implemented");
        };

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
