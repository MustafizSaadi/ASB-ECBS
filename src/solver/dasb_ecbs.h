/*
 * dasb_ecbs.h
 */

#pragma once
#include "cbs.h"
#include <map>


class DASB_ECBS : public CBS {
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
  DASB_ECBS(Problem* _P, float _w);
  DASB_ECBS(Problem* _P, float _w, bool _ID);
  ~DASB_ECBS();
  int lowlevelnode;
  int dtime;
  int conflict_cnt;
  int cnt;
  std::map< int, std::vector<double> > mp;

  virtual std::string logStr();
  uint64_t timeSinceEpochMillisec();
};
