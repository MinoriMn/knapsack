#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <algorithm> // std::copy
#include <iterator> // std::back_inserter
#include "n_item.hpp"
#include "learning.hpp"
#include "utility.hpp"
using namespace std;

//親選択
//ルーレット方式
vector<gene> Roulette::select(vector<pair<gene,float> >  population, int parentNum){
  float evSum = 0;//評価値合計
  int idx = 0;

  //評価値集計
  for(pair<gene,float> individual : population) {
    evSum += individual.second;
  }

  //ルーレット部
  vector<gene> parents;
  vector<pair<gene,float> >  dPopulation;
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
  vector<gene> children;
  int geneSize = parents.at(0).size();
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
      children.push_back(child1);
      children.push_back(child2);
    }
  }

  return children;
}

GA::GA(int generation, vector<NSItem> items, int initPopulationNum, int parentNum, float weightThreshold, ParentSelect* parentSelect, CrossOver* crossOver, float mutationRate){
  this->generation = 0;
  finGeneration = generation;

  copy(items.begin(), items.end(), back_inserter(this->items) );

  this->parentNum = parentNum;
  this->weightThreshold = weightThreshold;
  this->parentSelect = parentSelect;
  this->crossOver = crossOver;
  this->mutationRate = mutationRate;
  init(initPopulationNum);
}
//初期集団生成
void GA::init(int initPopulationNum){
  cout << "初期集団生成開始-----------------------" << endl;
  //乱数生成 http://siv3d.hateblo.jp/entry/2013/02/17/231829
  random_device random;
  mt19937 mt(random());
  uniform_int_distribution<int> geneGen(0,1);
  //遺伝子生成
  for (int i = 0; i < initPopulationNum; i++) {
    gene individual;
    for (int j = 0; j < items.size(); j++) {
      individual.push_back(geneGen(mt));
    }
    population.push_back(individual);
    //string s = vecIntToString(individual);
    //cout << s << endl;
  }

  cout << "初期集団生成終了-----------------------" << endl;
}

//GA実行
void GA::start(){
  for (int i = 0; i < finGeneration; i++) {
    oneGeneration(i);
  }
}
//一世代実行
void GA::oneGeneration(int gen){
  cout << "第" << gen << "世代開始-----------------------" << endl;
  vector<pair<gene,float> > populationAndEv = evaluate();//評価
  vector<gene> parents = parentSelect->select(populationAndEv, parentNum);//親選択
  vector<gene> children = crossOver->cross(parents);//子生成
  mutation(children);//突然変異

  copy(parents.begin(), parents.end(), back_inserter(children));
  population = children;
  cout << "第" << gen << "世代終了-----------------------" << endl;
}
//評価
vector<pair<gene,float> > GA::evaluate(){
  vector<pair<gene,float> > populationAndEv;
  for (int i = 0; i < population.size(); i++) {
    gene g = population[i];
    float weight = 0;
    float ev = 1;
    for (int j = 0; j < g.size(); j++) {
      weight += items[j].getWeight() * g[j];
      ev += items[j].getValue() * g[j];
      if(weight > weightThreshold){
        ev = 1;
        break;
      }
    }
    pair<gene,float> p = make_pair(g, ev);
    populationAndEv.push_back(p);
    cout << vecIntToString(g) << " ev:" << ev << " w:" << weight << endl;
  }

  return populationAndEv;
}
//突然変異
void GA::mutation(vector<gene> population){
  //乱数生成 http://siv3d.hateblo.jp/entry/2013/02/17/231829
  random_device random;
  mt19937 mt(random());
  uniform_real_distribution<float> p(0.0,1.0);
  for (int i = 0; i < population.size(); i++) {
    gene g = population.at(i);
    for (int j = 0; j < g.size(); j++) {
      if(p(mt) < mutationRate){
        // cout << "突然変異発生" << vecIntToString(g);
        g[j] = (g[j] + 1) % 2;//ビット反転
        // cout << " > " << vecIntToString(g) << endl;
      }
    }
  }
}
