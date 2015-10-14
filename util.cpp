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
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "util.h"
#include <ctime>
#include <cerrno>

using namespace std;

std::string slurpFile(const std::string& path)
{
  std::ifstream in(path, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw std::runtime_error("Failed to open file '" + path + "'");
}

bool is_in_vector_string(vector<string> vector, string testval)
{
    for(unsigned int i=0; i<vector.size(); ++i)
    {
        if(vector[i].compare(testval) == 0)
            return 1;
    }
    return 0;
}

int char_to_int(char c){
    if ((int) c >= (int) 'a') return ((int) c - (int)'a' + 10);
    if ((int) c >= (int) 'A') return ((int) c - (int)'A' + 10);
    return ((int) c - (int) '0');
}


int hex_to_int(char * argv){
    if(argv[0]!='x'){
        return 0;
    }
    int len = strlen(argv)-1;
    unsigned int arg1=0;
    int i=0;
    for(i=0;i<len;i++)arg1 = 16*arg1 + char_to_int(argv[i+1]);
    return arg1;
}

inline int string_dec_to_int(char * argv){
    int len = strlen(argv);
    unsigned int arg1=0;
    int i=0;
    for(i=0;i<len;i++)arg1 = 10*arg1 + char_to_int(argv[i]);
    return arg1;
}
inline  int string_hex_to_int(char * argv){
    int len = strlen(argv);
    unsigned int arg1=0;
    int i=0;
    for(i=0;i<len;i++)arg1 = 16*arg1 + char_to_int(argv[i]);
    return arg1;
}


inline int string_bin_to_int(char * argv){
    int len = strlen(argv);
    unsigned int arg1=0;
    int i=0;
    for(i=0;i<len;i++)arg1 = 2*arg1 + char_to_int(argv[i]);
    return arg1;
}
int string_to_int(char * argv){
    switch(argv[0]){
        case 'd': return  string_dec_to_int(argv+1); break;
        case 'x': return  string_hex_to_int(argv+1); break;
        case 'b': return  string_bin_to_int(argv+1); break;
        default: return  string_dec_to_int(argv); break;
    }
}




//returns true or false if parameter is there or not
int is_parameter(string param_name, int argc, char * argv[])
{
    for(int i =1;i<argc;i++)
        if(!param_name.compare(argv[i]))
            return i;
    return 0;
}

//returns (false,"") is parameter was not found
//returns (true,val) if parameter was found, val beoing the string following parameter filename
pair<bool,string> get_parameter(string param_name, int argc, char * argv[])
{
    int n = is_parameter(param_name, argc, argv);
    if(n<=0 || n>=argc-1)
        return pair<bool,string>(false,string(""));
    else
        return pair<bool,string>(true,string(argv[n+1]));
}

pair<bool,int> get_int_parameter(string param_name, int argc, char * argv[])
{
    int n = is_parameter(param_name, argc, argv);
    if(n<=0 || n>=argc-1)
        return pair<bool,int>(false,0);
    else
        return pair<bool,int>(true,atoi(argv[n+1]));
}

bool get_int_parameter(string param_name, int * arg1, int argc, char * argv[])
{
    int n = is_parameter(param_name, argc, argv);
    if(n<=0 || n>=argc-1)
        return false;
    else
    {
        *arg1 = atoi(argv[n+1]);
        return true;
    }
}

bool get_int_int_parameter(string param_name, int * arg1, int * arg2, int argc, char * argv[])
{
    int n = is_parameter(param_name, argc, argv);
    if(n<=0 || n>=argc-2)
        return false;
    else
    {
        *arg1 = atoi(argv[n+1]);
        *arg2 = atoi(argv[n+2]);
        return true;
    }
}

bool get_int_int_int_parameter(string param_name, int * arg1, int * arg2, int * arg3, int argc, char * argv[])
{
    int n = is_parameter(param_name, argc, argv);
    if(n<=0 || n>=argc-3)
        return false;
    else
    {
        *arg1 = atoi(argv[n+1]);
        *arg2 = atoi(argv[n+2]);
        *arg3 = atoi(argv[n+3]);
        return true;
    }
}

list<string> &split_list(const string &s, char delim, list<string> &elems) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

string system_time() {
  time_t t = time(0);   // get time now
  struct tm * now = localtime( & t );
  stringstream str;
  str << (now->tm_year + 1900) << '-' 
       << (now->tm_mon + 1) << '-'
       <<  now->tm_mday
       << "-" << now->tm_hour
       << "-" << now->tm_min
       << "-" << now->tm_sec;
  return str.str();
}

bool endsWith(std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

vector<string> getLines(const string &header)
{
    vector<string> lines;
    string line = "";
    for (unsigned int pos=0; pos<header.length(); pos++) {
        if (header[pos] == '\r' || header[pos] == '\n') {
            if (line != "") {
                lines.push_back(line);
            }
            line = "";
        } else {
            line += header[pos];
        }
    }
    return lines;
}

std::string camelize(std::string input)
{
#ifndef MSVC
    std::string output;
    bool caps = false;

    for (unsigned int k=0; k<input.size(); k++) {
        if (std::isspace(input[k])) {
            caps = true;
        } else {
            if (caps) {
                caps = false;
                output += toupper(input[k]);
            } else {
                output += input[k];
            }
        }
    }

    return output;
#else
	throw std::exception("Unimplemented");
#endif
}

string today()
{
	time_t tt;
	time(&tt);
	auto ttt = localtime(&tt);
	char result[80];
	strftime(result, 80, "%Y_%m_%d", ttt);
	return string(result);
}
