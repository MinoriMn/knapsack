#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

string vecIntToString(vector<int> vec){
  stringstream ss;
  copy( vec.begin(), vec.end(), ostream_iterator<int>(ss, ""));
  string s = ss.str();

  return s;
}
