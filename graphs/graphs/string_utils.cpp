#include <string>
#include <sstream>
#include <vector>
#include <iterator>

#include "string_utils.hpp"

using namespace std;


template<typename OUT> void split(const string &s, char delim, OUT result){
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)){
        *(result++) = item;
    }
}


vector<string> split(const string &s, char delim){
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}


string strip(string instring, char strip_char){
    size_t pos = instring.find_first_not_of(strip_char);
    instring.erase(0, pos);
    pos = instring.find_last_not_of(strip_char);
    if (string::npos != pos){
        instring.erase(pos + 1);
    }
    return instring;
}
