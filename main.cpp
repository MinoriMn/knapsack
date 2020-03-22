#include <iostream>
#include "n_item.hpp"
#include "learning.hpp"
#include "utility.hpp"
#include "matplotlib.hpp"
using namespace std;

#define GA_GRAPH_FILE_NAME "ga_result_graph.pdf"

// 学習結果書き出し
void writeGAData(vector<NSItem> items, GA ga){
  matplotlib plot;
  vector<GenerationRecord> generationRecords = ga.getGenerationRecord();
  int generation = generationRecords.size();

  cout << "グラフ書き出し開始-----------------------" << endl;
  plot.open();
  // set drawing range
  plot.screen(-5, 0, generation + 5, 8000);

  float preAveEv = 1;
  float preAveEvNotOne = 0;
  float preMaxEv = 1;

  for (int g = 0; g < generation; g++) {
    GenerationRecord record = generationRecords[g];
    float aveEv = record.getAveEv();
    float aveEvNotOne = record.getAveEvNotOne();
    float maxEv = record.getMaxEv();

    plot.line(g - 1, preAveEv, g, aveEv, "green", "linewidth=1");
    plot.line(g - 1, preAveEvNotOne, g, aveEvNotOne, "red", "linewidth=1");
    plot.line(g - 1, preMaxEv, g, maxEv, "blue", "linewidth=2");

    preAveEv = aveEv;
    preAveEvNotOne = aveEvNotOne;
    preMaxEv = maxEv;
  }

  plot.save(GA_GRAPH_FILE_NAME);
  // getchar();
  // finish drawing
  plot.close();
  cout << "グラフ書き出し終了----------------------" << endl;
}

GA runGA(int generation, vector<NSItem> items, int initPopulationNum, float weightThreshold){
  //親選択方法
  vector<ParentSelect*> parentSelects;
  Elite elite(1); parentSelects.push_back(dynamic_cast<ParentSelect*>(&elite));
  Roulette roulette(3); parentSelects.push_back(dynamic_cast<ParentSelect*>(&roulette));
  //交叉方法
  OnePointCrossOver onePointCrossOver(items.size()/2);
  //突然変異確率
  float mutationRate = 0.05;
  //GA(int generation, vector<NSItem> items, int initPopulationNum, float weightThreshold, ParentSelect* parentSelect, CrossOver* crossOver, float mutationRate)
  GA ga(generation, items, initPopulationNum, weightThreshold, parentSelects, dynamic_cast<CrossOver*>(&onePointCrossOver), mutationRate);
  ga.start();

  return ga;
}

//(グラフ書き出しファイル名)
int main(int argc, char *argv[]){
  //物品読み込み
  vector<NSItem> items = readItems();
  cout << "物品サイズ: " << items.size() << endl;
  int parentNum = 1 + 3;
  int generation = 1000;
  int initPopulationNum = 1;
  for(int i = 1; i <= parentNum; ++i) {
    initPopulationNum = initPopulationNum * i;
  };
  initPopulationNum += parentNum;
  float weightThreshold = 400;
  GA ga = runGA(generation, items, initPopulationNum, weightThreshold);

  writeGAData(items, ga);
}
