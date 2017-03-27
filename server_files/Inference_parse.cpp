/*
 * main.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: psharma5
 */
#include "Inference_parse.h"
size_t pos2;
using namespace std;
//Constructor
Inference_parse::Inference_parse(){
}

void Inference_parse::passString(string values) {
    v_parse_str.erase(v_parse_str.begin(), v_parse_str.end());
    parse_string(values);
}

//Parses the string passed as the parameter
void Inference_parse::parse_string(string values) {
  saved_value = -1;
  string temp_str = values;
  for(unsigned int i = 0; i < temp_str.length(); i++) {
    if(temp_str[i] == '(' || temp_str[i] == ')' || temp_str[i] == ',' || temp_str[i] == ' ') {
       decode_Fact(i, temp_str);
    }
  }
  print_all(v_parse_str, name);
}
//Splits the fact into individual words and adds them to indices in the vector
void Inference_parse::decode_Fact(int i, string temp_str) {
    if(temp_str[i] == '(') {
         name = temp_str.substr(saved_value+1, i-(saved_value+1));
    }
    if((temp_str[i] == ' ') && (temp_str[i-1] == ')')){
      //cout<< saved_value<< endl;
      //cout<< temp_str.substr(saved_value+1, i+(saved_value+1)) << endl;
      label = temp_str.substr(saved_value+1, i+(saved_value+1));
      pos2 = label.find(" ");
      label = label.substr(pos2+1);
      //cout << label << endl;
    }
    else if(!(temp_str[i] == '(')) {
    v_parse_str.push_back(temp_str.substr(saved_value+1, i-(saved_value+1)));
    }
    saved_value = i;
}

void Inference_parse::print_all(vector<string> v_parse_str, string name) {
  //cout<<"String Name: "<<name<<endl;
  for(unsigned int k =0; k < v_parse_str.size(); k++) {
    //cout<<k<<" "<<v_parse_str[k]<<endl;
  }
}

int Inference_parse::getSize_Vector(){
    return v_parse_str.size();
}

vector <string> Inference_parse::get_Vector(){
       return v_parse_str;
}
