
#include<cassert>
#include<iostream>

#include "../include/define.h"
#include "../include/misc.h"
#include "../include/analysis.h"
#include "../include/task.h"
#include "../include/config.h"
using namespace std;

void analysis_inMSGSet(vector<vector<message> >& inMSGSet, server_conf& configure){
    
    unsigned int prevR, tempR,tempV, size,slot,TDMA;
    unsigned int ceiling, floor,times,dline;

    unsigned int numSlots = configure.slot.size();
    unsigned int numCPUs = inMSGSet.size();
    TDMA= configure.T;

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

}
void analysis_outMSGSet(vector<vector<message> >& outMSGSet, server_conf& configure){
    unsigned int prevR, tempR,tempV, size,slot,TDMA;
    unsigned int ceiling, times,dline;

    unsigned int numSlots = configure.slot.size();
    unsigned int numCPUs = outMSGSet.size();
    TDMA= configure.T;

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
}

int analysis_taskSet(vector<vector<task> >& taskSet, server_conf& configure){ //return 0 if schedulable, esle the ID of first unschedulable task
    unsigned int prevR, tempR, tempJ, newJ;
    unsigned int ceiling, times,dline;
    int * unfixedcnt;
    int ret = -1;

    bool RFixed, JFixed, unFixed,CoreFixed;

    unsigned int numSlots = configure.slot.size();
    unsigned int numCPUs = taskSet.size();
    // SCE blocking term
    unsigned int KqLmax =0; 
    unsigned int B = KqLmax * (numCPUs -1);

    unfixedcnt = new int [numCPUs];



    //initially all task response time unfixed
    for (int i =0; i < numCPUs; ++i){
        unfixedcnt[i] = taskSet[i].size();
    }

    int iter =0;

    while (ret <0 && iter < THRESHOLD){  //until a task miss dline or all task J&R fixed
        for (int i =0; i < numCPUs; ++i){//for each core
            for (int j =0 ; j < taskSet[i].size(); ++j){ //for eacc task in that core
                
                unFixed = false;
                if (! taskSet[i][j].JFixed){
                    unFixed = true;
                    JFixed =true;
                    tempJ =taskSet[i][j].J.size() ? taskSet[i][j].getJ():0;

                    for (int k =0; k <taskSet[i][j].incomingMessageReceive.size(); ++k){
                        JFixed &= (taskSet[i][j].incomingMessageReceive[k]->getFrom()->JFixed & taskSet[i][j].incomingMessageReceive[k]->getFrom()->RFixed);
        dbg_msg(k);
                        newJ =  taskSet[i][j].incomingMessageReceive[k]->getFrom()->getJ() +
                                taskSet[i][j].incomingMessageReceive[k]->getFrom()->getR() + 
                                taskSet[i][j].incomingMessageReceive[k]->getJ()            +
                                taskSet[i][j].incomingMessageSend[k]->getJ();
        dbg_msg(newJ);
                        tempJ = (newJ >= tempJ)? newJ : tempJ;
        dbg_msg(tempJ);
                    }
                    if (tempJ > taskSet[i][j].getJ()){
                        taskSet[i][j].setJ(tempJ);
                    }
                    taskSet[i][j].JFixed = JFixed;
                }
            
                if (! taskSet[i][j].RFixed){
                    unFixed = true;
                    dline = taskSet[i][j].getD();
                    tempJ = taskSet[i][j].getJ();
                    //Set R0
                    if (taskSet[i][j].R.size() == 0){
                        tempR = taskSet[i][j].getC() + B;
                        for (int k =0; k <j; ++k){
                            tempR+= taskSet[i][k].getC();
                        }
                        taskSet[i][j].setR(tempR);
                    }
                    else {
                        tempR = taskSet[i][j].getR();
                    }
                    //Calculate R
                    while (tempR + tempJ<= dline){
                        RFixed = true;
                        dbg_msg(tempR);
                        dbg_msg(tempJ);
                        dbg_msg(dline);
                        prevR = taskSet[i][j].getR();
                        tempR = taskSet[i][j].getC() + B;
                            for (int k =0; k <j; ++k){
                                //Assume  always J_k < D_k
                                //RFixed &=  taskSet[i][k].JFixed;
                                times = (prevR + taskSet[i][k].getD()) / taskSet[i][k].getT() ;
                                ceiling = (prevR + taskSet[i][k].getD() - times * (taskSet[i][k].getT())) ? times +1 : times;
                                tempR+= taskSet[i][k].getC() * ceiling;
                            }
                        taskSet[i][j].setR(tempR);
                        if (tempR == prevR){
                            taskSet[i][j].RFixed = RFixed;
                            break;
                        }
                    }
                    if (tempR + tempJ> dline){
                        RFixed = true;
                        delete unfixedcnt;
                        return taskSet[i][j].getID(); 
                    }

                }
                if (unFixed & JFixed & RFixed){
#if DBG                
                    cout<<iter<<" "<<i<<" "<<j<<endl;
#endif
                    --unfixedcnt[i] ;
                }


            }//for each taskSet[i][j]
            
        }// for each core
        CoreFixed = true;
        for (int i =0; i < numCPUs; ++i){
            CoreFixed &=  (unfixedcnt[i] ==0);
        }
        if (CoreFixed){
            ret =0; //all task response times are fixed and schedulable
        }
    ++iter;
    }//while ret<0

#if DBG                
    for (int i =0; i < numCPUs; ++i){
        cout<<unfixedcnt[i]<<endl;
    }
#endif
    if (ret ==0 ){
        cout<<"Schedulable in "<<iter<<" iterations"<<endl;
    }
    delete unfixedcnt;
    return ret;

}
int analysis(  vector<vector<task> >& taskSet,  vector<vector<message> >& inMSGSet, vector<vector<message> >& outMSGSet, server_conf& configure, vector<float>& effU, vector<float>& actU ){
        


    assert (taskSet.size() == inMSGSet.size());
    assert (taskSet.size() == outMSGSet.size());

    unsigned int numSlots = configure.slot.size();
    unsigned int numCPUs = taskSet.size();
    int ret;
    float eU, aU;
    assert(numSlots >= numCPUs);
     
//Compute Message Jitters first
    analysis_inMSGSet(inMSGSet, configure);
    analysis_outMSGSet(outMSGSet, configure);



//Iteratively compute all R and J of tasks
    ret = analysis_taskSet(taskSet, configure);

    
    dbg_msg("analysis_taskSet finished");
    for (int i=0; i < taskSet.size(); ++i){
        eU= aU = 0.0;
        for (int j=0; j < taskSet[i].size(); ++j){
            eU+= (float)(taskSet[i][j].getC()+taskSet[i][j].getJ() )/taskSet[i][j].getT();
            aU+= (float)(taskSet[i][j].getC())/taskSet[i][j].getT();
        }
        effU.push_back(eU);
        actU.push_back(aU);
    }



   return ret; 
}

