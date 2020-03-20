#include <iostream>
#include "n_item.hpp"
#include "learning.hpp"
#include "utility.hpp"
using namespace std;

// 学習結果書き出し
void writeLearningData(vector<NSItem> items){
}

void readyLearningData(vector<NSItem> items){
  //親選択方法
  Roulette roulette;
  //交叉方法
  OnePointCrossOver onePointCrossOver(3);
  int parentNum = 3;
  int initPopulationNum = 1;
  for(int i = 1; i <= parentNum; ++i) {
    initPopulationNum = initPopulationNum * i;
  };
  initPopulationNum += parentNum;
  //GA(int generation, vector<NSItem> items, int initPopulationNum, int parentNum, ParentSelect* parentSelect, CrossOver* crossOver)
  GA ga(1000, items, initPopulationNum, parentNum, dynamic_cast<Roulette*>(&roulette), dynamic_cast<OnePointCrossOver*>(&onePointCrossOver));
}

int main(){
  //物品読み込み
  vector<NSItem> items = readItems();
  cout << "物品サイズ: " << items.size() << endl;

  readyLearningData(items);

  writeLearningData(items);
}
