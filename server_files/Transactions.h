// Transaction Header
#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include "common.h"
#include "Threads.h"
#include "Inference_parse.h"
#include "boost/filesystem.hpp"
#include <boost/filesystem.hpp>
#include <iterator>

using namespace std;
using namespace boost :: filesystem;

class Transactions:public Threads {
private:
  int status = 1;
public:
    Transactions();
    void LOAD(RB &rb , KB &kb, string file_name);
    //vector<Node> INFERENCE(KB& kb, RB& rb, string s1, int params, vector<string>& v);
    vector<Node> search_facts3(KB& kb, RB& rb, string s1, int params, vector <string>& v);
    void DUMP(RB &rb, KB &kb, string file_name);
    vector<string> temp_vec;
    vector<string> send_vec;
    vector<Node> INFERENCE(KB& kb, RB& rb, string s1, unsigned int params, vector<string> v);
    void pop_elements(KB& kb, RB& rb, int key, vector<string> v_parse_str, vector<string>, vector< vector<string> >);
    int compare_vec(vector<string> temp_vec, vector<string>::iterator str, vector<string>::iterator fin);
    void accum_iter(vector<string>::iterator rule_pred);
    //void INFERENCE2(KB& kb, string s1, int params);
    void DROP(RB &rb, KB &kb, string s1);
};

#endif /* TRANSACTIONS_H */
