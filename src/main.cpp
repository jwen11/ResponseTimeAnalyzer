#include <stdio.h>
#include <cctype>
#include <cmath>

#include <string>
#include <iomanip>
#include <iostream>
#include <vector>

#include "../include/define.h"
#include "../include/task.h"
#include "../include/misc.h"
#include "../include/message.h"
#include "../include/config.h"

#include "../include/file_handler.h"
#include "../include/analysis.h"

using namespace std;


int main(int argc, char** argv){
    if (argc >4 || argc < 3) {
        cout<<"[usage]: ./analyse <taskset> <messageset> <configure> "<<endl;
        return 0;
    }

    
    vector<vector <task> > TaskSet;

    vector<vector <message> > inMSGSet;
    vector<vector <message> > outMSGSet;
    server_conf configure;
    
    configure_read(argv[3], configure);
    task_read(argv[1], TaskSet,configure);
    message_read(argv[2], TaskSet, inMSGSet, outMSGSet );

    
#if VERBOSE
    
    cout<<endl<<endl<<"Server Config set is :"<<endl;
    display(configure);
   
    cout<<endl<<endl<<"Task set is :"<<endl;
    display(TaskSet);
    
    cout<<endl<<endl<<"inMSGSet set is :"<<endl;
    display(inMSGSet); 
    
    cout<<endl<<endl<<"outMSGSet set is :"<<endl;
    display(outMSGSet);
#endif 

    vector<float> effU;
    vector<float> actU;

    int unSchedTasks = analysis(   TaskSet,   inMSGSet,  outMSGSet,  configure,  effU,  actU );
    cout<<"The effective U in each core:";
    for (int i =0; i < TaskSet.size(); ++i){
        cout<<setw(6)<<effU[i]<<" ";
    }
    cout<<endl;
    cout<<"The actual U in each core:";
    for (int i =0; i < TaskSet.size(); ++i){
        cout<<setw(6)<<actU[i]<<" ";
    }
    cout<<endl;
    if (unSchedTasks){
        cout<<"The first unschedulabe task is :"<<unSchedTasks<<endl;
    }
    else{
        cout<<"The taskset is schedulable."<<endl;
    }
#if VERBOSE
    cout<<endl<<endl<<"Task set is :"<<endl;
    display(TaskSet);
    
    cout<<endl<<endl<<"inMSGSet set is :"<<endl;
    display(inMSGSet); 
    
    cout<<endl<<endl<<"outMSGSet set is :"<<endl;
    display(outMSGSet);
     
#endif    

return 0;

}
