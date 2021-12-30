/*
 * sasb_ecbs.h
 *
 */

#pragma once
#include "cbs.h"


class SASB_ECBS : public CBS {
protected:
  float w;  // sub-optimal factor
  std::unordered_map<int, int> table_fmin;  // record min of f-value

  virtual void init();
  int h3(Paths &paths);
  int h3(Agent* a, Nodes& p1, Paths &paths);
  bool solvePart(Paths& paths, Agents& block);
  void invoke(CTNode* node, Agents& block);
  virtual Nodes AstarSearch(Agent* a, CTNode* node);
  void getPartialPath(AN* n, Nodes &path);

public:
  SASB_ECBS(Problem* _P, float _w);
  SASB_ECBS(Problem* _P, float _w, bool _ID);
  ~SASB_ECBS();
  int lowlevelnode;
  int conflict_cnt;
  int cnt;
  std::vector<std::pair<int,int>> vec[50];

  virtual std::string logStr();
  uint64_t timeSinceEpochMillisec();
  void writeDiscoveredPath(int i,std::vector<std::pair<int,int>> & mat);
  void print_paths(Paths &paths);
};
