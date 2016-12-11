#ifndef _FILE_HANDLER_H
#define _FILE_HANDLER_H

#include <vector>
using namespace std
;
class task;

int file_read ( char* filename, vector<task>& TaskSet, bool flagP);

#endif
