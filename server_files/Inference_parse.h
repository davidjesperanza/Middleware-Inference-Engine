#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Inference_parse{
     private :
        string values;
     public :
        Inference_parse();
        ~Inference_parse(){}
        void passString(string values);
        void parse_string(string values);
        void decode_Fact(int i, string temp_str);
        void print_all(vector<string> v, string name);
        int  getSize_Vector();
        vector <string>  get_Vector();
        vector <string> v_parse_str;
        int saved_value = -1;
        string name = "";
        string label = "";
};
