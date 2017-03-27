#include "KB.h"
using namespace std;

//multimap< int, Node > factmap;


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
    os << i.second.info<<endl;
  }
  return os;
}

//Constructor
KB ::KB(){
}

void KB::passString(string o_values){
    stringmap.push_back(o_values);
    parse_string(o_values);
    v_parse_str.erase(v_parse_str.begin(), v_parse_str.end());
    saved_value = -1;
    key = 0;
}

//Adds the fact to the multimap
void KB::add_Fact(int o_key, Node &N ) {
    /*for(int j=0; j<N.info.size(); j++){
             cout << N.info[j] << ", ";
    }cout<<endl;*/
    factmap.insert(pair<int, Node >(o_key, N));
}
//Parses the string passed as the parameter
void KB::parse_string(string values){
  string temp_str = values;
  //cout << temp_str<< endl;
  for(unsigned int i = 0; i < temp_str.length(); i++) {
    if(temp_str[i] == ',') {key += 1;}
    if(temp_str[i] == '(' || temp_str[i] == ')' || temp_str[i] == ',' || temp_str[i] == ' ') {
       decode_Fact(i, temp_str);
    }
  }
  for(unsigned int k =0; k < v_parse_str.size(); k++) {
    //cout<<k<<" "<<v_parse_str[k]<<endl;
  }
  Node temp(v_parse_str,"fact");
  add_Fact(++key, temp);//++key
}
//Splits the fact into individual words and adds them to indices in the vector
void KB::decode_Fact(int i, string temp_str) {
    //cout<<v_parse_str<<endl;
    v_parse_str.push_back(temp_str.substr(saved_value+1, i-(saved_value+1)));
    saved_value = i;
}
//Prints the multimap
void KB:: print_values(ofstream &outputFile) {
    for(unsigned i =0; i < stringmap.size();i++){
       outputFile<< "FACT "<< stringmap.at(i) << endl;
    }
    stringmap.clear();
}

void KB::search_stringmap(string temp2){
	for(unsigned int i = 0; i < stringmap.size(); i++){
		cout<<"Iteration : "<< i<<endl;		
		string temp = stringmap.at(i);
		for(unsigned int j = 0; j < temp.length(); j++){
			if(temp[j] == '('){
				string tmp = temp.substr(0,j);
				if(tmp == temp2){
					stringmap.erase(stringmap.begin()+i);
					i = -1;
				}
			}
		}
	}
}

/*void KB:: print(KB &kb) {

    cout <<::kb.factmap;
}*/

/*int main() {
    KB testobj;
    testobj.passString("Father(John,Hanniabl)");
    testobj.print_values();
    //delete testobj;

return 0;

}*/
