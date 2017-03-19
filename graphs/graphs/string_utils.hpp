#include <vector>
#include <string>

#ifndef STRING_UTILS_HPP_INCLUDED
#define STRING_UTILS_HPP_INCLUDED
using namespace std;

template<typename OUT> void split(const string &, char, OUT);
vector<string> split(const string &, char);
string strip(string instring, char strip_char);

#endif // STRING_UTILS_HPP_INCLUDED
