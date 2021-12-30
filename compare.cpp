#include<bits/stdc++.h>
using namespace std;

bool exists_test0 (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

vector < double > vec[4];

double calculateMEAN(int i){
    double mean = 0;
    for(int j=0;j<vec[i].size();j++){
            mean += vec[i][j];
        }
    return mean/vec[i].size();
}

double calculateSD(int i,double mean)
{
    double standardDeviation = 0.0;
        for(int j=0;j<vec[i].size();j++){
            standardDeviation += pow(vec[i][j] - mean, 2);
        }
    return sqrt(standardDeviation / vec[i].size());
}


int main(){
    int ans;
    //bool success = false, completeness = false, percentage = false, performance = false;
    cout << "For success input 1" << endl ;
    cout << "For completeness input 2" << endl ;
    cout << "For percentage_weight input 3" << endl;
    cout << "For percentage_agent input 4" << endl;
    cout << "For percentage_weight_agent input 5" << endl;
    cout << "For performance_weight input 6" <<endl;
    cout << "For performance_agent input 7" <<endl;
    cout << "For performance_weight_agent input 8" <<endl;
    cout << "For conflict_count comparison input 9" <<endl;
    cout << "For find agent and weight input 10" <<endl;
    cin >> ans;
    double cnt1=0,cnt2=0,cnt3=0,cnt4=0,cnt5=0,cnt6=0;
    double solncnt[6],runtimecnt[6],lowlevelcnt[6],solncost[6],solnruntime[6],solnlowlevel[6];
    int conflict_cnt[6], row = 0, col = 0, r, c;
    double j = 1.250000000;
    int agent = 10, a = 10, cnt = 0, ex = 0, runtime_limit = 240000;
    bool flag = false;
    string file = "orz601d_";
    ofstream outfile;
    string write = "";
    switch (ans)
    {
    case 1:
        // for succsess and completeness
        a = 50;
        while(a<=80){
            j = 2.05;
            while(j<=3){
                ex = 0;
                cnt1=0,cnt2=0,cnt3=0,cnt4=0,cnt5=-1,cnt6=0;
                while(ex<100){
                cnt4 ++;
                // string string1 = "/home/mustafizur/pibt/log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                // string string2 = "/home/mustafizur/pibt/changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                // string string3 = "/home/mustafizur/pibt/changed_changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                
                string string1 = "/home/mustafizur/pibt/ecbs_kivalike_50_80_2.05_3/"+ file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                string string2 = "/home/mustafizur/pibt/swa_kivalike_50_80_2.05_3/" + file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                string string3 = "/home/mustafizur/pibt/dwa_kivalike_50_80_2.05_3/"+ file  + to_string(ex) + "_" +  to_string(a)+ "_" + to_string(j) + ".txt";

                //string string1 = "/home/mustafizur/pibt/bcbs_w_log/"+ file + to_string(ex) + "_0_" + to_string(a)+ "_" + to_string(j) + ".txt";
                bool flag1 = false, flag2 = false,flag3=false;
                //cout<< string1 << endl;
                if(exists_test0(string1)){
                    flag1 = true;
                    cnt1 ++;
                }
                if(exists_test0(string2)){
                    flag2 = true;
                    cnt2 ++;
                }
                if(exists_test0(string3)){
                    flag3 = true;
                    cnt3 ++;
                }
                // if(flag1 && flag2 && flag3){
                //     cnt5 ++;
                // }
                // if(cnt5 == 44 && cnt == 0){
                //     cout << a << " " << j << " " << ex << endl;
                //     cnt5 ++;
                // }
                // if(exists_test0(string4)){
                //     flag3 = true;
                //     cnt4 ++;
                // }
                ex += 1;
                }
                cout<< a <<" "<< j << " " << cnt1/cnt4 << " " << cnt2/cnt4 << " " << cnt3/cnt4  << " " <<endl;

                //cout<< a <<" "<< j << " " << cnt1/cnt4 << endl;

            cnt ++;
            j += 0.05;

            }
            // cout<< a <<" "<< cnt1/cnt4 << " " << cnt2/cnt4 << " " << cnt3/cnt4  << " " <<endl;
            //j += 0.2;
            a += 10;
       }
        //cout<< cnt1/cnt4 << " " << cnt2/cnt4 << " " << cnt3/cnt4 << " " << cnt4 <<endl;

        break;
    
    case 2:
        // for succsess and completeness
        //while(j<6){
            a = 10;
            while(a<=200){
                //int ex = 0;
                while(ex<100){

                // string string1 = "/home/mustafizur/pibt/log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                // string string2 = "/home/mustafizur/pibt/changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                // string string3 = "/home/mustafizur/pibt/changed_changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                
                string string1 = "/home/mustafizur/pibt/log/" + file + to_string(ex) + "_" +  to_string(a)+ "_" + to_string(j) + ".txt";
                string string2 = "/home/mustafizur/pibt/changed_log/" + file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                string string3 = "/home/mustafizur/pibt/changed_changed_log/" + file + to_string(ex) + "_" +  to_string(a)+ "_" + to_string(j) + ".txt";


                bool flag1 = false, flag2 = false,flag3=false;
                if(exists_test0(string1)){
                    flag1 = true;
                    //cout<< string1 << endl;
                }
                if(exists_test0(string2)){
                    flag2 = true;
                }
                if(exists_test0(string3)){
                    flag3 = true;
                }

                if(flag1 && !flag3){
                    cnt1 ++;
                    cout<<string1<<endl;
                    //remove(string1.c_str());
                }
                else if(!flag1 && flag3){
                    cnt3 ++;
                    cout<<string3<<endl;
                    //remove(string3.c_str());
                }

                if(flag1 && !flag2){
                    cnt5 ++;
                    cout<<string1<<endl;
                    //remove(string1.c_str());
                }
                else if(!flag1 && flag2){
                    cnt6 ++;
                    cout<<string2<<endl;
                    //remove(string3.c_str());
                }

                if(flag2 && !flag3){
                    cnt2 ++;
                    cout<<string2<<endl;
                    //remove(string2.c_str());
                }
                else if(!flag2 && flag3){
                    cnt4 ++;
                    cout<<string3<<endl;
                    //remove(string3.c_str());
                }
                ex += 1;
                }
                a += 10;
            // }
            // j += 1;
        } 

        cout << cnt1 << " problems which were solved by ECBS were not solved by ECBS-changed_2." <<endl; 
        cout << cnt3 << " problems which were solved by ECBS-changed_2 were not solved by ECBS." << endl;
        cout << cnt2 << " problems which were solved by ECBS-changed were not solved by ECBS-changed_2." << endl;
        cout << cnt4 << " problems which were solved by ECBS-changed_2 were not solved by ECBS-changed." << endl;      
        cout << cnt5 << " problems which were solved by ECBS were not solved by ECBS-changed." <<endl; 
        cout << cnt6 << " problems which were solved by ECBS-changed were not solved by ECBS." << endl; 


        break;

    case 3:
        j = 3.000000000;
        //while(j<6){ 
            a = 10;
            cnt = 0;
                for (size_t i = 0; i < 6; i++)
                {
                    solncnt[i]=0,runtimecnt[i]=0,lowlevelcnt[i]=0,solncost[i]=0,solnruntime[i]=0,solnlowlevel[i]=0;
                } 
            while(a<=150){
                // int agent = 10;  
                // //while(agent<4){
                int ex = 0;
                while(ex<100){
                        // string string1 = "/home/mustafizur/pibt/log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string2 = "/home/mustafizur/pibt/changed_log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string3 = "/home/mustafizur/pibt/changed_changed_log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        
                        // string string1 = "/home/mustafizur/pibt/log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string2 = "/home/mustafizur/pibt/changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string3 = "/home/mustafizur/pibt/changed_changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
    


                        string string1 = "/home/mustafizur/pibt/ecbs_log_32by32_10_150_1.5/"+ file + to_string(ex) + "_0_" + to_string(a)+ "_" + to_string(1.5) + ".txt";
                        string string2 = "/home/mustafizur/pibt/swa_ecbs_log_32by32_10_150_2/" + file + to_string(ex) + "_0_" + to_string(a)+ "_" + to_string(2.0) + ".txt";
                        string string3 = "/home/mustafizur/pibt/dwa_ecbs_log_32by32_10_150_2/"+ file  + to_string(ex) + "_0_" +  to_string(a)+ "_" + to_string(2.0) + ".txt";
                        
                        bool flag1 = false, flag2 = false,flag3=false;
                        if(exists_test0(string1)){
                            flag1 = true;
                        }
                        if(exists_test0(string2)){
                            flag2 = true;
                        }
                        if(exists_test0(string3)){
                            flag3 = true;
                        }
                        if(flag1 && flag2 && flag3){
                            cnt++;
                            ifstream in1(string1);
                            ifstream in2(string2);
                            ifstream in3(string3);
                            string data;
                            while(getline(in1,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[0] = atoi(intermediate.c_str());   
                                    //cout << lowlevelcnt[0] <<endl;
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[0] = atoi(intermediate.c_str());   
                                    //cout << runtimecnt[0] <<endl;
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[0] = atoi(intermediate.c_str());
                                    //cout << solncnt[0] <<endl;
                                }
                            }
                        
                            while(getline(in2,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[1] = atoi(intermediate.c_str());  
                                    //cout << lowlevelcnt[1] <<endl; 
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[1] = atoi(intermediate.c_str());   
                                    //cout << runtimecnt[1] <<endl;
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[1] = atoi(intermediate.c_str());
                                    //cout << solncnt[1] <<endl;
                                }
                            }

                            while(getline(in3,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[2] = atoi(intermediate.c_str()); 
                                    //cout << lowlevelcnt[2] <<endl;  
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[2] = atoi(intermediate.c_str());   
                                    //cout<< runtimecnt[2] <<endl;
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[2] = atoi(intermediate.c_str());
                                    //cout << solncnt[2]<<endl;
                                }
                            }


                            if(lowlevelcnt[0]>lowlevelcnt[2])
                                solnlowlevel[4] ++; // ecbs_2 better than ecbs
                            else if(lowlevelcnt[0]<lowlevelcnt[2])
                                solnlowlevel[0] ++; // ecbs better than ecbs_2

                            
                            if(lowlevelcnt[1]>lowlevelcnt[2])
                                solnlowlevel[5] ++; // ecbs_2 better than ecbs_1
                            else if(lowlevelcnt[1]<lowlevelcnt[2])
                                solnlowlevel[3] ++; // ecbs_1 better than ecbs_2

                            if(lowlevelcnt[0]>lowlevelcnt[1])
                                solnlowlevel[2] ++; // ecbs_1 better than ecbs
                            else if(lowlevelcnt[0]<lowlevelcnt[1])
                                solnlowlevel[1] ++; // ecbs better than ecbs_1

                    
                            if(runtimecnt[0]>runtimecnt[2])
                                solnruntime[4] ++; // ecbs_2 better than ecbs
                            else if(runtimecnt[0]<runtimecnt[2])
                                solnruntime[0] ++; // ecbs better than ecbs_2

                            
                            if(runtimecnt[1]>runtimecnt[2])
                                solnruntime[5] ++; // ecbs_2 better than ecbs_1
                            else if(runtimecnt[1]<runtimecnt[2])
                                solnruntime[3] ++; // ecbs_1 better than ecbs_2

                            if(runtimecnt[0]>runtimecnt[1])
                                solnruntime[2] ++; // ecbs_1 better than ecbs
                            else if(runtimecnt[0]<runtimecnt[1])
                                solnruntime[1] ++; // ecbs better than ecbs_1

                        
                            if(solncnt[0]>solncnt[2])
                                solncost[4] ++; // ecbs_2 better than ecbs
                            else if(solncnt[0]<solncnt[2])
                                solncost[0] ++; // ecbs better than ecbs_2

                            
                            if(solncnt[1]>solncnt[2])
                                solncost[5] ++; // ecbs_2 better than ecbs_1
                            else if(solncnt[1]<solncnt[2])
                                solncost[3] ++; // ecbs_1 better than ecbs_2

                            if(solncnt[0]>solncnt[1])
                                solncost[2] ++; // ecbs_1 better than ecbs
                            else if(solncnt[0]<solncnt[1])
                                solncost[1] ++; // ecbs better than ecbs_1

                        }
                        ex += 1;

                        }
                    // agent += 1;
                    // }

                a += 10;
                }

            cout<< "weight = " << j <<" instances = "  <<  cnt<<endl;  
            cout << "ecbs > ecbs2   ecbs > ecbs1    ecbs1 > ecbs   ecbs1 > ecbs2    ecbs2 > ecbs    ecbs2 > ecbs1" << endl;   
            cout<<"LowLevel: "<<endl;
            for (size_t i = 0; i < 6; i++)
            {
                cout << (solnlowlevel[i]/cnt)*100<< " ";
            }
            cout<<endl<<"runitme: "<<endl;
            for (size_t i = 0; i < 6; i++)
            {
                cout << (solnruntime[i]/cnt)*100<< " ";
            }
            cout<<endl<<"Cost: "<<endl;
            for (size_t i = 0; i < 6; i++)
            {
                cout << (solncost[i]/cnt)*100<< " ";
            }
            cout << endl;
        //     j += 1;
        // }


        break;

    case 4:
        a = 10;
        while(a<=200){
            double j = 3.000000000;
            cnt = 0;
                for (size_t i = 0; i < 6; i++)
                {
                    solncnt[i]=0,runtimecnt[i]=0,lowlevelcnt[i]=0,solncost[i]=0,solnruntime[i]=0,solnlowlevel[i]=0;
                } 
            //while(j<6){
                // int agent = 10;  
                // //while(agent<4){
                    //int ex = 0;
                    while(ex<100){
                        // string string1 = "/home/mustafizur/pibt/log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string2 = "/home/mustafizur/pibt/changed_log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string3 = "/home/mustafizur/pibt/changed_changed_log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        
                        // string string1 = "/home/mustafizur/pibt/log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string2 = "/home/mustafizur/pibt/changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string3 = "/home/mustafizur/pibt/changed_changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
    


                        string string1 = "/home/mustafizur/pibt/log/"+ file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        string string2 = "/home/mustafizur/pibt/changed_log/"+ file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        string string3 = "/home/mustafizur/pibt/changed_changed_log/"+ file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";

                        bool flag1 = false, flag2 = false,flag3=false;
                        if(exists_test0(string1)){
                            flag1 = true;
                        }
                        if(exists_test0(string2)){
                            flag2 = true;
                        }
                        if(exists_test0(string3)){
                            flag3 = true;
                        }
                        if(flag1 && flag2 && flag3){
                            cnt++;
                            ifstream in1(string1);
                            ifstream in2(string2);
                            ifstream in3(string3);
                            string data;
                            while(getline(in1,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[0] = atoi(intermediate.c_str());   
                                    //cout << lowlevelcnt[0] <<endl;
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[0] = atoi(intermediate.c_str());   
                                    //cout << runtimecnt[0] <<endl;
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[0] = atoi(intermediate.c_str());
                                    //cout << solncnt[0] <<endl;
                                }
                            }
                        
                            while(getline(in2,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[1] = atoi(intermediate.c_str());  
                                    //cout << lowlevelcnt[1] <<endl; 
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[1] = atoi(intermediate.c_str());   
                                    //cout << runtimecnt[1] <<endl;
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[1] = atoi(intermediate.c_str());
                                    //cout << solncnt[1] <<endl;
                                }
                            }

                            while(getline(in3,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[2] = atoi(intermediate.c_str()); 
                                    //cout << lowlevelcnt[2] <<endl;  
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[2] = atoi(intermediate.c_str());   
                                    //cout<< runtimecnt[2] <<endl;
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[2] = atoi(intermediate.c_str());
                                    //cout << solncnt[2]<<endl;
                                }
                            }


                            if(lowlevelcnt[0]>lowlevelcnt[2])
                                solnlowlevel[4] ++; // ecbs_2 better than ecbs
                            else if(lowlevelcnt[0]<lowlevelcnt[2])
                                solnlowlevel[0] ++; // ecbs better than ecbs_2

                            
                            if(lowlevelcnt[1]>lowlevelcnt[2])
                                solnlowlevel[5] ++; // ecbs_2 better than ecbs_1
                            else if(lowlevelcnt[1]<lowlevelcnt[2])
                                solnlowlevel[3] ++; // ecbs_1 better than ecbs_2

                            if(lowlevelcnt[0]>lowlevelcnt[1])
                                solnlowlevel[2] ++; // ecbs_1 better than ecbs
                            else if(lowlevelcnt[0]<lowlevelcnt[1])
                                solnlowlevel[1] ++; // ecbs better than ecbs_1

                    
                            if(runtimecnt[0]>runtimecnt[2])
                                solnruntime[4] ++; // ecbs_2 better than ecbs
                            else if(runtimecnt[0]<runtimecnt[2])
                                solnruntime[0] ++; // ecbs better than ecbs_2

                            
                            if(runtimecnt[1]>runtimecnt[2])
                                solnruntime[5] ++; // ecbs_2 better than ecbs_1
                            else if(runtimecnt[1]<runtimecnt[2])
                                solnruntime[3] ++; // ecbs_1 better than ecbs_2

                            if(runtimecnt[0]>runtimecnt[1])
                                solnruntime[2] ++; // ecbs_1 better than ecbs
                            else if(runtimecnt[0]<runtimecnt[1])
                                solnruntime[1] ++; // ecbs better than ecbs_1

                        
                            if(solncnt[0]>solncnt[2])
                                solncost[4] ++; // ecbs_2 better than ecbs
                            else if(solncnt[0]<solncnt[2])
                                solncost[0] ++; // ecbs better than ecbs_2

                            
                            if(solncnt[1]>solncnt[2])
                                solncost[5] ++; // ecbs_2 better than ecbs_1
                            else if(solncnt[1]<solncnt[2])
                                solncost[3] ++; // ecbs_1 better than ecbs_2

                            if(solncnt[0]>solncnt[1])
                                solncost[2] ++; // ecbs_1 better than ecbs
                            else if(solncnt[0]<solncnt[1])
                                solncost[1] ++; // ecbs better than ecbs_1

                        }
                        ex += 1;

                        }
                    // agent += 1;
                    // }

                // j += 1;
                // }

            cout<< "agent = " << a <<" instances = "  <<  cnt<<endl;  
            cout << "ecbs > ecbs2   ecbs > ecbs1    ecbs1 > ecbs   ecbs1 > ecbs2    ecbs2 > ecbs    ecbs2 > ecbs1" << endl;   
            cout<<"LowLevel: "<<endl;
            for (size_t i = 0; i < 6; i++)
            {
                cout << (solnlowlevel[i]/cnt)*100<< " ";
            }
            cout<<endl<<"runitme: "<<endl;
            for (size_t i = 0; i < 6; i++)
            {
                cout << (solnruntime[i]/cnt)*100<< " ";
            }
            cout<<endl<<"Cost: "<<endl;
            for (size_t i = 0; i < 6; i++)
            {
                cout << (solncost[i]/cnt)*100<< " ";
            }
            cout << endl;
            a += 10;
        }


        break;

    case 5:
        a = 10;
        while(a<=200){
            double j = 3.000000000;
            //while(j<6){
                for (size_t i = 0; i < 6; i++)
                {
                    solncnt[i]=0,runtimecnt[i]=0,lowlevelcnt[i]=0,solncost[i]=0,solnruntime[i]=0,solnlowlevel[i]=0;
                } 
                cnt = 0;
                // int agent = 10;  
                // //while(agent<4){
                    //int ex = 0;
                    while(ex<100){
                        // string string1 = "/home/mustafizur/pibt/log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string2 = "/home/mustafizur/pibt/changed_log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string3 = "/home/mustafizur/pibt/changed_changed_log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        
                        // string string1 = "/home/mustafizur/pibt/log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string2 = "/home/mustafizur/pibt/changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string3 = "/home/mustafizur/pibt/changed_changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
    


                        string string1 = "/home/mustafizur/pibt/log/" + file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        string string2 = "/home/mustafizur/pibt/changed_log/" + file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        string string3 = "/home/mustafizur/pibt/changed_changed_log/" + file + to_string(ex) + "_" +  to_string(a)+ "_" + to_string(j) + ".txt";

                        bool flag1 = false, flag2 = false,flag3=false;
                        if(exists_test0(string1)){
                            flag1 = true;
                        }
                        if(exists_test0(string2)){
                            flag2 = true;
                        }
                        if(exists_test0(string3)){
                            flag3 = true;
                        }
                        if(flag1 && flag2 && flag3){
                            cnt++;
                            ifstream in1(string1);
                            ifstream in2(string2);
                            ifstream in3(string3);
                            string data;
                            while(getline(in1,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[0] = atoi(intermediate.c_str());   
                                    //cout << lowlevelcnt[0] <<endl;
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[0] = atoi(intermediate.c_str());   
                                    //cout << runtimecnt[0] <<endl;
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[0] = atoi(intermediate.c_str());
                                    //cout << solncnt[0] <<endl;
                                }
                            }
                        
                            while(getline(in2,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[1] = atoi(intermediate.c_str());  
                                    //cout << lowlevelcnt[1] <<endl; 
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[1] = atoi(intermediate.c_str());   
                                    //cout << runtimecnt[1] <<endl;
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[1] = atoi(intermediate.c_str());
                                    //cout << solncnt[1] <<endl;
                                }
                            }

                            while(getline(in3,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[2] = atoi(intermediate.c_str()); 
                                    //cout << lowlevelcnt[2] <<endl;  
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[2] = atoi(intermediate.c_str());   
                                    //cout<< runtimecnt[2] <<endl;
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[2] = atoi(intermediate.c_str());
                                    //cout << solncnt[2]<<endl;
                                }
                            }


                            if(lowlevelcnt[0]>lowlevelcnt[2])
                                solnlowlevel[4] ++; // ecbs_2 better than ecbs
                            else if(lowlevelcnt[0]<lowlevelcnt[2])
                                solnlowlevel[0] ++; // ecbs better than ecbs_2

                            
                            if(lowlevelcnt[1]>lowlevelcnt[2])
                                solnlowlevel[5] ++; // ecbs_2 better than ecbs_1
                            else if(lowlevelcnt[1]<lowlevelcnt[2])
                                solnlowlevel[3] ++; // ecbs_1 better than ecbs_2

                            if(lowlevelcnt[0]>lowlevelcnt[1])
                                solnlowlevel[2] ++; // ecbs_1 better than ecbs
                            else if(lowlevelcnt[0]<lowlevelcnt[1])
                                solnlowlevel[1] ++; // ecbs better than ecbs_1

                    
                            if(runtimecnt[0]>runtimecnt[2])
                                solnruntime[4] ++; // ecbs_2 better than ecbs
                            else if(runtimecnt[0]<runtimecnt[2])
                                solnruntime[0] ++; // ecbs better than ecbs_2

                            
                            if(runtimecnt[1]>runtimecnt[2])
                                solnruntime[5] ++; // ecbs_2 better than ecbs_1
                            else if(runtimecnt[1]<runtimecnt[2])
                                solnruntime[3] ++; // ecbs_1 better than ecbs_2

                            if(runtimecnt[0]>runtimecnt[1])
                                solnruntime[2] ++; // ecbs_1 better than ecbs
                            else if(runtimecnt[0]<runtimecnt[1])
                                solnruntime[1] ++; // ecbs better than ecbs_1

                        
                            if(solncnt[0]>solncnt[2])
                                solncost[4] ++; // ecbs_2 better than ecbs
                            else if(solncnt[0]<solncnt[2])
                                solncost[0] ++; // ecbs better than ecbs_2

                            
                            if(solncnt[1]>solncnt[2])
                                solncost[5] ++; // ecbs_2 better than ecbs_1
                            else if(solncnt[1]<solncnt[2])
                                solncost[3] ++; // ecbs_1 better than ecbs_2

                            if(solncnt[0]>solncnt[1])
                                solncost[2] ++; // ecbs_1 better than ecbs
                            else if(solncnt[0]<solncnt[1])
                                solncost[1] ++; // ecbs better than ecbs_1

                        }
                        ex += 1;

                        }
                    // agent += 1;
                    // }
                    cout<< "agent = " << a << " weight = " << j << " instances = "  <<  cnt<<endl;  
                    cout << "ecbs > ecbs2   ecbs > ecbs1    ecbs1 > ecbs   ecbs1 > ecbs2    ecbs2 > ecbs    ecbs2 > ecbs1" << endl;   
                    cout<<"LowLevel: "<<endl;
                    for (size_t i = 0; i < 6; i++)
                    {
                        cout << (solnlowlevel[i]/cnt)*100<< " ";
                    }
                    cout<<endl<<"runitme: "<<endl;
                    for (size_t i = 0; i < 6; i++)
                    {
                        cout << (solnruntime[i]/cnt)*100<< " ";
                    }
                    cout<<endl<<"Cost: "<<endl;
                    for (size_t i = 0; i < 6; i++)
                    {
                        cout << (solncost[i]/cnt)*100<< " ";
                    }
                    cout << endl;

                // j += 1;
                // }
            a += 10;
        }

        break;

    case 6:

        j = 1.250000000;
        while(j<6){ 
            a = 10;
            cnt = 0;
                for (size_t i = 0; i < 6; i++)
                {
                    solncnt[i]=0,runtimecnt[i]=0,lowlevelcnt[i]=0,solncost[i]=0,solnruntime[i]=0,solnlowlevel[i]=0;
                } 
            while(a<=100){
            //while(j<6){
                // int agent = 10;  
                // //while(agent<4){
                    //int ex = 0;
                    while(ex<100){
                        // string string1 = "/home/mustafizur/pibt/log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string2 = "/home/mustafizur/pibt/changed_log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string3 = "/home/mustafizur/pibt/changed_changed_log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        
                        // string string1 = "/home/mustafizur/pibt/log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string2 = "/home/mustafizur/pibt/changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string3 = "/home/mustafizur/pibt/changed_changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
    


                        string string1 = "/home/mustafizur/pibt/log/"+ file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        string string2 = "/home/mustafizur/pibt/changed_log/"+ file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        string string3 = "/home/mustafizur/pibt/changed_changed_log/"+ file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";

                        bool flag1 = false, flag2 = false,flag3=false;
                        if(exists_test0(string1)){
                            flag1 = true;
                        }
                        if(exists_test0(string2)){
                            flag2 = true;
                        }
                        if(exists_test0(string3)){
                            flag3 = true;
                        }
                        if(flag1 && flag2 && flag3){
                            cnt++;
                            ifstream in1(string1);
                            ifstream in2(string2);
                            ifstream in3(string3);
                            string data;
                            while(getline(in1,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[0] = atoi(intermediate.c_str());   
                                    //cout << lowlevelcnt[0] <<endl;
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[0] = atoi(intermediate.c_str());   
                                    //cout << runtimecnt[0] <<endl;
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[0] = atoi(intermediate.c_str());
                                    //cout << solncnt[0] <<endl;
                                }
                            }
                        
                            while(getline(in2,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[1] = atoi(intermediate.c_str());  
                                    //cout << lowlevelcnt[1] <<endl; 
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[1] = atoi(intermediate.c_str());   
                                    //cout << runtimecnt[1] <<endl;
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[1] = atoi(intermediate.c_str());
                                    //cout << solncnt[1] <<endl;
                                }
                            }

                            while(getline(in3,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[2] = atoi(intermediate.c_str()); 
                                    //cout << lowlevelcnt[2] <<endl;  
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[2] = atoi(intermediate.c_str());   
                                    //cout<< runtimecnt[2] <<endl;
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[2] = atoi(intermediate.c_str());
                                    //cout << solncnt[2]<<endl;
                                }
                            }

                            if(lowlevelcnt[2]==0){
                                solnlowlevel[0] += 1;
                                solnlowlevel[1] += 1;
                            }
                            else{
                                solnlowlevel[0] += lowlevelcnt[0]/lowlevelcnt[2];
                                solnlowlevel[1] += lowlevelcnt[1]/lowlevelcnt[2];
                            }

                            if(lowlevelcnt[1]==0){
                                solnlowlevel[2] += 1;
                            }
                            else{
                                solnlowlevel[2] += lowlevelcnt[0]/lowlevelcnt[1];
                            }

                            if(runtimecnt[2]==0){
                                vec[0].push_back(1);
                                vec[1].push_back(1);
                                solnruntime[0] += 1;
                                solnruntime[1] += 1;
                            }
                            else{
                                vec[0].push_back(runtimecnt[0]/runtimecnt[2]);
                                vec[1].push_back(runtimecnt[1]/runtimecnt[2]);
                                solnruntime[0] += runtimecnt[0]/runtimecnt[2];
                                solnruntime[1] += runtimecnt[1]/runtimecnt[2];
                            }

                            if(runtimecnt[1]==0){
                                vec[2].push_back(1);
                                solnruntime[2] += 1;
                            }
                            else{
                                vec[2].push_back(runtimecnt[0]/runtimecnt[1]);
                                solnruntime[2] += runtimecnt[0]/runtimecnt[1];
                            }

                            if(solncnt[2]==0){
                                solncost[0] += 1;
                                solncost[1] += 1;
                            }
                            else{
                                solncost[0] += solncnt[0]/solncnt[2]; 
                                solncost[1] += solncnt[1]/solncnt[2];
                            }

                            if(solncnt[1]==0){
                                solncost[2] += 1;
                            }
                            else{
                                solncost[2] += solncnt[0]/solncnt[1];
                            }
                        }
                        ex += 1;

                        }
                    // agent += 1;
                    // }

                a += 10;
                }

            // cout << "ecbs/ecbs_1    ecbs/ecbs_2    ecbs_1/ecbs_2" << endl;
            // cout<< " weight = " << j <<" instances = "  <<  cnt<<endl;
            // cout << "Lowlevel: "<< solnlowlevel[2]/cnt << " " << solnlowlevel[0]/cnt << " " << solnlowlevel[1]/cnt << endl;
            // cout << "runtime: " << solnruntime[2]/cnt << " " << solnruntime[0]/cnt << " " << solnruntime[1]/cnt <<endl;
            // cout << "runtime SD:" << calculateSD(2,solnruntime[2]/cnt) << " " << calculateSD(0,solnruntime[0]/cnt) << " " <<calculateSD(1,solnruntime[1]/cnt) << endl;
            // cout << "Cost: " << solncost[2]/cnt << " " << solncost[0]/cnt << " " << solncost[1]/cnt << endl;

            double mean,mean1,mean2;
            mean = calculateMEAN(0);
            mean1 = calculateMEAN(1);
            mean2 = calculateMEAN(2);
            cout << j << " " << mean2 << " " << 2*(calculateSD(2,mean2)/sqrt(vec[2].size())) << " " <<  mean << " " << 2*(calculateSD(0,mean)/sqrt(vec[0].size())) << endl;

            for(int i=0;i<3;i++) vec[i].clear();
            j += 1;
            }

        break;
    
    case 7:
        a = 10;
        while(a<=200){
            //cnt = 0;
            for (size_t i = 0; i < 6; i++)
            {
                solncnt[i]=0,runtimecnt[i]=0,lowlevelcnt[i]=0,solncost[i]=0,solnruntime[i]=0,solnlowlevel[i]=0;
            } 
            j = 3;
            while(j<=3){
               int cnt = 0;  
            //     // //while(agent<4){
                    for (size_t i = 0; i < 6; i++)
                        {
                            solncnt[i]=0,runtimecnt[i]=0,lowlevelcnt[i]=0,solncost[i]=0,solnruntime[i]=0,solnlowlevel[i]=0;
                        } 
                    int ex = 0;
                    while(ex<=100){
                        int val = 0;
                        // string string1 = "/home/mustafizur/pibt/log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string2 = "/home/mustafizur/pibt/changed_log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string3 = "/home/mustafizur/pibt/changed_changed_log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        
                        // string string1 = "/home/mustafizur/pibt/log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string2 = "/home/mustafizur/pibt/changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string3 = "/home/mustafizur/pibt/changed_changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
    
                        string string1 = "/home/mustafizur/pibt/ecbs_orz601d_10_200_3/"+ file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        string string2 = "/home/mustafizur/pibt/swa_orz601d_10_200_3/" + file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        string string3 = "/home/mustafizur/pibt/dwa_orz601d_10_200_3/"+ file  + to_string(ex) + "_" +  to_string(a)+ "_" + to_string(j) + ".txt";

                        //string string4 = "/home/mustafizur/pibt/bcbs_w_log/"+ file + to_string(ex) + "_0_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        
                        //string string4 = "/home/mustafizur/pibt/dwa_dynamic_32by32_10_100_1.1/"+ file  + to_string(ex) + "_99_" +  to_string(a)+ "_" + to_string(j) + ".txt";
                        //string string4 = "/home/mustafizur/pibt/bcbs_1_log_orz601d/"+ file  + to_string(ex) + "_" +  to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string5 = "/home/mustafizur/pibt/bcbs_w_log_orz601d/"+ file  + to_string(ex) + "_" +  to_string(a)+ "_" + to_string(j) + ".txt";
                        // //string string4 = "/home/mustafizur/pibt/dwa_ecbs_log/"+ file  + to_string(ex) + "_V2_99_" +  to_string(a)+ "_" + to_string(j) + ".txt";

                        bool flag1 = false, flag2 = false,flag3=false, flag4 = true, flag5 = true;
                        if(exists_test0(string1)){
                            flag1 = true;
                            // cout << 1 << endl;
                        }
                        if(exists_test0(string2)){
                            flag2 = true;
                            //cout << 2 << endl;
                        }
                        if(exists_test0(string3)){
                            flag3 = true;
                            //cout << 3 << endl;
                        }
                        // if(exists_test0(string4)){
                        //     flag4 = true;
                        // }
                        // if(exists_test0(string5)){
                        //     flag5 = true;
                        // }
                        string data;
                        if(flag1 && flag2 && flag3 && flag4){
                            ifstream in1(string1);  
                            while(getline(in1,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[0] = atoi(intermediate.c_str());  
                                    //vec[0].push_back(lowlevelcnt[0]); 
                                    //cout << lowlevelcnt[0] << " ";
                                    write += intermediate + " ";
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    // runtimecnt[0] = atoi(intermediate.c_str());   
                                    //vec[0].push_back(runtimecnt[0]);
                                    //write += intermediate + " ";
                                    //write += to_string(runtimecnt[0]) + " ";
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[0] = atoi(intermediate.c_str());
                                    //cout << solncnt[0] <<" ";
                                    //write += intermediate + " ";
                                }
                                else if(intermediate == "[solver] ConflictCount"){
                                    getline(check1,intermediate,':');
                                    //solncnt[0] = atoi(intermediate.c_str());
                                    //cout << solncnt[0] <<" ";
                                    //write += intermediate + " ";
                                }
                            } 
                        // }
                        // // else{
                        // //     cout << runtime_limit << " ";
                        // // }

                        // if(flag2){
                            ifstream in2(string2);  
                            while(getline(in2,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[1] = atoi(intermediate.c_str());  
                                    //vec[1].push_back(lowlevelcnt[1]);
                                    //cout << lowlevelcnt[1] << " ";
                                    //write += intermediate + " ";
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[1] = atoi(intermediate.c_str());  
                                    //vec[1].push_back(runtimecnt[1]); 
                                    //cout << runtimecnt[1] << " ";
                                    //write += intermediate + " ";
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[1] = atoi(intermediate.c_str());
                                    //write += intermediate + " ";
                                    //cout << solncnt[1] << " ";
                                }
                                else if(intermediate == "[solver] ConflictCount"){
                                    getline(check1,intermediate,':');
                                    //solncnt[0] = atoi(intermediate.c_str());
                                    //cout << solncnt[0] <<" ";
                                    //write += intermediate + " ";
                                }
                            }
                        // }
                        // // else{
                        // //     cout<< runtime_limit << " ";
                        // // }

                        // if(flag3){
                         ifstream in3(string3);  
                         while(getline(in3,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[2] = atoi(intermediate.c_str()); 
                                    //vec[2].push_back(lowlevelcnt[2]); 
                                    //cout << lowlevelcnt[2] << " "; 
                                    //write += intermediate + " "; 
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[2] = atoi(intermediate.c_str()); 
                                    //write += intermediate + " "; 
                                    // vec[2].push_back(runtimecnt[2]); 
                                    //cout<< runtimecnt[2] - val << " ";
                                    //write += to_string(int(runtimecnt[2] - val)) + " ";
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[2] = atoi(intermediate.c_str());
                                    //write += intermediate + " ";
                                    //cout << solncnt[2]<< " ";
                                }
                                else if(intermediate == "[solver] DynamicTime"){
                                    getline(check1,intermediate,':');
                                    val = atoi(intermediate.c_str());
                                    //cout << solncnt[3]<< " ";
                                }
                                else if(intermediate == "[solver] ConflictCount"){
                                    getline(check1,intermediate,':');
                                    //solncnt[0] = atoi(intermediate.c_str());
                                    //cout << solncnt[0] <<" ";
                                    //write += intermediate + " ";
                                }
                            }   
                        // }
                        // // else{
                        // //     cout << runtime_limit << " ";
                        // // }

                        // if(flag4){
                            // ifstream in4(string4);  
                            // while(getline(in4,data)){
                            //     stringstream check1(data);
                            //     string intermediate;
                            //     getline(check1,intermediate,':');
                            //     if(intermediate == "[solver] Lowlevelnode"){
                            //         getline(check1,intermediate,':');
                            //         lowlevelcnt[3] = atoi(intermediate.c_str()); 
                            //         //vec[2].push_back(lowlevelcnt[2]); 
                            //         //cout << lowlevelcnt[2] << " ";  
                            //     }
                            //     else if(intermediate == "[solver] elapsed"){
                            //         getline(check1,intermediate,':');
                            //         runtimecnt[3] = atoi(intermediate.c_str());  
                            //         //vec[3].push_back(runtimecnt[3]); 
                            //         //cout<< runtimecnt[3] - val << " ";
                            //         write += intermediate + " ";
                            //     }
                            //     else if(intermediate == "SolutionCost"){
                            //         getline(check1,intermediate,':');
                            //         solncnt[3] = atoi(intermediate.c_str());
                            //         //cout << solncnt[3]<< " ";
                            //     }
                            //     else if(intermediate == "[solver] DynamicTime"){
                            //         getline(check1,intermediate,':');
                            //         val = atoi(intermediate.c_str());
                            //         //cout << solncnt[3]<< " ";
                            //     }
                            // }

                       // }
                        
                        
                            // while(getline(in5,data)){
                            //     stringstream check1(data);
                            //     string intermediate;
                            //     getline(check1,intermediate,':');
                            //     if(intermediate == "[solver] Lowlevelnode"){
                            //         getline(check1,intermediate,':');
                            //         lowlevelcnt[4] = atoi(intermediate.c_str()); 
                            //         //vec[2].push_back(lowlevelcnt[2]); 
                            //         //cout << lowlevelcnt[2] << " ";  
                            //     }
                            //     else if(intermediate == "[solver] elapsed"){
                            //         getline(check1,intermediate,':');
                            //         runtimecnt[4] = atoi(intermediate.c_str());  
                            //         //vec[3].push_back(runtimecnt[3]); 
                            //         //cout<< runtimecnt[4] << " ";
                            //     }
                            //     else if(intermediate == "SolutionCost"){
                            //         getline(check1,intermediate,':');
                            //         solncnt[4] = atoi(intermediate.c_str());
                            //         //cout << solncnt[4]<< " ";
                            //     }
                            // }

                            // if(lowlevelcnt[2]==0){
                            //     solnlowlevel[0] += 1;
                            //     solnlowlevel[1] += 1;
                            // }
                            // else{
                            //     solnlowlevel[0] += lowlevelcnt[0]/lowlevelcnt[2];
                            //     solnlowlevel[1] += lowlevelcnt[1]/lowlevelcnt[2];
                            // }

                            // if(lowlevelcnt[1]==0){
                            //     solnlowlevel[2] += 1;
                            // }
                            // else{
                            //     solnlowlevel[2] += lowlevelcnt[0]/lowlevelcnt[1];
                            // }

                            // if(runtimecnt[2]==0){
                            //     vec[0].push_back(1);
                            //     vec[1].push_back(1);
                            //     solnruntime[0] += 1;
                            //     solnruntime[1] += 1;
                            //     //cout << "Special " << 1 << endl;
                            // }
                            // else{
                            //     vec[0].push_back(runtimecnt[0]/runtimecnt[2]);
                            //     vec[1].push_back(runtimecnt[1]/runtimecnt[2]);
                            //     //cout << runtimecnt[0]/runtimecnt[2] << " " << runtimecnt[1]/runtimecnt[2] << endl;
                            //     solnruntime[0] += runtimecnt[0]/runtimecnt[2];
                            //     solnruntime[1] += runtimecnt[1]/runtimecnt[2];
                            // }

                            // if(runtimecnt[1]==0){
                            //     vec[2].push_back(1);
                            //     solnruntime[2] += 1;
                            //     //cout << "Special " << 1 << endl;
                            // }
                            // else{
                            //     vec[2].push_back(runtimecnt[0]/runtimecnt[1]);
                            //     //cout << runtimecnt[0]/runtimecnt[1] <<endl;
                            //     solnruntime[2] += runtimecnt[0]/runtimecnt[1];
                            // }
                            // if(solncnt[2]==0){
                            //     solncost[0] += 1;
                            //     solncost[1] += 1;
                            // }
                            // else{
                            //     solncost[0] += solncnt[0]/solncnt[2]; 
                            //     solncost[1] += solncnt[1]/solncnt[2];
                            // }

                            // if(solncnt[1]==0){
                            //     solncost[2] += 1;
                            // }
                            // else{
                            //     solncost[2] += solncnt[0]/solncnt[1];
                            // }
                        }
                        ex += 1;

                        }
                    // agent += 1;
                    j += 0.5;
                    write += "\n";
                    // cout << endl;
                    }

                //}

            // cout << "ecbs/ecbs_1    ecbs/ecbs_2    ecbs_1/ecbs_2" << endl;
            // cout<< " agent = " << a <<" instances = "  <<  cnt<<endl;
            // //cout << "Lowlevel: "<< solnlowlevel[2]/cnt << " " << solnlowlevel[0]/cnt << " " << solnlowlevel[1]/cnt << endl;
            // cout << "runtime: " << solnruntime[2]/cnt << " " << solnruntime[0]/cnt << " " << solnruntime[1]/cnt <<endl;
            // cout << "runtime SD:" << calculateSD(2,solnruntime[2]/cnt) << " " << calculateSD(0,solnruntime[0]/cnt) << " " <<calculateSD(1,solnruntime[1]/cnt) << endl;
            //cout << "Cost: " << solncost[2]/cnt << " " << solncost[0]/cnt << " " << solncost[1]/cnt << endl;
            
            //cout << "ecbs " << "ecbs1 " << "ecbs2" << endl;

            //cout << endl;
        
            // double mean,mean1,mean2,mean3;
            // mean = calculateMEAN(0);
            // // // // cout << "runtime SD:" << calculateSD(0,mean) << endl;
            // mean1 = calculateMEAN(1);
            // mean2 = calculateMEAN(2);
            // //mean3 = calculateMEAN(3);
            // //cout<< " agent = " << a <<" instances = "  <<  cnt<<endl;
            // //cout << a <<" " << mean << " " << mean1 << " " << mean2 << endl;
            // // // // cout << "runtime SD:" << calculateSD(0,mean) << " " << calculateSD(1,mean1) << " " <<calculateSD(2,mean2) << endl;
            // // cout << vec[0].size() << " " << vec[1].size() << " " << vec[2].size() << endl;
            // cout << a << " " << mean << " " << 2*(calculateSD(0,mean)/sqrt(vec[0].size())) << " " << mean1 << " " << 2*(calculateSD(1,mean1)/sqrt(vec[1].size())) << " " << mean2 << " " << 2*(calculateSD(2,mean2)/sqrt(vec[2].size())) << endl;
            // // //cout << a << " " << mean2 << " " << 2*(calculateSD(2,mean2)/sqrt(vec[2].size())) << " " <<  mean << " " << 2*(calculateSD(0,mean)/sqrt(vec[0].size())) << endl;

            //j += 0.1;
            // for(int i=0;i<3;i++) vec[i].clear();
            a += 10;
            }
            outfile.open("/home/mustafizur/pibt/statistics/outlier.txt");

            outfile << write << endl;

        break;

    case 8:
        a = 10;
        while(a<=200){
            j = 3.000000000;
            //while(j<6){
                    int cnt = 0;
                    for (size_t i = 0; i < 6; i++)
                    {
                        solncnt[i]=0,runtimecnt[i]=0,lowlevelcnt[i]=0,solncost[i]=0,solnruntime[i]=0,solnlowlevel[i]=0;
                    } 
                // int agent = 10;  
                // //while(agent<4){
                    int ex = 0;
                    while(ex<100){
                        // string string1 = "/home/mustafizur/pibt/log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string2 = "/home/mustafizur/pibt/changed_log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string3 = "/home/mustafizur/pibt/changed_changed_log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        
                        // string string1 = "/home/mustafizur/pibt/log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string2 = "/home/mustafizur/pibt/changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string3 = "/home/mustafizur/pibt/changed_changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
    


                        string string1 = "/home/mustafizur/pibt/log/"+ file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        string string2 = "/home/mustafizur/pibt/changed_log/"+ file + to_string(ex) + "_" +to_string(a)+ "_" + to_string(j) + ".txt";
                        string string3 = "/home/mustafizur/pibt/changed_changed_log/"+ file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";

                        bool flag1 = false, flag2 = false,flag3=false;
                        if(exists_test0(string1)){
                            flag1 = true;
                        }
                        if(exists_test0(string2)){
                            flag2 = true;
                        }
                        if(exists_test0(string3)){
                            flag3 = true;
                        }
                        if(flag1 && flag2 && flag3){
                            cnt++;
                            ifstream in1(string1);
                            ifstream in2(string2);
                            ifstream in3(string3);
                            string data;
                            while(getline(in1,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[0] = atoi(intermediate.c_str());   
                                    //cout << lowlevelcnt[0] <<endl;
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[0] = atoi(intermediate.c_str());   
                                    //cout << runtimecnt[0] <<endl;
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[0] = atoi(intermediate.c_str());
                                    //cout << solncnt[0] <<endl;
                                }
                            }
                        
                            while(getline(in2,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[1] = atoi(intermediate.c_str());  
                                    //cout << lowlevelcnt[1] <<endl; 
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[1] = atoi(intermediate.c_str());   
                                    //cout << runtimecnt[1] <<endl;
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[1] = atoi(intermediate.c_str());
                                    //cout << solncnt[1] <<endl;
                                }
                            }

                            while(getline(in3,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] Lowlevelnode"){
                                    getline(check1,intermediate,':');
                                    lowlevelcnt[2] = atoi(intermediate.c_str()); 
                                    //cout << lowlevelcnt[2] <<endl;  
                                }
                                else if(intermediate == "[solver] elapsed"){
                                    getline(check1,intermediate,':');
                                    runtimecnt[2] = atoi(intermediate.c_str());   
                                    //cout<< runtimecnt[2] <<endl;
                                }
                                else if(intermediate == "SolutionCost"){
                                    getline(check1,intermediate,':');
                                    solncnt[2] = atoi(intermediate.c_str());
                                    //cout << solncnt[2]<<endl;
                                }
                            }

                            if(lowlevelcnt[2]==0){
                                solnlowlevel[0] += 1;
                                solnlowlevel[1] += 1;
                            }
                            else{
                                solnlowlevel[0] += lowlevelcnt[0]/lowlevelcnt[2];
                                solnlowlevel[1] += lowlevelcnt[1]/lowlevelcnt[2];
                            }

                            if(lowlevelcnt[1]==0){
                                solnlowlevel[2] += 1;
                            }
                            else{
                                solnlowlevel[2] += lowlevelcnt[0]/lowlevelcnt[1];
                            }

                            if(runtimecnt[2]==0){
                                vec[0].push_back(1);
                                vec[1].push_back(1);
                                solnruntime[0] += 1;
                                solnruntime[1] += 1;
                            }
                            else{
                                vec[0].push_back(runtimecnt[0]/runtimecnt[2]);
                                vec[1].push_back(runtimecnt[1]/runtimecnt[2]);
                                solnruntime[0] += runtimecnt[0]/runtimecnt[2];
                                solnruntime[1] += runtimecnt[1]/runtimecnt[2];
                            }

                            if(runtimecnt[1]==0){
                                vec[2].push_back(1);
                                solnruntime[2] += 1;
                            }
                            else{
                                vec[2].push_back(runtimecnt[0]/runtimecnt[1]);
                                solnruntime[2] += runtimecnt[0]/runtimecnt[1];
                            }

                            if(solncnt[2]==0){
                                solncost[0] += 1;
                                solncost[1] += 1;
                            }
                            else{
                                solncost[0] += solncnt[0]/solncnt[2]; 
                                solncost[1] += solncnt[1]/solncnt[2];
                            }

                            if(solncnt[1]==0){
                                solncost[2] += 1;
                            }
                            else{
                                solncost[2] += solncnt[0]/solncnt[1];
                            }
                        }
                        ex += 1;

                        }
                    // agent += 1;
                    // }

                cout << "ecbs/ecbs_1    ecbs/ecbs_2    ecbs_1/ecbs_2" << endl;
                cout<< " agent = " << a << " weight = " << j << " instances = "  <<  cnt<<endl;
                cout << "Lowlevel: "<< solnlowlevel[2]/cnt << " " << solnlowlevel[0]/cnt << " " << solnlowlevel[1]/cnt << endl;
                cout << "runtime: " << solnruntime[2]/cnt << " " << solnruntime[0]/cnt << " " << solnruntime[1]/cnt <<endl;
                cout << "runtime SD:" << calculateSD(2,solnruntime[2]/cnt) << " " << calculateSD(0,solnruntime[0]/cnt) << " " <<calculateSD(1,solnruntime[1]/cnt) << endl;
                cout << "Cost: " << solncost[2]/cnt << " " << solncost[0]/cnt << " " << solncost[1]/cnt << endl;
                for(int i=0;i<3;i++) vec[i].clear();
                // j += 1;
                // }
            a += 10;
            }

        break;

    case 9:
        a = 250;
       // while(a<=200){
            j = 2.750000000;
            //while(j<6){
                    for (size_t i = 0; i < 6; i++)
                    {
                        conflict_cnt[i] = 0;
                    } 
                // int agent = 10;  
                // //while(agent<4){
                    //int ex = 0;
                    while(ex<100){
                        // string string1 = "/home/mustafizur/pibt/log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string2 = "/home/mustafizur/pibt/changed_log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string3 = "/home/mustafizur/pibt/changed_changed_log/8by8_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        
                        // string string1 = "/home/mustafizur/pibt/log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string2 = "/home/mustafizur/pibt/changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        // string string3 = "/home/mustafizur/pibt/changed_changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
    


                        string string1 = "/home/mustafizur/pibt/log/"+ file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        string string2 = "/home/mustafizur/pibt/dwa_ecbs_log/" + file + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                        string string3 = "/home/mustafizur/pibt/dwa_ecbs_log/"+ file  + "V2_" + to_string(ex) + "_" +  to_string(a)+ "_" + to_string(j) + ".txt";

                        bool flag1 = false, flag2 = false,flag3=false;
                        if(exists_test0(string1)){
                            flag1 = true;
                        }
                        if(exists_test0(string2)){
                            flag2 = true;
                        }
                        if(exists_test0(string3)){
                            flag3 = true;
                        }
                        if(flag1 && flag2 && flag3){
                            cnt++;
                            ifstream in1(string1);
                            ifstream in2(string2);
                            ifstream in3(string3);
                            string data;
                            while(getline(in1,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] ConflictCount"){
                                    getline(check1,intermediate,':');
                                    cnt1 = atoi(intermediate.c_str());   
                                    //cout << lowlevelcnt[0] <<endl;
                                }
                            }
                        
                            while(getline(in2,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] ConflictCount"){
                                    getline(check1,intermediate,':');
                                    cnt2 = atoi(intermediate.c_str());  
                                    //cout << lowlevelcnt[1] <<endl; 
                                }
                            }

                            while(getline(in3,data)){
                                stringstream check1(data);
                                string intermediate;
                                getline(check1,intermediate,':');
                                if(intermediate == "[solver] ConflictCount"){
                                    getline(check1,intermediate,':');
                                    cnt3 = atoi(intermediate.c_str()); 
                                    //cout << lowlevelcnt[2] <<endl;  
                                }
                            }
                        }

                            if(cnt1 < cnt2)
                                conflict_cnt[0] ++;
                            if(cnt1 < cnt3)
                                conflict_cnt[1] ++;
                            if(cnt2 < cnt1)
                                conflict_cnt[2] ++;
                            if(cnt2 < cnt3)
                                conflict_cnt[3] ++;
                            if(cnt3 < cnt1)
                                conflict_cnt[4] ++;
                            if(cnt3 < cnt2)
                                conflict_cnt[5] ++;
                    // agent += 1;
                    ex += 1;
                    }

                cout << "ecbs -> swa_ecbs   ecbs -> dwa_ecbs    swa_ecbs -> ecbs   swa_ecbs -> dwa_ecbs    dwa_ecbs > ecbs    dwa_ecbs > swa_ecbs" << endl; 
                for (size_t i = 0; i < 6; i++)
                    {
                        cout << conflict_cnt[i]<< " ";
                    } 
                // j += 1;
                //}
            a += 10;
            cout << endl;

        break;
    
    case 10:
        // for succsess and completeness
        a = 60;
        cout << "input row and col" <<endl;
        cin >> r >> c;
        while(a<=120){
            j = 1.05;
            while(j<=3){
                ex = 0;
                col = 0;
                while(ex<=99){
                // string string1 = "/home/mustafizur/pibt/log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                // string string2 = "/home/mustafizur/pibt/changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                // string string3 = "/home/mustafizur/pibt/changed_changed_log/32by32_agents" + to_string(agent) + "_ex" + to_string(ex) + "_" + to_string(a)+ "_" + to_string(j) + ".txt";
                
                string string1 = "/home/mustafizur/pibt/ecbs_32by32_60_120_1.05_3/"+ file + to_string(ex) + "_0_" + to_string(a)+ "_" + to_string(j) + ".txt";
                string string2 = "/home/mustafizur/pibt/swa_32by32_60_120_1.05_3/" + file + to_string(ex) + "_0_" + to_string(a)+ "_" + to_string(j) + ".txt";
                string string3 = "/home/mustafizur/pibt/dwa_32by32_60_120_1.05_3/"+ file  + to_string(ex) + "_0_" +  to_string(a)+ "_" + to_string(j) + ".txt";
                bool flag1 = false, flag2 = false,flag3=false;
                //cout<< string1 << endl;
                if(exists_test0(string1)){
                    flag1 = true;
                }
                if(exists_test0(string2)){
                    flag2 = true;
                }
                if(exists_test0(string3)){
                    flag3 = true;
                }
                if(flag1 && flag2 && flag3){
                    if(row == r && col == c){
                        cout << a << " " << j << " " << ex << endl;
                        flag = true;
                        break;
                    }
                    col ++;
                }
                // if(cnt5 == 44 && cnt == 0){
                //     cout << a << " " << j << " " << ex << endl;
                //     cnt5 ++;
                // }
                // if(exists_test0(string4)){
                //     flag3 = true;
                //     cnt4 ++;
                // }
                ex += 1;
                }

            if(flag)
                break;
                
            row ++;
            j += 0.05;

            }
            if(flag)
                break;
            // cout<< a <<" "<< cnt1/cnt4 << " " << cnt2/cnt4 << " " << cnt3/cnt4  << " " <<endl;
            //j += 0.2;
            a += 10;
       }
        //cout<< cnt1/cnt4 << " " << cnt2/cnt4 << " " << cnt3/cnt4 << " " << cnt4 <<endl;

        break;
    } 
    return 0;
}