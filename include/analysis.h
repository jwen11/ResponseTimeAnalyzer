#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

#include<vector>

using namespace std;
class task;
class message;

bool taskCompare( const task& lhs, const task& rhs);
bool messageCompare( const message& lhs, const message& rhs);
int prioritize(  vector<task>& taskSet );
int prioritize(  vector<message>& messageSet );
int analysis(  vector<task>& taskSet, float& effU, float& actU );

#endif
