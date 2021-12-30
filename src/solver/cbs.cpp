/*
 * cbs.cpp
 *
 * Purpose: Conflict-based Search
 *
 * Sharon, G., Stern, R., Felner, A., & Sturtevant, N. R. (2015).
 * Conflict-based search for optimal multi-agent pathfinding.
 *
 * Created by: Keisuke Okumura <okumura.k@coord.c.titech.ac.jp>
 */


#include "cbs.h"
#include <numeric>
#include "../util/util.h"
using namespace std;


CBS::CBS(Problem* _P) : Solver(_P), ID(false) {
  init();
}
CBS::CBS(Problem* _P, bool _ID) : Solver(_P), ID(_ID) {
  init();
}

CBS::~CBS() {}

void CBS::init() {
  G->setRegFlg(true);
}

bool CBS::solve() {
  solveStart();

  Paths PATHS;
  std::vector<Agents> WHOLE;

  // initialize
  for (int i = 0; i < A.size(); ++i) PATHS.push_back({});

  if (!ID) {  // normal CBS
    solvePart(PATHS, A);
    formalizePath(PATHS);

  } else {  // with ID framework
    for (auto a : A) WHOLE.push_back({ a });

    // solve with independent detection
    while (true) {
      std::cout<<"Whole "<<WHOLE.size()<<std::endl;
      for (auto BLOCK : WHOLE) {
        if (!solvePart(PATHS, BLOCK)) {
          solveEnd();
          return false;  // failed
        }
      }
      formalizePath(PATHS);
      if (checkAgents(PATHS, WHOLE)) break;

      // initialize
      PATHS.clear();
      for (int i = 0; i < A.size(); ++i) PATHS.push_back({});
    }
  }

  int maxLength = getMaxLengthPaths(PATHS);
  for (int t = 1; t < maxLength; ++t) {
    for (int i = 0; i < A.size(); ++i) A[i]->setNode(PATHS[i][t]);
    P->update();

    if (P->getTimestep() >= P->getTimestepLimit()) {
	std::cout<<"Timeout"<<std::endl;
	break;
	}
  }

  solveEnd();
  return true;
}

bool CBS::checkAgents(Paths& paths, std::vector<Agents>& whole) {
  int maxLength = getMaxLengthPaths(paths);
  std::vector<Agents> OPEN = whole;
  std::vector<Agents> CLOSE, TMP;
  Agents block1, block2;
  int i, j;
  bool checkAll = true;
  bool checkPart, checkFrac;
  whole.clear();

  while (!OPEN.empty()) {
    block1 = OPEN[0];
    openToClose(block1, OPEN, CLOSE);

    checkFrac = true;
    for (auto block2 : OPEN) {

      checkPart = true;
      for (auto a : block1) {
        if (!checkPart) break;

        auto itrA = std::find_if(A.begin(), A.end(),
                                 [a](Agent* _a) { return a == _a; });
        i = std::distance(A.begin(), itrA);

        for (auto b : block2) {
          if (!checkPart) break;

          auto itrB = std::find_if(A.begin(), A.end(),
                                   [b](Agent* _b) { return b == _b; });
          j = std::distance(A.begin(), itrB);

          for (int t = 0; t < maxLength; ++t) {
            // detect collision
            if (paths[j][t] == paths[i][t]) {
              checkPart = false;
              break;
            }
            // intersection
            if (t == 0) continue;
            if (paths[j][t] == paths[i][t-1] && paths[j][t-1] == paths[i][t]) {
              checkPart = false;
              break;
            }
          }
        }
      }

      // merge
      if (!checkPart) {
        TMP.push_back(block2);
        checkFrac = false;
      }
    }

    if (!checkFrac) checkAll = false;
    Agents newAgents;
    newAgents.insert(newAgents.end(), block1.begin(), block1.end());
    for (auto block2 : TMP) {
      openToClose(block2, OPEN, CLOSE);
      newAgents.insert(newAgents.end(), block2.begin(), block2.end());
    }
    TMP.clear();
    whole.push_back(newAgents);
  }

  OPEN.clear();
  CLOSE.clear();
  return checkAll;
}

bool CBS::solvePart(Paths& paths, Agents& block) {

  cout<< "solvepart" << endl;
  CTNode* node;
  Constraints constraints;
  std::vector<CTNode*> OPEN, ALL;
  bool status = true;

  CTNode* root = new CTNode { {}, {}, 0, nullptr, true, {}, 0 };
  invoke(root, block);
  OPEN.push_back(root);
  ALL.push_back(root);
  bool CAT = std::any_of(paths.begin(), paths.end(),
                         [](Nodes p) { return !p.empty(); });

  while (!OPEN.empty()) {
    auto itr = std::min_element(OPEN.begin(), OPEN.end(),
                                [CAT, this, &paths]
                                (CTNode* n1, CTNode* n2) {
                                  if (CAT && n1->cost == n2->cost) {
                                    int c1 = this->countCollisions(n1, paths);
                                    int c2 = this->countCollisions(n2, paths);
                                    return c1 < c2;
                                  }
                                  return n1->cost < n2->cost;
                                });
    node = *itr;
    constraints = valid(node, block);
    if (constraints.empty()) break;
    OPEN.erase(itr);

    for (auto constraint : constraints) {
      CTNode* newNode = new CTNode { constraint, node->paths,
                                     0, node, true,
                                     {}, 0 };

      // it works, but it is late
      // if (isDuplicatedCTNode(newNode, ALL)) continue;

      invoke(newNode, block);
      if (newNode->valid) {
        OPEN.push_back(newNode);
        ALL.push_back(newNode);
      }
    }
    constraints.clear();
  }

  if (!OPEN.empty()) {  // sucssess
    for (int i = 0; i < paths.size(); ++i) {
      if (!node->paths[i].empty()) {
        paths[i] = node->paths[i];
      }
    }
    status = status && true;
  } else {
    status = false;
  }

  return status;
}

int CBS::countCollisions(CTNode* c, Paths& paths) {
  int collision = 0;
  for (auto p1 : paths) {
    if (p1.empty()) continue;
    for (auto p2 : c->paths) {
      if (p2.empty() || p1[0] == p2[0]) continue;
      for (int t = 0; t < p1.size(); ++t) {
        if (p2.size() < t) {
          if (p1[t] == p2[p2.size() - 1]) ++collision;
          continue;
        }
        if (p1[t] == p2[t]) {
          ++collision;
          continue;
        }
        if (t > 0 && p1[t-1] == p2[t] && p1[t] == p2[t-2]) {
          ++collision;
          continue;
        }
      }
    }
  }

  return collision;
}

void CBS::invoke(CTNode* node, Agents& block) {
  // calc path
  if (node->c.empty()) {  // initail
    Paths paths;
    for (int i = 0; i < A.size(); ++i) paths.push_back({});
    for (auto a : block) {
      auto itr = std::find_if(A.begin(), A.end(),
                              [a](Agent* b) { return a == b; });
      paths[std::distance(A.begin(), itr)] = AstarSearch(a, node);
    }
    node->paths = paths;
  } else {
    Agent* a;
    for (auto c : node->c) {
      a = c->a;
      auto itr = std::find_if(A.begin(), A.end(),
                              [a](Agent* b) { return a == b; });
      node->paths[std::distance(A.begin(), itr)].clear();
    }
    for (auto c : node->c) {
      a = c->a;
      auto itr = std::find_if(A.begin(), A.end(),
                              [a](Agent* b) { return a == b; });
      node->paths[std::distance(A.begin(), itr)] = AstarSearch(a, node);
    }
  }
  if (!node->valid) return;
  calcCost(node, block);
  formalizePathAgents(node, block);
}

void CBS::calcCost(CTNode* node, Agents& block) {
  int cost = 0;
  Node* g;
  Nodes path;
  for (auto a : block) {
    auto itr1 = std::find_if(A.begin(), A.end(),
                            [a](Agent* b) { return a == b; });
    g = a->getGoal();
    path = node->paths[std::distance(A.begin(), itr1)];
    auto itr2 = path.end() - 1;
    while (g == *itr2) --itr2;
    cost += std::distance(path.begin(), itr2);
  }
  node->cost = cost;
}

Constraints CBS::valid(CTNode* node, Agents& block) {
  Paths paths = node->paths;
  int maxLength = node->paths[0].size();
  Constraints constraints = {};
  std::vector<int> ids;
  Node* v;
  Agent *a, *b;
  int i, j;

  for (int t = 1; t < maxLength; ++t) {
    for (int _i = 0; _i < block.size(); ++_i) {
      a = block[_i];
      auto itr1 = std::find_if(A.begin(), A.end(),
                               [a](Agent* _a)
                               { return a->getId() == _a->getId(); });
      i = std::distance(A.begin(), itr1);
      v = paths[i][t];

      // check collision
      ids.clear();
      for (int _j = _i + 1; _j < block.size(); ++_j) {
        b = block[_j];
        auto itr2 = std::find_if(A.begin(), A.end(),
                                 [b](Agent* _b) { return b == _b; });
        j = std::distance(A.begin(), itr2);
        if (paths[j][t] == v) ids.push_back(j);
      }

      if (!ids.empty()) {  // detect collision
        ids.push_back(i);
        for (int k = 0; k < ids.size(); ++k) {
          Constraint constraint;
          for (int l = 0; l < ids.size(); ++l) {
            if (k == l) continue;
            Conflict* c = new Conflict { A[ids[l]], t, v, v, true, "" };
            //setCKey(c);
            setCKey(c, min(A[ids[l]]->getId(),A[ids[k]]->getId()), max(A[ids[l]]->getId(),A[ids[k]]->getId()));
            constraint.push_back(c);
            // if((A[ids[l]]->conflicted_list).size()==0){

            // }
          }
          constraints.push_back(constraint);
        }
        return constraints;
      }

      // check intersection
      auto itr3 = paths.begin() + i;
      auto itr4 = std::find_if(itr3 + 1, paths.end(),
                               [t, itr3](Nodes path) {
                                 if (path.empty()) return false;
                                 return (path[t] == (*itr3)[t-1])
                                   && (path[t-1] == (*itr3)[t]); });
      if (itr4 != paths.end()) {  // detect intersection

        Constraint knownConstraint = getConstraints(node);

        j = std::distance(paths.begin(), itr4);
        Conflict* c1 = new Conflict { A[i], t, (*itr3)[t], (*itr3)[t-1], false, "" };
        Conflict* c2 = new Conflict { A[j], t, (*itr4)[t], (*itr4)[t-1], false, "" };
        // setCKey(c1);
        // setCKey(c2);
        setCKey(c1, min(A[i]->getId(),A[j]->getId()), max(A[i]->getId(),A[j]->getId()));
        setCKey(c2, min(A[i]->getId(),A[j]->getId()), max(A[i]->getId(),A[j]->getId()));
        constraints.push_back({ c1 });
        constraints.push_back({ c2 });
        return constraints;
      }
    }
  }

  return constraints;
}

void CBS::formalizePathAgents(CTNode* node, Agents& block) {
  int maxLength = getMaxLengthPaths(node->paths);
  Node* g;
  int i;
  for (auto a : block) {
    auto itr = std::find_if(A.begin(), A.end(),
                            [a](Agent* b) { return a == b; });
    i = std::distance(A.begin(), itr);
    g = node->paths[i][node->paths[i].size() - 1];
    while (node->paths[i].size() != maxLength) node->paths[i].push_back(g);
  }
  
}

Nodes CBS::AstarSearch(Agent* a, CTNode* node) {
  Constraint constraints = getConstraintsForAgent(node, a);

  Node* _s = a->getNode();
  Node* _g = a->getGoal();

  // ==== fast implementation ====
  // constraint free
  if (constraints.empty()) return G->getPath(_s, _g);

  // know path
  std::string cKey = getCKey(_s, _g, constraints);
  auto itrK = knownPaths.find(cKey);
  if (itrK != knownPaths.end()) {
    if (itrK->second.empty()) node->valid = false;
    return itrK->second;
  }

  // previously computed path
  std::string dKey = cKey;
  if (!constraints.empty()) {
    while (*(dKey.end()-1) != '-') dKey.erase(dKey.end()-1);
    dKey.erase(dKey.end()-1);
  }
  Nodes dPath;
  itrK = knownPaths.find(dKey);
  if (itrK != knownPaths.end()) {
    dPath = itrK->second;
  }

  // goal condition
  bool existGoalConstraint = false;
  int timeGoalConstraint = 0;
  for (auto c: constraints) {
    if (c->onNode && c->v == _g && c->t > timeGoalConstraint) {
      existGoalConstraint = true;
      timeGoalConstraint = c->t;
    }
  }
  // =============================

  Nodes path, tmpPath, C;
  int f, g;
  std::string key;
  bool invalid = true;  // success or not

  boost::heap::fibonacci_heap<Fib_AN> OPEN;
  std::unordered_map<std::string, boost::heap::fibonacci_heap<Fib_AN>::handle_type> SEARCHED;
  std::unordered_set<std::string> CLOSE;  // key
  AN* n = new AN { _s, 0, pathDist(_s, _g), nullptr };
  auto handle = OPEN.push(Fib_AN(n));
  key = getKey(n);
  SEARCHED.emplace(key, handle);

  while (!OPEN.empty()) {
    // argmin
    n = OPEN.top().node;

    // check goal condtion
    if (n->v == _g) {
      if (!existGoalConstraint || timeGoalConstraint < n->g) {
        invalid = false;
        break;
      }
    }

    // ==== fast implementation ====
    tmpPath = G->getPath(n->v, _g);
    if (validShorcut(a, n, _g, constraints, tmpPath)) {
      for (int i = 1; i < tmpPath.size(); ++i) {
        n = new AN { tmpPath[i], 0, 0, n };
      }
      invalid = false;
      break;
    }
    tmpPath.clear();

    // encount previously explored path
    if (!dPath.empty() && n->g <= dPath.size() - 1 && n->v == dPath[n->g]) {
      tmpPath = dPath;
      for (int i = 0; i < n->g; ++i) tmpPath.erase(tmpPath.begin());
      if (validShorcut(a, n, _g, constraints, tmpPath)) {
        for (int i = 1; i < tmpPath.size(); ++i) {
          n = new AN { tmpPath[i], 0, 0, n };
        }
        invalid = false;
        break;
      }
    }
    // =============================

    // update list
    OPEN.pop();
    CLOSE.emplace(getKey(n));

    // search neighbor
    C = G->neighbor(n->v);
    C.push_back(n->v);

    for (auto m : C) {
      g = n->g + 1;
      key = getKey(g, m);
      if (CLOSE.find(key) != CLOSE.end()) continue;

      // check constraints
      auto constraint = std::find_if(constraints.begin(), constraints.end(),
                                     [a, g, m, n] (Conflict* c) {
                                       if (c->a != a) return false;
                                       if (c->t != g) return false;
                                       if (c->onNode) return c->v == m;
                                       return c->v == m && c->u == n->v;
                                     });
      if (constraint != constraints.end()) continue;
      f = g + pathDist(m, _g);

      // ==== fast implementation ====
      if (!dPath.empty() && g <= dPath.size() - 1 && m == dPath[g]) {
        f = dPath.size() - 1;
      }
      // if (existGoalConstraint) {
      //   f = pathDist(m, _g) + timeGoalConstraint;
      // }
      // =============================

      auto itrS = SEARCHED.find(key);
      if (itrS == SEARCHED.end()) {  // new node
        AN* l = new AN { m, g, f, n };
        auto handle = OPEN.push(Fib_AN(l));
        SEARCHED.emplace(key, handle);
      } else {
        auto handle = itrS->second;
        AN* l = (*handle).node;
        if (l->f > f) {
          l->g = g;
          l->f = f;
          l->p = n;
        }
        OPEN.increase(handle);
      }
    }
  }

  // back tracking
  if (!invalid) {  // check failed or not
    while (n != nullptr) {
      path.push_back(n->v);
      n = n->p;
    }
    std::reverse(path.begin(), path.end());
  } else {
    node->valid = false;
  }
  knownPaths.emplace(cKey, path);

  return path;
}

Constraint CBS::getConstraints(CTNode* ctNode) {
  Constraint constraints = {};
  CTNode* p = ctNode;
  while (p != nullptr) {
    for (auto c : p->c) constraints.push_back(c);
    p = p->p;
  }
  return constraints;
}

Constraint CBS::getConstraintsForAgent(CTNode* ctNode, Agent* a) {
  Constraint constraints = {};
  CTNode* p = ctNode;
  while (p != nullptr) {
    for (auto c : p->c) {
      if (c->a == a) constraints.push_back(c);
    }
    p = p->p;
  }
  return constraints;
}

bool CBS::isDuplicatedConflict(Constraint &constraint, Conflict* c) {
  auto itr = std::find_if(constraint.begin(), constraint.end(),
                          [c] (Conflict* d)
                          { if (c->onNode != d->onNode) return false;
                            if (c->a != d->a) return false;
                            if (c->onNode && d->onNode) {
                              return c->t == d->t && c->v == d->v;
                            }
                            return c->t == d->t
                                && c->v == d->v
                                && c->u == d->u;
                          });
  return itr != constraint.end();
}

bool CBS::isDuplicatedConflict(Conflict* c1, Conflict* c2) {
  if (c1->a != c2->a) return false;
  if (c1->t != c2->t) return false;
  if (c1->v != c2->v) return false;
  if (c1->onNode != c2->onNode) return false;
  if (!c1->onNode && c1->u != c2->u) return false;
  return true;
}

bool CBS::isDuplicatedCTNode(CTNode* newCT, std::vector<CTNode*> &cts) {
  Constraint newC = getConstraints(newCT);
  std::sort(newC.begin(), newC.end(), [] (Conflict* c1, Conflict* c2)
                                      { if (c1->t != c2->t) return c1->t < c2->t;
                                        if (c1->a != c2->a) return c1->a->getId() < c2->a->getId();
                                        if (c1->onNode != c2->onNode) return c1->onNode;
                                        if (c1->v != c2->v) return c1->v->getId() < c2->v->getId();
                                        if (c1->u != c2->u) return c1->u->getId() < c2->u->getId();
                                        return true;
                                      });
  bool duplicated;
  Constraint oldC;
  for (auto ct : cts) {
    oldC = getConstraints(ct);
    if (newC.size() != oldC.size()) continue;
    std::sort(oldC.begin(), oldC.end(), [] (Conflict* c1, Conflict* c2)
                                        { if (c1->t != c2->t) return c1->t < c2->t;
                                          if (c1->a != c2->a) return c1->a->getId() < c2->a->getId();
                                          if (c1->onNode != c2->onNode) return c1->onNode;
                                          if (c1->v != c2->v) return c1->v->getId() < c2->v->getId();
                                          if (c1->u != c2->u) return c1->u->getId() < c2->u->getId();
                                          return true;
                                        });
    duplicated = true;
    for (int i = 0; i < newC.size(); ++i) {
      if (!isDuplicatedConflict(newC[i], oldC[i])) {
        duplicated = false;
        break;
      }
    }
    if (duplicated) return true;
  }
  return false;
}

bool CBS::validShorcut(Agent* a, AN* n, Node* _g,
                       Constraint &constraints,
                       Nodes &tmpPath) {
  auto itrC = std::find_if(constraints.begin(), constraints.end(),
                           [a, n, _g, &tmpPath] (Conflict* c) {
                             if (c->a != a) return false;
                             if (c->t < n->g) return false;
                             if (c->onNode) {
                               if (c->t > tmpPath.size() + n->g - 1) {
                                 if (c->v == _g) return true;
                               } else {
                                 if (c->v == tmpPath[c->t - n->g]) return true;
                               }
                             } else {
                               if (c->t <= 0
                                   || c->t > tmpPath.size() + n->g) return false;
                               if (c->v == tmpPath[c->t - n->g]
                                   && c->u == tmpPath[c->t - n->g - 1])
                                 return true;
                             }
                             return false;
                           });
  return itrC == constraints.end();
}

std::string CBS::getCKey(Node* s, Node* g, Constraint &constraints) {
  std::string key = std::to_string(s->getId()) + "-" + std::to_string(g->getId());
  for (auto c : constraints) {
    key += "-" + c->key;
  }
  return key;
}

void CBS::setCKey(Conflict* c, int a1, int a2) {
  std::string key = std::to_string(a1) + "_" + std::to_string(a2) + "_" + std::to_string(c->v->getId());
  c->key = key;
}

std::string CBS::logStr() {
  std::string str;
  str += "[solver] type:CBS\n";
  str += "[solver] ID:" + std::to_string(ID) + "\n";
  str += Solver::logStr();
  return str;
}
