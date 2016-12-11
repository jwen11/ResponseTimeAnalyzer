#include <stdio.h>
#include <cctype>
#include <cmath>

#include <string>
#include <iomanip>
#include <iostream>
#include <vector>

#include "../include/task.h"
#include "../include/file_handler.h"
#include "../include/analysis.h"

using namespace std;


int main(int argc, char** argv){
    if (argc >3 || argc < 2) {
        cout<<"[usage]: ./analyse <file in> [p]"<<endl;
        return 0;
    }

    bool flagP = (argc ==3);
    
    vector <task> TaskSet;
    vector<task>::iterator it;

    file_read(argv[1], TaskSet, flagP);

    prioritize(TaskSet, flagP);
    

    cout<<"The task set is :"<<endl;
        cout<<setw(6)<<"Prio"<<setw(6)<<"ID"<<setw(6)<<"Exec"<<setw(6)<<"Priod"<<setw(6)<<"Dline"<<setw(6)<<"Blk"<<endl;
    for (it = TaskSet.begin(); it != TaskSet.end(); ++it){
        cout<<setw(6)<<it->getP()<<setw(6)<<it->getID()<<setw(6)<<it->getC()<<setw(6)<<it->getT()<<setw(6)<<it->getD()<<setw(6)<<it->getB()<<endl;
    }

    float effectU,actualU,UB;
    
    unsigned int size = TaskSet.size();
    UB = size * (pow(2.0, 1.0/size) -1.0);
    int unSchedTasks = analysis(TaskSet, effectU, actualU);

    cout<<endl<<endl;
    cout<<"The Utilization Bound     of"<<setw(4)<<size<<" task(s)  is "<<UB<<endl;
    cout<<"The Effective Utilization of the task set is "<<effectU<<endl;
    cout<<"The Actual    Utilization of the task set is "<<actualU<<endl;

    cout<<endl<<"There are "<<setw(5)<<unSchedTasks<<" task(s) unschedulable"<<endl;
    
        cout<<setw(6)<<"Prio"<<setw(6)<<"ID"<<setw(6)<<"Exec"<<setw(6)<<"Priod"<<setw(6)<<"Dline"<<setw(6)<<"Blk"<<setw(6)<<"R"<<endl;
    for (it = TaskSet.begin(); it != TaskSet.end(); ++it){
        cout<<setw(6)<<it->getP()<<setw(6)<<it->getID()<<setw(6)<<it->getC()<<setw(6)<<it->getT()<<setw(6)<<it->getD()<<setw(6)<<it->getB()<<setw(6)<<it->getR();
        if (it->IsSchedulable() == 0) cout<<"  !!Unschedulable!!";
        cout<<endl;
    }

return 0;

}
