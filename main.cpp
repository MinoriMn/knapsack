#include <iostream>
#include "n_item.hpp"
#include "learning.hpp"
using namespace std;

// 学習結果書き出し
void writeLearningData(vector<NSItem> items){
}

void readyLearningData(){

}

int main(){
  //物品読み込み
  vector<NSItem> items = readItems();

  cout << "物品サイズ: " << items.size() << endl;

  writeLearningData(items);
}
