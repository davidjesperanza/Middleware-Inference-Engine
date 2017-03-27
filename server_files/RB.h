#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include "Node.h"
using namespace std;

class RB : public virtual Node{
    private:
        int key = 0;
        string values;
        int status = 1;
        int number_of_spaces = -1;
    public:
	vector <string> string_map;
        RB();
        ~RB() {}
        void add_Rule(int o_key,Node &N, string temp_str);
        void passString(string o_values);
        void parse_string(string values);
        void decode_rule(int i,string temp_str);
        vector<string> pop_elements(int key,vector<string> v_parse_str);
        void print_values(ofstream &outputFile);
        void print(RB &rb);
        vector<string> v_parse_str;
        int saved_value = -1;
        bool found = false;
        multimap<unsigned int, Node > rulemap;
	void search_stringmap(string temp2);


};
