#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "n_item.hpp"
using namespace std;

//物品データ
NSItem::NSItem(string n, float w, float v){
  name = n;
  weight = w;
  value = v;
}
string NSItem::toString(){
  string s = name + " w:" + to_string(weight) + " v:" + to_string(value);
  return s;
}


vector<string> splitCsv(string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    vector<string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}
//物品読み込み
vector<NSItem> readItems(){
  ifstream ifs(ITEMS_FILE_NAME);
  string line;
  vector<NSItem> items;
  cout << "物品データ読込開始-----------------------" << endl;

  //ラベル
  getline(ifs, line);
  cout << line << endl;

  //物品データ
  while (getline(ifs, line)) {
      vector<string> strvec = splitCsv(line, ',');

      NSItem item(strvec.at(0), stof(strvec.at(1)), stof(strvec.at(2)));
      cout << item.toString() << endl;
      items.push_back(item);
  }

  cout << "物品データ読込完了-----------------------" << endl;

  return items;
}
