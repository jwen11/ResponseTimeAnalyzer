#ifndef _FILE_HANDLER_H
#define _FILE_HANDLER_H

#include <vector>
using namespace std;

class task;
class message;
class server_conf;

int task_read ( char* filename, vector<vector<task> > & TaskSet, server_conf& configure);
int message_read ( char* filename, vector<vector<task> >& TaskSet, vector<vector<message> >& inMSGSet, vector<vector<message> >& outMSGSet);

int configure_read(char* filename, server_conf& configure);

bool taskCompare( const task& lhs, const task& rhs);
bool messageCompare( const message& lhs, const message& rhs);
int prioritize(  vector<task>& taskSet );
int prioritize(  vector<message>& messageSet );
#endif
