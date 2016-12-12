
#include<algorithm>
#include<cassert>

#include "../include/analysis.h"
#include "../include/task.h"
#include "../include/config.h"
using namespace std;

bool taskCompare( const task& lhs, const task& rhs){
    if (lhs.P < rhs.P ) return true;
    else if (lhs.P == rhs.P &&lhs.T < rhs.T ) return true;
    else return false;
}

bool messageCompare( const message& lhs, const message& rhs){
    if (lhs.P < rhs.P ) return true;
    else if (lhs.P == rhs.P &&lhs.T < rhs.T ) return true;
    else return false;
}

int prioritize(  vector<task>& taskSet){
    sort(taskSet.begin(),taskSet.end(), taskCompare);
    unsigned int P =1;
        for (vector<task>::iterator it = taskSet.begin() ; it != taskSet.end(); ++it){
            it->setP(P); 
            ++P;
        }

}

int prioritize(  vector<message>& messageSet){
    sort(messageSet.begin(),messageSet.end(), messageCompare);
    unsigned int P =1;
        for (vector<message>::iterator it = messageSet.begin() ; it != messageSet.end(); ++it){
            it->setP(P); 
            ++P;
        }

}

int analysis(  vector<vector<task> >& taskSet,  vector<vector<message> >& inMSGSet, vector<vector<message> >& outMSGSet, server_conf& configure, vector<float>& effU, vector<float>& actU ){
        
    unsigned int prevR, tempR,tempV, size,slot,TDMA;
    int ret =0;
    unsigned int ceiling, floor,times,dline;
    


    unsigned int numSlots = configure.slot.size();
    unsigned int numCPUs = taskSet.size();
   
    assert(numSlots >= numCPUs);
     
    TDMA= configure.T;
//Compute Message Jitters first
for (int i =0; i < numCPUs; ++i){
    size = configure.size_in[i];
    slot = configure.slot[i];
    
     
    for (int j =0 ; j < inMSGSet[i].size(); ++j){
        if (inMSGSet[i][j].getFrom()->getCPU() == i){ //if this message is intra-core, no message jitter
            
            inMSGSet[i][j].setJ(0);
            inMSGSet[i][j].JFixed = true;                
            continue;
        }

        tempV = 0;
        dline = inMSGSet[i][j].getT();
        
        //set R0
        for (int k=0; k <=j; ++k){ //include j self
            tempV += inMSGSet[i][k].getSize();
        }
        floor = tempV /size;
        tempR = floor * TDMA;
        for (int k = inMSGSet[i][j].getFrom()->getCPU(); k != i; k =(k+1)%numSlots){
            tempR += configure.slot[k];
        }
        prevR = tempR;
        inMSGSet[i][j].setJ(tempR);

        //Calculate Rn
        while (tempR <= dline){
            tempV = inMSGSet[i][j].getSize();
            for (int k =0; k < j ; ++k){ //exclude self
                //here assume Jitter no later than deadline
                times = (tempR+inMSGSet[i][k].getT())/(inMSGSet[i][k].getT());
                ceiling = (tempR %inMSGSet[i][k].getT()) ?  times+1: times;
                tempV += ceiling * inMSGSet[i][k].getSize();
            }
            floor = tempV /size;
            tempR = floor * TDMA ;
            for (int k = inMSGSet[i][j].getFrom()->getCPU(); k != i; k =(k+1)%numSlots){
                tempR += configure.slot[k];
            }
            inMSGSet[i][j].setJ(tempR);
            //break if converge
            if (tempR == prevR){
                break;
            }
            prevR = tempR;

        }
        inMSGSet[i][j].JFixed = true;                
        
    }

}

for (int i =0; i < numCPUs; ++i){
    size = configure.size_out[i];
    slot = configure.slot[i];
     
    for (int j =0 ; j < outMSGSet[i].size(); ++j){
        if (outMSGSet[i][j].getTo()->getCPU() == i){ //if this message is intra-core, no message jitter
            
            outMSGSet[i][j].setJ(0);
            outMSGSet[i][j].JFixed = true;                
            continue;
        }
        tempV = 0;
        dline = outMSGSet[i][j].getT();
        
        //set R0
        for (int k=0; k <=j; ++k){ //include j self
            tempV += outMSGSet[i][k].getSize();
        }
        times = tempV /size;
        ceiling = (tempV%size)? times+1: times;
        tempR = ceiling * TDMA + slot;
        prevR = tempR;
        outMSGSet[i][j].setJ(tempR);

        //Calculate Rn
        while (tempR <= dline){
            tempV = outMSGSet[i][j].getSize();
            for (int k =0; k < j ; ++k){ //exclude self
                //here assume Jitter no later than deadline
                times = (tempR+outMSGSet[i][k].getT())/outMSGSet[i][k].getT();
                ceiling = (tempR %outMSGSet[i][k].getT()) ?  times+1: times;
                tempV += ceiling * outMSGSet[i][k].getSize();
            }
            times = tempV /size;
            ceiling = (tempV%size)? times+1: times;
            tempR = ceiling * TDMA + slot;
            outMSGSet[i][j].setJ(tempR);
            //break if converge
            if (tempR == prevR){
                break;
            }
            prevR = tempR;

        }
        outMSGSet[i][j].JFixed = true;                
        
    }

}



//Iteratively Compute Task Jitter and ResponseTime
//
//
//
//   for ( it = taskSet.begin() ; it != taskSet.end(); ++it){
//           tempR = it->getC() ;
//       for ( j = taskSet.begin() ; j != it; ++j){
//           tempR += j->getC();
//       }
//       
//       while (tempR <= it->getD()){
//           prevR = tempR;
//           tempR = it->getC();
//           
//           for (j = taskSet.begin() ; j != it; ++j){
//               times = prevR / j->getT() ;
//               ceiling = ( prevR - times* j->getT() ) ? times +1 : times;
//
//               tempR += j->getC() * ceiling;
//           }
//           if (tempR == prevR){
//               assert (tempR <= it->getD());
//               break; //is schedulable
//           }
//       }// it unschedulable
//
//        it->setR(tempR);     
//        effU +=  (it->getC()+ it->getT() - it->getD()  )/it->getT() ;
//        actU +=  (it->getC() )/it->getT() ;
//        if (tempR > it->getD()) ++ret;
//    }

   return ret; 
}

