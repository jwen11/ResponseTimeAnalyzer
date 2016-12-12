#ifndef _MSG_H_
#define _MSG_H_

#include <string>

#include"../include/task.h"

using namespace std;

class task;

class message{
    unsigned int P;  //Priority
    unsigned int ID;
    unsigned int T;  //Period
    unsigned int Size; 
    task* from;
    task* to;    
public:
    vector<unsigned int> J;
    bool JFixed;
    
    message (unsigned int ID,task* from ,task* to, unsigned int T, unsigned int Size,unsigned int P);

    unsigned int getP();
    unsigned int getID();
    unsigned int getT();
    unsigned int getSize();
    task* getFrom();
    task* getTo();
    
    void setP( unsigned int in );

    unsigned int getJ();
    void setJ(unsigned int in );

    friend bool messageCompare( const message& lhs, const message& rhs);

};


#endif

