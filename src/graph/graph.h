#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <unordered_map>
#include "node.h"

using Nodes = std::vector<Node*>;
using Paths = std::vector<Nodes>;

struct KnownPath {
  Node* s;
  Node* g;
  Nodes path;
};

struct AN {  // Astar Node
  Node* v;
  int g;
  int f;
  AN* p;
};

struct Fib_AN { // AN for Fibonacci heap
  Fib_AN(AN* _node): node(_node) {}
  AN* node;
  // a has less priority than b if a < b
  bool operator<(const Fib_AN& other) const {
    if (node->f != other.node->f) {
      return node->f > other.node->f;
    } else {
      return node->g < other.node->g;
    }
  }
};

class Graph {
private:
  // digraph or not
  bool directed;

  // register path or not
  bool regFlg;

protected:
  // nodes
  Nodes nodes;

  // cache of searched path
  std::unordered_map<std::string, KnownPath*> knownPaths;
  // search through id
  std::unordered_map< int, Node*> node_id_table;

  // random generator
  std::mt19937* MT;

  // start and goals
  Nodes starts;
  Nodes goals;

  void init();
  Nodes getPath(Node* s, Node* g, int (*dist)(Node*, Node*));
  Nodes getPath(Node* s, Node* g, Nodes &prohibitedNodes,
                int (*dist)(Node*, Node*));
  void registerPath(const Nodes &path);

public:
  Graph();
  Graph(std::mt19937* _MT);
  ~Graph();

  Node* getNode(int id);
  bool existNode(int id);
  Node* getNode(int x, int y);
  Nodes getNodes() { return nodes; }
  int getNodesNum() { return nodes.size(); }
  int getNodeIndex(Node* v);
  Node* getNodeFromIndex(int i) { return nodes[i]; }
  virtual std::string getKey(Node* s, Node* g);

  Nodes neighbor(Node* v);
  Nodes neighbor(int id);

  // implemented in Grid class
  virtual int getW() { return 0; };
  virtual int getH() { return 0; };

  // for Digraph
  void setDirected(bool _directed) { directed = _directed; }
  bool isDirected() { return directed; }

  // register path or not
  void setRegFlg(bool flg) { regFlg = flg; }

  // typical exampl: manhattan distance
  virtual int dist(Node* v1, Node* v2) { return 0; }
  virtual Nodes getPath(Node* s, Node* g) { return {}; }
  virtual Nodes getPath(Node* s, Node* g, Nodes &prohibitedNodes);
  //virtual Nodes getPathcnt(Node* s, Node* g, int* cnt2);
  virtual bool getPathInit(Node* s, Node* g);

  virtual Paths getRandomStartGoal(int num);
  // for iterative MAPF
  virtual Node* getNewGoal(Node* v) { return v; }

  // for pickup and delivery
  virtual Nodes getPickup() { return {}; }
  virtual Nodes getDelivery() { return {}; }
  virtual Nodes getEndpoints() { return {}; }
  virtual Nodes getAllSpecialPoints() { return {}; }

  // for iECBS
  virtual std::string getMapName() { return ""; }

  virtual std::string logStr() { return ""; };
};
