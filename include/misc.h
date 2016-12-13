#ifndef _MISC_H_
#define _MISC_H_

#include<string>
#include<vector>
using namespace std;

class task;
class message;
class server_conf;

void display(vector<vector< task> >& in);
void display(vector<vector< message> >& in);
void display(server_conf& in);
void dbg_msg( string   s);
void dbg_msg( int   s);


#else
#endif
