#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

#include<vector>

using namespace std;
class task;

bool taskCompare( const task& lhs, const task& rhs);
int prioritize(  vector<task>& TaskSet, bool flagP);
int analysis(  vector<task>& TaskSet, float& effU, float& actU );

#endif
