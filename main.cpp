#include <iostream>
#include "n_item.hpp"
#include "learning.hpp"
#include "utility.hpp"
using namespace std;

// 学習結果書き出し
void writeLearningData(vector<NSItem> items){
}

void readyLearningData(vector<NSItem> items){
  int parentNum = 3;
  int initPopulationNum = 1;
  for(int i = 1; i <= parentNum; ++i) {
    initPopulationNum = initPopulationNum * i;
  };
  initPopulationNum += parentNum;
  float weightThreshold = 300;
  //親選択方法
  Roulette roulette;
  //交叉方法
  OnePointCrossOver onePointCrossOver(3);
  //突然変異確率
  float mutationRate = 0.1;
  //GA(int generation, vector<NSItem> items, int initPopulationNum, int parentNum, float weightThreshold, ParentSelect* parentSelect, CrossOver* crossOver, float mutationRate)
  GA ga(2, items, initPopulationNum, parentNum, weightThreshold, dynamic_cast<Roulette*>(&roulette), dynamic_cast<OnePointCrossOver*>(&onePointCrossOver), mutationRate);
  ga.start();
}

int main(){
  //物品読み込み
  vector<NSItem> items = readItems();
  cout << "物品サイズ: " << items.size() << endl;

  readyLearningData(items);

  writeLearningData(items);
}
