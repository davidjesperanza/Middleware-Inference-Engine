#include "Threads.h"

mutex mtx;

void Threads::init_thread(KB& kb, RB& rb, int key, vector<string> send_vec, vector<string> v) {
    vector<future<string>> futureObj;
    for(int i = 0; i < send_vec.size(); i++) //launches threads
        futureObj.push_back(async(launch::async, &Threads::search_facts3, this, kb, rb, send_vec[i], key, v, i));
    for (auto& fut : futureObj){
        auto x = fut.get();
	mtx.unlock();
        cout<< x <<endl;
    }
 }

void Threads::init_threadAND(KB& kb, RB& rb, int key, string send_vec, vector< vector<string> > v) {
    vector<future<string>> futureObj;
    for(int i = 0; i < v.size(); i++) //launches threads
        futureObj.push_back(async(launch::async, &Threads::search_facts3, this, kb, rb, send_vec, key, v[i], i));
    for (auto& fut : futureObj){
        auto x = fut.get();
	mtx.unlock();
        cout<< x <<endl;
    }
 }
