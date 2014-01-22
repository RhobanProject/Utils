/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef UTIL_H
#define UTIL_H

typedef unsigned char ui8;
typedef unsigned short ui16;
typedef unsigned int ui32;
typedef unsigned int uint;

#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <list>

using namespace std;

bool is_in_vector_string(vector<string> vector, string testval);

template <typename T>
bool is_in(vector<T> lst, T x) {
  for (int i=0; i < (int) lst.size(); i++)
    if (x==lst[i]) return true;
  return false;
}

/* extract the subvector of lst regarding indexes [i0,i1] included */
template <typename T>
vector<T> v_extract_subvector(vector<T> & lst, int i0, int i1) {
  vector<T> result;
  if (i0 < 0 || i1 < 0 || 
      i0 > ((int) lst.size()-1) ||
      i1 > ((int) lst.size()-1) ||
      i0 > i1) return result;
  for (int i=0; i < i1-i0+1; i++)
    result.push_back(lst[i0+i]);
  return result;
}

inline string my_itoa(int i)
{
	ostringstream os;
	os << i;
	return os.str();
}

int char_to_int(char c);
int hex_to_int(char * argv);
int string_to_int(char * argv);

//TODO: eliminer my_trunc
#define my_trunc(x,a,b) { if ((x) < (a)) x=a; if ((x) > (b)) x=b; }

// Truncate the value x and return the new value
#define interval_trunc(x,a,b) ( ((x)<(a)) ? x=a : ( ((x)>(b))? x=b : x ) )
#define abs_value(x) (((x)>=0)?(x):-(x))

/*****************************************************************************/
#define BOT_VERBOSE_MODE 1

#define BOT_VERBOSE(x,...) do {                                   \
	if ( BOT_VERBOSE_MODE ) { printf(x,...); fflush(stdout); }   \
} while(0);

#define BOT_ERROR(x,...) do {                                     \
    printf("Bot Error: "); printf(x,...); fflush(stdout);            \
} while(0);

/*****************************************************************************/
#define check_opt(option) (argc>1 && strcmp(argv[1], option)==0)
/*****************************************************************************/

int is_parameter(string param_name, int argc, char * argv[]);
pair<bool,string> get_parameter(string param_name, int argc, char * argv[]);
pair<bool,int> get_int_parameter(string param_name, int argc, char * argv[]);
bool get_int_parameter(string param_name, int * arg1, int argc, char * argv[]);
bool get_int_int_parameter(string param_name, int * arg1, int * arg2, int argc, char * argv[]);
bool get_int_int_int_parameter(string param_name, int * arg1, int * arg2, int * arg3, int argc, char * argv[]);

/*****************************************************************************/
/*! \name Tools (\todo: to be put anywhere else !
 *****************************************************************************/
/*@{*/

//Hug the following lines may conflict with some C++ libraries I suspect
#define my_min(a,b) (((a)<(b))? (a) : (b))
#define my_max(a,b) (((a)>(b))? (a) : (b))

template<typename T>
void list_concat(std::list<T> & dest, const std::list<T> src) {
  for (typename std::list<T>::const_iterator elt = src.begin(); elt != src.end(); elt++)
    dest.push_back(*elt);
}

template<typename T>
bool list_contains(std::list<T> l, T elt) {
	for (typename std::list<T>::iterator e = l.begin(); e != l.end(); e++)
		if ((*e) == elt) return true;
	return false;
}

template<typename T>
std::list<T> vector_to_list(std::vector<T> & V) {
  std::list<T> L;
  for (int i=0; i<(int)V.size(); i++)
    L.push_back(V[i]);
  return L;
}

vector<string> &split(const string &s, char delim, vector<string> &elems);
list<string> &split_list(const string &s, char delim, list<string> &elems);

template<typename T>
inline string join(vector<T> tab, string delimiter) {
    ostringstream oss;
    int n = tab.size();
    for (int i=0; i<n; i++) {
        oss << tab[i];
        if (i != n-1) {
            oss << delimiter;
        }   
    }   

    return oss.str();
}

string system_time();

/*@}*/
#endif
