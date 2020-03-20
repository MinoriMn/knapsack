#include <string>
#include <vector>
using namespace std;

#ifndef ITEMS_FILE_NAME
#define ITEMS_FILE_NAME "items.csv"
#endif

#ifndef N_ITEM
#define N_ITEM
//物品データ
class NSItem
{
private:
  string name;
  float weight;
  float value;
public:
  NSItem(string n, float w, float v);
  string getName();
  float getWeight();
  float getValue();

  string toString();
};

vector<string> splitCsv(string& input, char delimiter);
//物品読み込み
vector<NSItem> readItems();
#endif
