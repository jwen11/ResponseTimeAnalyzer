#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

#include<vector>

using namespace std;
class task;
class message;
class server_conf;

bool taskCompare( const task& lhs, const task& rhs);
bool messageCompare( const message& lhs, const message& rhs);
int prioritize(  vector<task>& taskSet );
int prioritize(  vector<message>& messageSet );
int analysis(  vector<vector<task> >& taskSet,  vector<vector<message> >& inMSGSet, vector<vector<message> >& outMSGSet, server_conf& configure ,vector<float>& effU, vector<float>& actU  );

#endif
