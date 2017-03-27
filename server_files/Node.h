#ifndef NODE_H
#define NODE_H
#include "common.h"


using namespace std;

class Node{
public:
    string name;
    std::vector<string> info;
    Node();
    Node(vector<string>& v, string s1);
};

#endif
