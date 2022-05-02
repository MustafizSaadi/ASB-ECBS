#include "dummy.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>

#include "util/param.h"
#include "util/util.h"
#include "graph/simplegrid.h"
#include "graph/pd.h"
#include "graph/station.h"

#include "agent/agent.h"
#include "task/task.h"
#include "problem/mapf.h"
#include "problem/mapd.h"
#include "problem/imapf.h"
#include "problem/imapf_fair.h"

#include "solver/pibt.h"
#include "solver/winpibt.h"
#include "solver/cbs.h"
#include "solver/ecbs.h"
#include "solver/iecbs.h"
#include "solver/whca.h"
#include "solver/hca.h"
#include "solver/tp.h"
#include "solver/pps.h"
#include "solver/sasb_ecbs.h"
#include "solver/dasb_ecbs.h"
#include "solver/BCBS_1_w.h"
#include "solver/BCBS_w_1.h"

static void setCurrentTime(std::string &str);  // for log filename

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}


Problem* run(int argc, char *argv[])
{
  std::string configfile;


#ifdef OF
  std::cout << "reading params" << "\n";
#endif

  /************************
   * set args
   ************************/
  int opt = 0;
  std::string arg;
  opterr = 0;  // ignore getopt error
  while ((opt = getopt(argc, argv, "p:")) != -1) {
    arg = std::string(optarg);
    switch (opt) {
    case 'p':  // config
      configfile = arg;
      break;
    default:
      break;
    }
  }

  /************************
   * default setting
   ************************/
  Param::EnvConfig* envConfig = new Param::EnvConfig
    {
     Param::P_MAPF,    // problem type
     Param::S_PIBT,    // solver type
     "log",            // log_folder
     "./map/5x5.map",  // field type
     3,                // agent number
     10000,            // timesteplimit
     100,              // timelimit
     10,               // task number
     0.1,              // task frequency
     false,            // scenario
     "",               // scenario file
     0,                // seed
     false,            // save log
     true,             // print log
     false,            // print time
    };
  Param::SolverConfig* solverConfig = new Param::SolverConfig
    {
     false,  // WarshallFloyd
     true,   // CBS, ECBS, iECBS, independet operater
     5,      // WHCA* or winPIBT, window size
     1.5,    // ECBS or iECBS, suboptimal param
     true,   // winPIBT, softmode
    };
  Param::VisualConfig* visualConfig = new Param::VisualConfig
    {
     false,                  // showicon
     "./material/sheep.png"  // icon
    };

  /************************
   * load setting
   ************************/
  setParams(configfile, envConfig, solverConfig, visualConfig);

//#ifdef OF
//#endif


  /************************
   * set seed
   ************************/
  // seed for problem and graph
  std::mt19937* MT_PG = new std::mt19937(envConfig->seed);
  // seed for solver
  std::mt19937* MT_S = new std::mt19937(envConfig->seed);

  /************************
   * graph definition
   ************************/
  Graph* G = nullptr;
  if (envConfig->PTYPE == Param::PROBLEM_TYPE::P_MAPF ||
      envConfig->PTYPE == Param::PROBLEM_TYPE::P_IMAPF ||
      envConfig->PTYPE == Param::PROBLEM_TYPE::P_IMAPF_FAIR) {
    G = new SimpleGrid(envConfig->field, MT_PG);
  } else if (envConfig->PTYPE == Param::PROBLEM_TYPE::P_MAPD) {
    G = new PD(envConfig->field, MT_PG);
  } else if (envConfig->PTYPE == Param::PROBLEM_TYPE::P_MAPF_STATION ||
             envConfig->PTYPE == Param::PROBLEM_TYPE::P_IMAPF_STATION) {
    G = new Station(envConfig->field, MT_PG);
  } else {
    std::cout << "error@run, problem is not defined" << "\n";
    std::exit(1);
  }

  /************************
   * agent definition
   ************************/
  Agents A;
  Paths points;
  if (envConfig->scenario) {
#ifdef OF
    std::cout << "use scenario : " << envConfig->scenariofile << "\n";
#endif
    setScenario(envConfig->scenariofile, points, G);
  } else {
    points = G->getRandomStartGoal(envConfig->agentnum);
  }
  
  for (int i = 0; i < envConfig->agentnum; ++i) {
    Agent* a = new Agent(points[i][0]);
    A.push_back(a);
  }


  Problem* P = nullptr;
  if (envConfig->PTYPE == Param::PROBLEM_TYPE::P_MAPF ||
      envConfig->PTYPE == Param::PROBLEM_TYPE::P_MAPF_STATION) {
    std::vector<Task*> T;
    for (int i = 0; i < envConfig->agentnum; ++i) {
      Task* tau = new Task(points[i][1]);
      T.push_back(tau);
    }
    P = new MAPF(G, A, T, MT_PG, envConfig->field, envConfig->timelimit);
  } else if (envConfig->PTYPE == Param::PROBLEM_TYPE::P_MAPD) {
    P = new MAPD(G, A, G->getPickup(), G->getDelivery(),
                 envConfig->tasknum, envConfig->taskfrequency, MT_PG);
  } else if (envConfig->PTYPE == Param::PROBLEM_TYPE::P_IMAPF ||
             envConfig->PTYPE == Param::PROBLEM_TYPE::P_IMAPF_STATION) {
    P = new IMAPF(G, A, envConfig->tasknum, MT_PG);
  } else if (envConfig->PTYPE == Param::PROBLEM_TYPE::P_IMAPF_FAIR) {
    P = new IMAPF_FAIR(G, A, envConfig->tasknum, MT_PG);
  } else {
    std::cout << "error@run, problem is not defined" << "\n";
    std::exit(1);
  }
  // set timestep limit
  P->setTimestepLimit(envConfig->timesteplimit);

  /************************
   * solver definition
   ************************/
  Solver* solver = nullptr;
  switch (envConfig->STYPE) {
  case Param::SOLVER_TYPE::S_CBS:
    if (envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF &&
        envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF_STATION) {
      std::cout << "error@run, CBS cannot solve except MAPF" << "\n";
      std::exit(1);
    }
    solver = new CBS(P, solverConfig->ID);
    break;
  case Param::SOLVER_TYPE::S_ECBS:
    if (envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF &&
        envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF_STATION) {
      std::cout << "error@run, ECBS cannot solve except MAPF" << "\n";
      std::exit(1);
    }
    solver = new ECBS(P, solverConfig->suboptimal, solverConfig->ID);
    break;
  case Param::SOLVER_TYPE::S_SASB_ECBS:
    if (envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF &&
        envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF_STATION) {
      std::cout << "error@run, ECBS cannot solve except MAPF" << "\n";
      std::exit(1);
    }
    solver = new SASB_ECBS(P, solverConfig->suboptimal, solverConfig->ID);
    break;
  case Param::SOLVER_TYPE::S_DASB_ECBS:
    if (envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF &&
        envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF_STATION) {
      std::cout << "error@run, ECBS cannot solve except MAPF" << "\n";
      std::exit(1);
    }
    solver = new DASB_ECBS(P, solverConfig->suboptimal, solverConfig->ID);
    break;
  case Param::SOLVER_TYPE::S_BCBS_1_W:
    if (envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF &&
        envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF_STATION) {
      std::cout << "error@run, ECBS cannot solve except MAPF" << "\n";
      std::exit(1);
    }
    solver = new BCBS_1_w(P, solverConfig->suboptimal, solverConfig->ID);
    break;
  case Param::SOLVER_TYPE::S_BCBS_W_1:
    if (envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF &&
        envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF_STATION) {
      std::cout << "error@run, ECBS cannot solve except MAPF" << "\n";
      std::exit(1);
    }
    solver = new BCBS_w_1(P, solverConfig->suboptimal, solverConfig->ID);
    break;
  case Param::SOLVER_TYPE::S_iECBS:
    if (envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF &&
        envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF_STATION) {
      std::cout << "error@run, iECBS cannot solve except MAPF" << "\n";
      std::exit(1);
    }
    solver = new iECBS(P, solverConfig->suboptimal, solverConfig->ID);
    break;
  case Param::SOLVER_TYPE::S_WHCA:
    if (envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF &&
        envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF_STATION) {
      std::cout << "error@run, WHCA cannot solve except MAPF" << "\n";
      std::exit(1);
    }
    solver = new WHCA(P, solverConfig->window);
    break;
  case Param::SOLVER_TYPE::S_HCA:
    if (envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF &&
        envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF_STATION) {
      std::cout << "error@run, HCA cannot solve except MAPF" << "\n";
      std::exit(1);
    }
    solver = new HCA(P);
    break;
  case Param::SOLVER_TYPE::S_PPS:
    if (envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF &&
        envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPF_STATION) {
      std::cout << "error@run, PPS cannot solve except MAPF" << "\n";
      std::exit(1);
    }
    solver = new PPS(P);
    break;
  case Param::SOLVER_TYPE::S_PIBT:
    solver = new PIBT(P, MT_S);
    break;
  case Param::SOLVER_TYPE::S_winPIBT:
    solver = new winPIBT(P, solverConfig->window,
                         solverConfig->softmode, MT_S);
    break;
  case Param::SOLVER_TYPE::S_TP:
    if (envConfig->PTYPE != Param::PROBLEM_TYPE::P_MAPD) {
      std::cout << "error@run, TP cannot solve except MAPD" << "\n";
      std::exit(1);
    }
    solver = new TP(P, G->getAllSpecialPoints());
    break;
  default:
    std::cout << "error@run, solver is not defined" << "\n";
    std::exit(1);
    break;
  }

  // precomputing distances
  if (solverConfig->WarshallFloyd) {
#ifdef OF
    std::cout << "start WarshallFloyd, "
              << "it requires O(" << G->getNodesNum() << "^3) cost\n";
#endif
    // std:: cout << "Floyd " << envConfig->field<< std::endl;
    // int st = envConfig->field.find("8");
    // int en = envConfig->field.find(".map");
    // input_file = envConfig->field.substr(st,en-st);
    // std::cout << input_file <<std::endl;
    solver->WarshallFloyd(envConfig->field);

#ifdef OF
    std::cout << "done." << "\n";
#endif
  }

  /************************
   * start solving
   ************************/
#ifdef OF
  std::cout << "done." << "\n";
  std::cout << "start solving the iterative MAPF problem" << "\n";
#endif
  
  //ofstream myfile;
  uint64_t current_time1 = timeSinceEpochMillisec();

  solver->solve();
  

  uint64_t current_time2 = timeSinceEpochMillisec();

  // myfile.open("output_high_level_node.txt",ios_base::app);
  // myfile<<solver->highLevelNode<<endl;
  // myfile.close();

#ifdef OF
  std::cout << "success to solve!" << "\n\n";
#endif

  /************************
   * summarize results
   ************************/
  std::string result = "[setting] seed:" + std::to_string(envConfig->seed) + "\n";
  if (envConfig->scenario) {
    result += "[setting] scenario: " + envConfig->scenariofile + "\n";
  }
  result += solver->logStr();
  if (envConfig->log) {
    std::string outfile;
    std::ofstream log;
    setCurrentTime(outfile);
    
    struct stat sb;

    if (!(stat(envConfig->log_folder.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))) {
        mkdir(envConfig->log_folder.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
    } 

    outfile = "./" + envConfig->log_folder + "/" + outfile + ".txt";
    log.open(outfile, std::ios::out);
    if (!log) {
      std::cout << "error@run, cannot open log file "
                << outfile << "\n";
      std::exit(1);
    }
    log << result;
    log.close();
  }

  if (envConfig->printlog) {
    std::cout << result << "\n";
  } else if (envConfig->printtime) {
    std::cout << "Map Name:" << envConfig->field << std::endl;
    std::cout << "Solution Cost:" << P->cost << std::endl;
    std::cout << "Makespan:" << P->getTerminationTime() << std::endl;
    std::cout << "[solver] elapsed:" << solver->getElapsed() << "\n\n";
    
  }


  // for visualization
  P->visual_showicon = visualConfig->showicon;
  P->visual_icon = visualConfig->icon;

  return P;
}

// for log file name
static void setCurrentTime(std::string &str) {
  char buff[27] = "";
  time_t now = time(NULL);
  timeval curTime;
  gettimeofday(&curTime, NULL);
  struct tm* pnow = localtime(&now);
  sprintf(buff, "%04d-%02d-%02d-%02d-%02d-%02d-%06d",
          pnow->tm_year + 1900, pnow->tm_mon + 1,
          pnow->tm_mday, pnow->tm_hour, pnow->tm_min, pnow->tm_sec,
          curTime.tv_usec);
  str = std::string(buff);
}
