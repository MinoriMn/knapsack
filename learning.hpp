#include <vector>
using namespace std;

#ifndef LEARNING
#define LEARNING

typedef vector<int> gene;//遺伝子配列
//親選択方法(親クラス)
class ParentSelect{
public:
  virtual vector<gene> select(vector< pair<gene,float> > population, int parentNum) = 0;
};
//ルーレット選択
class Roulette : public ParentSelect{
public:
  virtual vector<gene> select(vector< pair<gene,float> > population, int parentNum);
};

//交叉(親クラス)
class CrossOver{
public:
  virtual void cross(vector<gene> parents) = 0;
};
//一点交叉
class OnePointCrossOver{
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
  ParentSelect* select;
  CrossOver* crossOver;

  int parentNum;//親選択数
  vector<gene> population;//個体群

  void init();//初期集団生成
  void oneGeneration();//1世代の実行
public:
  GA(int generation, int initPopulationNum, int parentNum, ParentSelect* parentSelect, CrossOver* crossOver);
  void start();
};


#endif
