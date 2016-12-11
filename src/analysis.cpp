
#include<algorithm>
#include<cassert>

#include "../include/analysis.h"
#include "../include/task.h"
using namespace std;

bool taskCompare( const task& lhs, const task& rhs){
    if (lhs.P < rhs.P ) return true;
    else if (lhs.P == rhs.P &&lhs.T < rhs.T ) return true;
    else return false;
}

int prioritize(  vector<task>& TaskSet, bool flagP){
    sort(TaskSet.begin(),TaskSet.end(), taskCompare);
    unsigned int P =1;
    if (~flagP){
        for (vector<task>::iterator it = TaskSet.begin() ; it != TaskSet.end(); ++it){
            it->setP(P); 
            ++P;
        }
    }

}

int analysis(  vector<task>& TaskSet, float& effU, float& actU ){
        
    float tempR = 0, prevR =0;
    int ret =0;
    unsigned int ceiling, times;
    
    vector<task>::iterator it, j;

    effU =actU =0;

   for ( it = TaskSet.begin() ; it != TaskSet.end(); ++it){
           tempR = it->getC() + it->getB();
       for ( j = TaskSet.begin() ; j != it; ++j){
           tempR += j->getC();
       }
       
       while (tempR <= it->getD()){
           prevR = tempR;
           tempR = it->getC()+  it->getB();
           
           for (j = TaskSet.begin() ; j != it; ++j){
               times = prevR / j->getT() ;
               ceiling = ( prevR - times* j->getT() ) ? times +1 : times;

               tempR += j->getC() * ceiling;
           }
           if (tempR == prevR){
               assert (tempR <= it->getD());
               break; //is schedulable
           }
       }// it unschedulable

        it->setR(tempR);     
        effU +=  (it->getC()+ it->getT() - it->getD() + it->getB() )/it->getT() ;
        actU +=  (it->getC() )/it->getT() ;
        if (tempR > it->getD()) ++ret;
    }

   return ret; 
}

