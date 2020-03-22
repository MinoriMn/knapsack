#include <vector>
#include "n_item.hpp"
using namespace std;

#ifndef LEARNING
#define LEARNING

typedef vector<int> gene;//遺伝子配列

//各世代の記録
class GenerationRecord
{
private:
  vector<pair<gene,float> > population;
  int maxIdx;
  float maxEv;//最大値
  float aveEv;//平均
  float aveEvNotOne;//平均(評価1を除く)
public:
  GenerationRecord(vector<pair<gene,float> > population, int maxIdx, float maxEv, float aveEv, float aveEvNotOne);
  vector<pair<gene,float> > getPopulationAndEv();
  int getMaxidx();
  float getMaxEv();
  float getAveEv();
  float getAveEvNotOne();
};
//親選択方法(親クラス)
class ParentSelect{
public:
  int parentNum;
  ParentSelect(int parentNum);
  virtual vector<gene> select(vector<pair<gene,float> > population) = 0;
};
//ルーレット選択
class Roulette : public ParentSelect{
public:
  Roulette(int parentNum):ParentSelect(parentNum){}
  virtual vector<gene> select(vector<pair<gene,float> > population);
};
//エリート選択
class Elite : public ParentSelect{
public:
  Elite(int parentNum):ParentSelect(parentNum){}
  virtual vector<gene> select(vector<pair<gene,float> > population);
};

//交叉(親クラス)
class CrossOver{
public:
  virtual vector<gene> cross(vector<gene> parents) = 0;
};
//一点交叉
class OnePointCrossOver : public CrossOver{
private:
  int crossPoint; //分割点index(設定値より後ろの値を入れ替える)
public:
  OnePointCrossOver(int crossPoint){
    this->crossPoint = crossPoint;
  }
  virtual vector<gene> cross(vector<gene> parents);
};

class GA{
private:
  int finGeneration;//終了世代
  int generation;

  float weightThreshold;//重さの閾値

  vector<ParentSelect*> parentSelects;
  CrossOver* crossOver;

  vector<NSItem> items;
  vector<gene> population;//個体群

  float mutationRate;//突然変異確率

  vector<GenerationRecord> record;

  void init(int initPopulationNum);//初期集団生成
  void oneGeneration(int gen);//1世代の実行
  vector<pair<gene,float> > evaluate();//評価
  vector<gene> mutation(vector<gene> population);//突然変異
  GenerationRecord makeRecord(vector<pair<gene,float> > population);//世代の記録
public:
  GA(int generation, vector<NSItem> items, int initPopulationNum, float weightThreshold, vector<ParentSelect*> parentSelects, CrossOver* crossOver, float mutationRate);
  void start();
  vector<GenerationRecord> getGenerationRecord();
};


#endif
