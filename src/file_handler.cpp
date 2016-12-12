
#include <string>
#include <iomanip>
#include <cctype>
#include <cassert>
#include <sstream>
#include <iostream>
#include <fstream>

#include "../include/file_handler.h"
#include "../include/task.h"
#include "../include/message.h"
#include "../include/config.h"

/*
%%%%%TaskFile format:
%Number of CPUs
2
%Meesgaes
%CPU  ID  C    T  [D] [P]
1     5   7   29
1     3   5   14
2     4   5   14
*/

int task_read ( char* filename, vector<vector<task> >& TaskSet){
    
    ifstream ifs;
    ifs.open(filename,ifstream::in);
    
    string line;
    char ch;

    unsigned numCPUs;

    unsigned int CPU, ID, P;
    unsigned int C, T, D ;
    unsigned int format; 


//Get how many activated cores
    ch = ifs.peek();
    while (ch != EOF){
        getline (ifs, line);
        stringstream input(line);
        if (isdigit(ch)){
            input>>numCPUs;
            break;
        }

        ch = ifs.peek();
    }


//Init empty tasksets in each activated CPU
    vector<task> empty_list;
    for (int i =0; i < numCPUs; ++i){
        TaskSet.push_back(empty_list);
    }

//Get the tasks
    ch = ifs.peek();
    while (ch != EOF){
        getline (ifs, line);
        stringstream input(line);
        if (isdigit(ch)){
        
          input>>CPU;
          input>>ID >>C >>T;
          format =0;
          if (input.peek()!= EOF){
             input >>D;
             if (D)
                format =1;
          
            if (input.peek()!= EOF){
                input >>P;
                if (P)
                    format =2;
            }
          }

            if (format ==2)     TaskSet[CPU].push_back(task(CPU,ID,C,T,D,P));
            else if (format ==1)TaskSet[CPU].push_back(task(CPU,ID,C,T,D));
            else                TaskSet[CPU].push_back(task(CPU,ID,C,T));

        }
        ch = ifs.peek();
    }
    ifs.close();
    for (int i =0; i < TaskSet.size(); ++i)
        cout<<TaskSet[i].size()<<" ";
    cout<<endl;
    return 0;
}


/*
%%%%%MessageFile format:
%Meesgaes
%ID From To Size [Period] [Priority_IN] [Priority_OUT] 
1   5   7   29
*/
int message_read ( char* filename, vector<vector<task> >& TaskSet, vector<vector<message> >& inMSGSet, vector<vector<message> >& outMSGSet)
{
    ifstream ifs;
    ifs.open(filename,ifstream::in);
    string line;
    char ch;
    unsigned numCPUs;
    unsigned int ID, From, To, PeriodFrom, PeriodTo;
    unsigned int Size, T,Pin, Pout;
    task* from;
    task* to;
    bool getFrom, getTo;
//Get how many activated cores
    numCPUs = TaskSet.size();
    cout<<numCPUs<<endl;
//Init empty tasksets in each activated CPU
    vector<message> empty_list;
    for (int i =0; i < numCPUs; ++i){
        inMSGSet.push_back (empty_list);
        outMSGSet.push_back(empty_list);
    }
//Get the Message
    ch = ifs.peek();
    while (ch != EOF){
        getline (ifs, line);
        stringstream input(line);
        cout<<line<<endl;
        if (isdigit(ch)){
          input>>ID>>From>>To>>Size;
        T = Pin = Pout = 0;
        if (input.peek() != EOF){
            input >>T;
            if (input.peek() != EOF)
                input >>Pin;
            if (input.peek() != EOF)
                input >>Pout;
        }
//Get the pointer to the task
        getFrom = false;
        getTo  = false;
        for (int i =0; i < numCPUs; ++i){
            for (vector<task>::iterator j =  TaskSet[i].begin(); j != TaskSet[i].end(); ++j){
                if ((*j).getID() == From) {
                    from = &(*j);
                    getFrom =true;
                }
                if ((*j).getID() == To){
                    to = &(*j);
                    getTo =true;
                }
            }
            if (getFrom & getTo) break;
        }
//Get the period
        if (T ==0 ){
            if (from->getT() > to->getT() )
                T = from->getT();
            else 
                T = to->getT();    
        }
        outMSGSet[from->getCPU()].push_back( message(ID,from, to, T, Size, Pout));
        inMSGSet[to->getCPU()].push_back(    message(ID,from, to, T, Size, Pin));
        }
        ch = ifs.peek();
    }
    ifs.close();
    return 0;
}

/*
%%%%%ConfigFile format:
%Number of CPUs
2
%TDMA Period
10
%size_in    size_out   slot   
2048   2048  1
2048   2048  1
*/

int configure_read ( char* filename, server_conf& conf){
    ifstream ifs;
    ifs.open(filename,ifstream::in);
    
    string line;
    char ch;

    unsigned numCPUs;
    unsigned T, in, out, slot;

//Get how many activated cores
    ch = ifs.peek();
    while (ch != EOF){
        getline (ifs, line);
        stringstream input(line);
        if (isdigit(ch)){
            input>>numCPUs;
            break;
        }

        ch = ifs.peek();
    }

//Get TDMA Period
    ch = ifs.peek();
    while (ch != EOF){
        getline (ifs, line);
        stringstream input(line);
        if (isdigit(ch)){
            input>>T;
            break;
        }

        ch = ifs.peek();
    }

    conf.T = T;


//Get the configure of each server
    ch = ifs.peek();
    while (ch != EOF){
        getline (ifs, line);
        stringstream input(line);
        cout<<line<<endl;
        if (isdigit(ch)){
          input>>in>>out>>slot;
          conf.size_in.push_back(in);
          conf.size_out.push_back(out);
          conf.slot.push_back(slot);
        }
        ch = ifs.peek();
    }
    assert (conf.slot.size() == numCPUs);
    return 0;
}
