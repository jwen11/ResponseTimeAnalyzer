#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

#include<vector>

using namespace std;
class task;
class message;
class server_conf;


void analysis_inMSGSet(vector<vector<message> >& inMSGSet, server_conf& configure);
void analysis_outMSGSet(vector<vector<message> >& outMSGSet, server_conf& configure);
int analysis_taskSet(vector<vector<task> >& taskSet, server_conf& configure);
int analysis(  vector<vector<task> >& taskSet,  vector<vector<message> >& inMSGSet, vector<vector<message> >& outMSGSet, server_conf& configure ,vector<float>& effU, vector<float>& actU  );

#endif
