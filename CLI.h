/*
 * Author: Chen Shtar 318731411 & Lidor Ovadia 204268114
 */

#ifndef CLI_H_
#define CLI_H_

#include <string.h>
#include "commands.h"
#include <vector>
#include <algorithm>

using namespace std;

class CLI {
    DefaultIO* dio;
    vector<Command*> commands;
public:
    CLI(DefaultIO* dio);
    void start();
    virtual ~CLI();
};

#endif /* CLI_H_ */