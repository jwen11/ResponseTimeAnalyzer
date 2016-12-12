#include<stdio.h>
#include<cassert>
#include<iostream>

#include"../include/task.h"
using namespace std;


task::task(unsigned CPU, unsigned int ID, unsigned int C, unsigned int T){
    this->JFixed = false;
    this->RFixed = false;
    this->CPU  =  CPU;
    this->P  =  0;
    this->ID =  ID;
    this->C  = C;
    this->T  = T;
    this->D  = this->T;
    cout<<CPU<<" "<<ID<<" "<<C<<" "<<T<<endl;
    assert(C<= D);

}

task::task(unsigned CPU, unsigned int ID, unsigned int C, unsigned int T, unsigned int D){
    this->JFixed = false;
    this->RFixed = false;
    this->CPU  =  CPU;
    this->P  =  0;
    this->ID =  ID;
    this->C  = C;
    this->T  = T;
    this->D  = D;
    cout<<CPU<<" "<<ID<<" "<<C<<" "<<T<<endl;
    assert(C<= D);
    assert(D<= T);
}



task::task(unsigned CPU, unsigned int ID, unsigned int C, unsigned int T, unsigned int D, unsigned int P){
    this->JFixed = false;
    this->RFixed = false;
    this->CPU  =  CPU;
    this->P  =  P;
    this->ID =  ID;
    this->C  = C;
    this->T  = T;
    this->D  = D;
    cout<<CPU<<" "<<ID<<" "<<C<<" "<<T<<endl;
    assert(C<= D);
    assert(D<= T);
}



void task::setP(unsigned int in){
    this->P = in;
}

void task::setR(unsigned int in){
    this->R.push_back( in);
}

void task::setJ(unsigned int in){
    this->J.push_back( in);
}

unsigned int task::getP(){
        return this->P;
}
unsigned int task::getID(){
        return this->ID;
}
unsigned int task::getCPU(){
    return this->CPU;
}
unsigned int task::getC(){
    return this->C;
}
unsigned int task::getT(){
    return this->T;
}
unsigned int task::getD(){
    return this->D;
}
unsigned int task::getR(){
    return *(this->R.rbegin());
}
unsigned int task::getJ(){
    return *(this->J.rbegin());
}


bool task::IsSchedulable(){
    if (JFixed & RFixed)
        return ((this->getR()+this->getJ()) <= this->D );
    else 
        return false;
}

