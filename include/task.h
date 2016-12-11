#ifndef _TASK_H_
#define _TASK_H_

#include <string>
using namespace std;

class task{
    unsigned int P; // priority
    unsigned int ID;
    float C; //execution time
    float T; //period
    float D; //deadline
    float B; //block time
    float R; //analysis
    
//    void setC (float in);
//    void setT (float in);
//    void setB (float in);
//    void setD (float in);
public:
    task (unsigned int ID,float C, float T);
    task (unsigned int ID,float C, float T, float D);
    task (unsigned int ID,float C, float T, float D, float B);
    task (unsigned int P,unsigned int ID,float C, float T);
    task (unsigned int P,unsigned int ID,float C, float T, float D);
    task (unsigned int P,unsigned int ID,float C, float T, float D, float B);

    void setR (float in);
    void setP (unsigned int  in);
    
    unsigned int getP();
    unsigned int getID();
    float getC();
    float getT();
    float getD();
    float getB();
    float getR();
    friend bool taskCompare( const task& lhs, const task& rhs);

    bool IsSchedulable();
};


#endif

