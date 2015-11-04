#include <stdio.h>

#include <string>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

#include "../include/task.h"

using namespace std;


int main(int argc, char** argv){
    if (argc != 2) {
        cout<<"[usage]: ./analyse <file in>"<<endl;
    }
    unsigned int numTasks = 0;
    ifstream ifs;
    ifs.open(argv[1],ifstream::in);
    
    string line;
    char ch;

    unsigned int ID;
    float C, T, D, B;
    vector <task> task_set;


    ch = ifs.peek();
    while (ch != EOF){
        getline (ifs, line);
        cout<<line<<endl;
        stringstream input(line);
        if (isdigit(ch)){
          input>>ID>>C>>T;
          if (input.peek()== EOF){
            task_set.push_back(task(ID,C,T));
          }
          else{ 
            input >>D;
            if (input.peek()== EOF){
             task_set.push_back(task(ID,C,T,D));
            }
            else{
                input >>B;
                task_set.push_back(task(ID,C,T,D,B));
            }    
          } 
        }

        ch = ifs.peek();
    }

    cout<<"The task set is :"<<endl;
    for (vector<task>::iterator it = task_set.begin(); it != task_set.end(); ++it){
        cout<<setw(5)<<it->getID()<<setw(5)<<it->getC()<<setw(5)<<it->getT()<<setw(5)<<it->getD()<<setw(5)<<it->getB()<<endl;
    }

return 0;

}
