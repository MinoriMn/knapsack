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
  double weight;
  double value;
public:
  NSItem(string n, double w, double v);
  string toString();
};

vector<string> splitCsv(string& input, char delimiter);
//物品読み込み
vector<NSItem> readItems();
#endif
