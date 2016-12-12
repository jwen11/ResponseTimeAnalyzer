#include<stdio.h>
#include<cassert>

#include"../include/message.h"
using namespace std;





message::message(unsigned int ID,task* from ,task* to, unsigned int T, unsigned int Size,unsigned int P ){
    this->P  =  P;
    this->ID =  ID;
    this->T     = T;   
    this->Size  = Size;

    this->from  = from;
    this->to    = to;

    this->JFixed = false;

    assert(from != to);
}




unsigned int message::getP(){
        return this->P;
}
unsigned int message::getID(){
        return this->ID;
}
unsigned int message::getT(){
    return this->T;
}
unsigned int message::getSize(){
    return this->Size;
}
task* message::getFrom(){
    return this->from;
}
task* message::getTo(){
    return this->to;
}

unsigned int message::getJ(){
    return *(this->J.rbegin());
}


void message::setP(unsigned int in){
    this->P = in;
}

void message::setJ(unsigned int in){
    this->J.push_back( in);
}


