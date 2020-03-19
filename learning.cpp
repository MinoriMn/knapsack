#include <vector>
#include <random>
#include <algorithm> // std::copy
#include <iterator> // std::back_inserter
#include "learning.hpp"
using namespace std;

//親選択
//ルーレット方式
vector<gene> Roulette::select(vector< pair<gene,float> >  population, int parentNum){
  float evSum = 0;//評価値合計
  int idx = 0;

  //評価値集計
  for(pair<gene,float> individual : population) {
    evSum += individual.second;
  }

  //ルーレット部
  vector<gene> parents;
  vector< pair<gene,float> >  dPopulation;
  copy(population.begin(), population.end(), back_inserter(dPopulation) );
  //乱数生成 http://siv3d.hateblo.jp/entry/2013/02/17/231829
  random_device random;
  mt19937 mt(random());
  for (int i = 0; i < parentNum; i++) {
    uniform_real_distribution<float> evRandom(0.0,evSum);
    float genEv = evRandom(mt);
    float thresholdEv = 0;

    pair<gene,float> individual;
    for (int j = 0; j < dPopulation.size(); j++) {
      individual = dPopulation.at(j);
      thresholdEv += individual.second;
      if(genEv < thresholdEv){
        parents.push_back(individual.first);
        evSum -= individual.second;
        dPopulation.erase(dPopulation.begin() + j);
        break;
      }
    }
  }

  return parents;
}

vector<gene> OnePointCrossOver::cross(vector<gene> parents){
  vector<gene> population;
  int geneSize = parents.at(0).size();
  copy(parents.begin(), parents.end(), back_inserter(population) );
  for (int i = 0; i < parents.size()-1; i++) {
    for (int j = i+1; j < parents.size(); j++) {
      gene child1, child2;
      gene parent1 = parents.at(i);
      gene parent2 = parents.at(j);
      for (int k = 0; k < crossPoint; k++) {
        child1.push_back(parent1.at(k));
        child2.push_back(parent2.at(k));
      }
      for (int k = crossPoint; k < geneSize; k++) {
        child1.push_back(parent2.at(k));
        child2.push_back(parent1.at(k));
      }
      population.push_back(child1);
      population.push_back(child2);
    }
  }

  return population;
}
