/*
 * testapp.cpp
 *
 * Purpose:
 * Created by: Keisuke Okumura <okumura.k@coord.c.titech.ac.jp>
 */

#include "dummy.h"
#include <chrono>
#include <cstdint>
#include<bits/stdc++.h>
using namespace std;
#ifndef OF

#include "app.h"

// uint64_t timeSinceEpochMillisec() {
//   using namespace std::chrono;
//   return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
// }

int main(int argc, char *argv[])
{
  //time_t current_time1,current_time2;
  //ofstream myfile;
  uint64_t current_time1 = timeSinceEpochMillisec();
  run(argc, argv);
  uint64_t current_time2 = timeSinceEpochMillisec();
  //myfile.open("output_runtime.txt",ios_base::app);
  //myfile<<current_time2-current_time1<<endl;
  //myfile.close();
  std:: cout<<current_time2-current_time1<<std::endl;
	

  return 0;
}

#endif
