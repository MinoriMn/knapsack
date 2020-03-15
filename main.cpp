#include <iostream>
#include "n_item.hpp"
using namespace std;

//学習結果書き出し
// void writeLearningData(NSItem* head){
//   //物品データ解放
//   freeItems(head);
// }

int main(){
  vector<NSItem> items = readItems();

  cout << "物品サイズ: " << items.size() << endl;

  // writeLearningData(itemsHead);
}
