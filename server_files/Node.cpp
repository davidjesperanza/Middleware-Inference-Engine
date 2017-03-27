#include "Node.h"
Node::Node(){
    
}

Node::Node(vector<string>& v, string s1){
    name = s1;
    for(unsigned int i=0; i<v.size(); i++){
        info.push_back(v[i]);
    }
}












