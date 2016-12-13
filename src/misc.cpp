
#include<vector>
#include <string>
#include <iomanip>
#include <iostream>

#include "../include/define.h"
#include "../include/misc.h"
#include "../include/message.h"
#include "../include/task.h"
#include "../include/config.h"

using namespace std;

void display(vector<vector< task> >& in){
    cout<<"The task set is in "<<in.size()<<" cores:"<<endl;
        cout<<setw(6)<<"CPU"<<setw(6)<<"Prio"<<setw(6)<<"ID"<<setw(6)<<"Exec"<<setw(6)<<"Priod"<<setw(6)<<"Dline"<<setw(6)<<"InMSG"<<endl;

    for (int i =0; i < in.size(); ++i){

        cout<<i<<endl;
        for (vector<task>::iterator it = in[i].begin(); it != in[i].end(); ++it){
            cout<<setw(6)<<(*it).getCPU()<<setw(6)<<(*it).getP()<<setw(6)<<(*it).getID()<<setw(6)<<(*it).getC()<<setw(6)<<(*it).getT()<<setw(6)<<(*it).getD();
            for(int j =0; j < (*it).incomingMessageSend.size(); ++j ){
                cout<<setw(6)<<(*it).incomingMessageSend[j]->getFrom()->getID();
            }
            cout<<setw(6)<<" ";
            for(int j =0; j < (*it).incomingMessageReceive.size(); ++j ){
                cout<<setw(6)<<(*it).incomingMessageReceive[j]->getFrom()->getID();
            }
            cout<<endl<<setw(6)<<"R:"<<setw(6)<<(*it).RFixed;
            for(int j =0; j < (*it).R.size(); ++j ){
                cout<<setw(6)<<(*it).R[j];
            }
            cout<<endl<<setw(6)<<"J:"<<setw(6)<<(*it).JFixed;
            for(int j =0; j < (*it).J.size(); ++j ){
                cout<<setw(6)<<(*it).J[j];
            }
            cout<<endl;
        }
    }
    cout<<endl;
}

void display(vector<vector< message> >& in){
    cout<<"The message set is :"<<endl;
        cout<<setw(6)<<"Prio"<<setw(6)<<"ID"<<setw(6)<<"From"<<setw(6)<<"To"<<setw(6)<<"Priod"<<setw(6)<<"Size"<<endl;
    for (int i =0; i < in.size(); ++i){
        for (vector<message>::iterator it = in[i].begin(); it != in[i].end(); ++it){
            cout<<setw(6)<<(*it).getP()<<setw(6)<<(*it).getID()<<setw(6)<<(*it).getFrom()->getID()<<setw(6)<<(*it).getTo()->getID()<<setw(6)<<(*it).getT()<<setw(6)<<(*it).getSize();
            for(int j =0; j < (*it).J.size(); ++j ){
                cout<<setw(6)<<(*it).J[j];
            }
            cout<<endl;
        }
    }
    cout<<endl;
}
void display(server_conf& in){
    cout<<"The server conf is :"<<endl;
    cout<<in.slot.size()<<" slots"<<endl;
    cout<<setw(6)<<"in"<<setw(6)<<"out"<<setw(6)<<"slot"<<endl;
    for (int i =0 ; i < in.slot.size(); ++i){
        cout<<setw(6)<<in.size_in[i]<<setw(6)<<in.size_out[i]<<setw(6)<<in.slot[i]<<endl;
    }

}


void dbg_msg(  string  s){
#if DBG 
    cout<<s<<endl;
#else
    return;    
#endif    
}

void dbg_msg(  int  s){
#if DBG 
    cout<<s<<endl;
#else
    return;    
#endif    
}
