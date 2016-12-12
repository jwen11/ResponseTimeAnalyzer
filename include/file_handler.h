#ifndef _FILE_HANDLER_H
#define _FILE_HANDLER_H

#include <vector>
using namespace std;

class task;
class message;
class server_conf;

int task_read ( char* filename, vector<vector<task> > & TaskSet);
int message_read ( char* filename, vector<vector<task> >& TaskSet, vector<vector<message> >& inMSGSet, vector<vector<message> >& outMSGSet);

int configure_read(char* filename, server_conf& configure);
#endif
