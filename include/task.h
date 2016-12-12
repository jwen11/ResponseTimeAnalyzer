#ifndef _TASK_H_
#define _TASK_H_

#include <string>
#include <vector>

#include "../include/message.h"

using namespace std;

class message;


class task{
    unsigned int P; // priority
    unsigned int ID;
    unsigned int CPU;
    unsigned int C; //execution time
    unsigned int T; //period
    unsigned int D; //deadline

    vector <unsigned int> J; //Releas Jitter time
    vector <unsigned int> R; //Response analysis
            
//    void setC (unsigned in);
//    void setT (unsigned in);
//    void setD (unsigned in);
public:
    bool JFixed;
    bool RFixed;
    vector<message*> incomingMessages;

    task (unsigned int CPU,unsigned int ID,unsigned int C, unsigned int T);
    task (unsigned int CPU,unsigned int ID,unsigned int C, unsigned int T, unsigned D);
    task (unsigned int CPU,unsigned int ID,unsigned C, unsigned T, unsigned D,unsigned int P);

    void setP (unsigned int  in);
    void setR (unsigned in);
    void setJ (unsigned in);
    
    unsigned int getP();
    unsigned int getID();
    unsigned int getCPU();
    unsigned int getC();
    unsigned int getT();
    unsigned int getD();
    unsigned int getR();
    unsigned int getJ();
    friend bool taskCompare( const task& lhs, const task& rhs);

    bool IsSchedulable();
};


#endif

