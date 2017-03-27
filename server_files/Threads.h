#ifndef THREADS_H
#define THREADS_H

#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <atomic>
#include <thread>
#include <future>

#include "RB.h"
#include "KB.h"

using namespace std;

class Threads:public RB, public KB {
private:
    //int count = 0;

public:
    Threads() {}
    ~Threads() {};
    void init_thread(KB& kb, RB& rb, int key, vector<string> send_vec, vector<string> v);
    void init_threadAND(KB& kb, RB& rb, int key, string send_vec, vector< vector<string> > v);
    virtual string search_facts3(KB kb, RB rb, string s1, unsigned int params, vector <string> v, int id);

};

#endif // THREADS_H
