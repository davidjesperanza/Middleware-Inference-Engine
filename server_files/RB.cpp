/*
 * main.cpp

 *
 *  Created on: Feb 20, 2017
 *      Author: psharma5
 */
#include "RB.h"
using namespace std;

//multimap<int, Node > rulemap;
//Operator overloading to print the multimap
inline ostream & operator << (ostream & os, const vector <string> &v){
  for(const auto & i : v){
    os << i <<" ";
  }
  cout<<endl;
  return os;
}

inline ostream & operator << (ostream & os , const multimap<int,Node > &m){
  for(const auto & i : m){
    //os << i.first << " : " << endl;
    os << "RULE ";
    os << i.second.info<<endl;
  }
  return os;
}

RB::RB() {
}

void RB::passString(string o_values){
  string_map.push_back(o_values);
  parse_string(o_values);
  v_parse_str.erase(v_parse_str.begin(), v_parse_str.end());
  //cout<<"Testing Line Before "<<endl;
}
//Adds a rule to the main multimap shared by all objects
void RB::add_Rule(int o_key, Node &N, string temp_str) {
    if(status == -1) {
      cout<<"Error: Missing Operator in Rule"<<endl;
      cout<<"Unable to put values in map: "<<temp_str<<endl;

    }
    if(status == 1){
       /*for(int j=0; j<N.info.size(); j++){
             cout << N.info[j] << ", ";
       }
       cout <<endl;*/
       rulemap.insert(pair<unsigned int, Node >(o_key, N));
    }

       /*cout << o_key << endl;
       for(int j=0; j<N.info.size(); j++){
             cout << N.info[j] << ", ";
        }*/
}

//Parses the string
void RB::parse_string(string values) {
  number_of_spaces = -1;
  saved_value = -1;
  found = false;
  key = 0;
  status = 1;
  string temp_str = values;
  for(unsigned int i = 0; i < temp_str.length(); i++) {
    if(temp_str[i] == ':') {found = true;}
    if(found && temp_str[i] == ')') {number_of_spaces++;}
    if(!found && temp_str[i] == '$') {key += 1;}
    if(temp_str[i] == '(' || temp_str[i] == ')' || temp_str[i] == ':'
    || temp_str[i] == '-' || temp_str[i] == ',' || temp_str[i] == ' ') {
       decode_rule(i, temp_str);
    }
  }
  vector<string> hisVec;
  hisVec = pop_elements(key, v_parse_str);
  Node temp(hisVec,"rule");
  add_Rule(key, temp, temp_str);
}
//Adds each word in the string to a specific index inside a vector
void RB::decode_rule(int i, string temp_str) {
    v_parse_str.push_back(temp_str.substr(saved_value+1, i-(saved_value+1)));
    saved_value = i;
}
//Deletes or pops unneccessary elements from the vector
vector <string> RB::pop_elements(int key, vector<string> v_parse_str) {
   v_parse_str.erase(remove(v_parse_str.begin(), v_parse_str.end(),""), v_parse_str.end());

  //if(v_parse_str.at(key+1)

   //Print to Check values inside vector
   /*
   for(int k =0; k < v_parse_str.size(); k++) {
     cout<<k<<" "<<v_parse_str[k]<<endl;
   }
   */
   return v_parse_str;
}

//Prints the rulemap
void RB::print_values(ofstream &outputFile) {
    for(unsigned i =0; i < string_map.size();i++){
       outputFile<< "RULE "<< string_map.at(i) << endl;
    }
    //outputFile << "Rule" + <<::rulemap;
    string_map.clear();
}

void RB::search_stringmap(string temp2){
	for(unsigned int i = 0; i < string_map.size(); i++){		
		string temp = string_map.at(i);
		for(unsigned int j = 0; j < temp.length(); j++){
			if(temp[j] == '('){
				string tmp = temp.substr(0,j);
				if(tmp == temp2){
					string_map.erase(string_map.begin()+i);
					i = -1;
				}
			}
		}
	}
}


/*void RB:: print(RB &rb) {

    cout <<::rb.rulemap;
}*/

/*int main(){
 RB testobj;
    testobj.passString("Parent($X,$Y) :- OR Father($X,$Y) Mother($X,$Y)");
    testobj.print_values();
    //delete testobj;
return 0;
}*/
