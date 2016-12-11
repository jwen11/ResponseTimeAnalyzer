#include<stdio.h>
#include<cassert>

#include"../include/task.h"
using namespace std;


task::task(unsigned int ID, float C, float T){
    this->P  =  1;
    this->ID =  ID;
    this->C  = C;
    this->T  = T;
    this->D  = this->T;
    this->B  = 0;
    this->R  = this->T +1;
    assert(C<= D);

}

task::task(unsigned int ID, float C, float T, float D){
    this->P  =  1;
    this->ID =  ID;
    this->C  = C;
    this->T  = T;
    this->D  = D;
    this->B  = 0;
    this->R  = this->T +1;
    assert(C<= D);
    assert(D<= T);
}

task::task(unsigned int ID, float C, float T, float D, float B){
    this->P  =  1;
    this->ID =  ID;
    this->C  = C;
    this->T  = T;
    this->D  = D;
    this->B  = B;
    this->R  = this->T +1;
    assert(C<= D);
    assert(D<= T);
}

task::task(unsigned int P,unsigned int ID, float C, float T){
    this->P  =  P;
    this->ID =  ID;
    this->C  = C;
    this->T  = T;
    this->D  = this->T;
    this->B  = 0;
    this->R  = this->T +1;
    assert(C<= D);

}

task::task(unsigned int P,unsigned int ID, float C, float T, float D){
    this->P  =  P;
    this->ID =  ID;
    this->C  = C;
    this->T  = T;
    this->D  = D;
    this->B  = 0;
    this->R  = this->T +1;
    assert(C<= D);
    assert(D<= T);
}

task::task(unsigned int P,unsigned int ID, float C, float T, float D, float B){
    this->P  =  P;
    this->ID =  ID;
    this->C  = C;
    this->T  = T;
    this->D  = D;
    this->B  = B;
    this->R  = this->T +1;
    assert(C<= D);
    assert(D<= T);
}

//void task::setC(float in){
//    this->C = in;
//}
//void task::setT(float in){
//    this->T = in;
//}
//void task::setB(float in){
//    this->B = in;
//}
//void task::setD(float in){
//    this->D = in;
//}

void task::setP(unsigned int in){
    this->P = in;
}
void task::setR(float in){
    this->R = in;
}

unsigned int task::getP(){
        return this->P;
}
unsigned int task::getID(){
        return this->ID;
}
float task::getC(){
    return this->C;
}
float task::getT(){
    return this->T;
}
float task::getD(){
    return this->D;
}
float task::getB(){
    return this->B;
}
float task::getR(){
    return this->R;
}


bool task::IsSchedulable(){
    return this->R <= this->D;
}

