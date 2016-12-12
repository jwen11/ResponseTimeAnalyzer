#ifndef _CONF_H_
#define _CONF_H_

#include <string>
#include <vector>
using namespace std;

class server_conf{
public:
    vector<unsigned int> size_in;
    vector<unsigned int> size_out;
    vector<unsigned int> slot;
    unsigned int T;

};

#endif
