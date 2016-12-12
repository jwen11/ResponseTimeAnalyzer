#include <stdio.h>
#include <cctype>
#include <cmath>

#include <string>
#include <iomanip>
#include <iostream>
#include <vector>

#include "../include/task.h"
#include "../include/misc.h"
#include "../include/message.h"
#include "../include/config.h"

#include "../include/file_handler.h"
#include "../include/analysis.h"

using namespace std;

#define VERBOSE 1

int main(int argc, char** argv){
    if (argc >4 || argc < 3) {
        cout<<"[usage]: ./analyse <taskset> <messageset> <configure> "<<endl;
        return 0;
    }

    
    vector<vector <task> > TaskSet;
    vector<vector <message> > inMSGSet;
    vector<vector <message> > outMSGSet;
    server_conf configure;
    
    task_read(argv[1], TaskSet);
    message_read(argv[2], TaskSet, inMSGSet, outMSGSet );
    configure_read(argv[3], configure);

    for (int i = 0; i < TaskSet.size(); ++i){
        prioritize(TaskSet[i]);
        prioritize(inMSGSet[i]);
        prioritize(outMSGSet[i]);
    }

    
#if VERBOSE
    cout<<endl<<endl<<"Task set is :"<<endl;
    display(TaskSet);
    
    cout<<endl<<endl<<"inMSGSet set is :"<<endl;
    display(inMSGSet); 
    
    cout<<endl<<endl<<"outMSGSet set is :"<<endl;
    display(outMSGSet);
    
    cout<<endl<<endl<<"Server Config set is :"<<endl;
    display(configure);
     
#endif    

//    float effectU,actualU,UB;
//    
//    unsigned int size = TaskSet.size();
//    UB = size * (pow(2.0, 1.0/size) -1.0);
//    int unSchedTasks = analysis(TaskSet, effectU, actualU);
//
//    cout<<endl<<endl;
//    cout<<"The Utilization Bound     of"<<setw(4)<<size<<" task(s)  is "<<UB<<endl;
//    cout<<"The Effective Utilization of the task set is "<<effectU<<endl;
//    cout<<"The Actual    Utilization of the task set is "<<actualU<<endl;
//
//    cout<<endl<<"There are "<<setw(5)<<unSchedTasks<<" task(s) unschedulable"<<endl;
//    
//        cout<<setw(6)<<"Prio"<<setw(6)<<"ID"<<setw(6)<<"Exec"<<setw(6)<<"Priod"<<setw(6)<<"Dline"<<setw(6)<<"Blk"<<setw(6)<<"R"<<endl;
//    for (it = TaskSet.begin(); it != TaskSet.end(); ++it){
//        cout<<setw(6)<<it->getP()<<setw(6)<<it->getID()<<setw(6)<<it->getC()<<setw(6)<<it->getT()<<setw(6)<<it->getD()<<setw(6)<<it->getJ()<<setw(6)<<it->getR();
//        if (it->IsSchedulable() == 0) cout<<"  !!Unschedulable!!";
//        cout<<endl;
//    }
//
return 0;

}
