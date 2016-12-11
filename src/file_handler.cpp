
#include <string>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <iostream>
#include <fstream>

#include "../include/file_handler.h"
#include "../include/task.h"


int file_read ( char* filename, vector<task>& TaskSet, bool flagP){
    
    ifstream ifs;
    ifs.open(filename,ifstream::in);
    
    string line;
    char ch;

    unsigned int ID,P;
    float C, T, D, B;


    ch = ifs.peek();
    while (ch != EOF){
        getline (ifs, line);
        stringstream input(line);
        if (isdigit(ch)){
          if (flagP) input>>P;
          input>>ID>>C>>T;
          if (input.peek()== EOF){
            if (flagP) TaskSet.push_back(task(P,ID,C,T));
            else       TaskSet.push_back(task(ID,C,T));
          }
          else{ 
            input >>D;
            if (input.peek()== EOF){
                if (flagP) TaskSet.push_back(task(P,ID,C,T,D));
                else       TaskSet.push_back(task(ID,C,T,D));
            }
            else{
                input >>B;
                if (flagP) TaskSet.push_back(task(P,ID,C,T,D,B));
                else       TaskSet.push_back(task(ID,C,T,D,B));
            }    
          } 
        }

        ch = ifs.peek();
    }
    ifs.close();
    return 0;
}
