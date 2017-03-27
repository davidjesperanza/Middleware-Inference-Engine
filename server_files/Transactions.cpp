// Transactions CPP
#include "Transactions.h"

std::multimap<unsigned int, vector<Node> > tempMap;
int globalcount = 0;
extern mutex mtx;
int globalflag;
int globalAND;
vector<string> extrarules;
Transactions::Transactions(){
}

//Loads Facts and Rules  into KB and RB
void Transactions::LOAD(RB &rb , KB &kb, string file_name){
  Inference_parse parser2;
  ifstream input_file;
  string line_of_file;
  vector<string> file_input;
  size_t pos;
  string tmp;
  map<string, int> commands;
   commands["quit"] = 1;
   commands["clear"] = 2;
   commands["FACT"] = 3;
   commands["RULE"] = 4;
   commands["INFERENCE"] = 5;
   commands["DROP"] = 6;
   commands["DUMP"] = 7;
   commands["LOAD"] = 8;
  if(exists(file_name)){
    //File Found
    input_file.open(file_name);
    if(input_file.fail()){ cout << "Cannot Open File\n" << endl;}
    else{
      while(getline(input_file,line_of_file)){
        vector <string > params;
        string word;
        string name;
        istringstream iss(line_of_file);
        while(iss >> word) file_input.push_back(word);
        pos = line_of_file.find_first_of(" ");
        tmp = line_of_file.substr(pos+1);
        if(commands.find(file_input.at(0)) == commands.end()){cout << "Command Not Found - Transactions - Load -" << endl;/*Command Not Found*/}
        else{
          int size;
          vector<Node> myVec;
          int n = commands[file_input.at(0)];
          switch(n){
            case 3 :
                   //cout << "FACT COMMAND\n";
                   kb.passString(tmp);
                   break;
            case 4 :
                   //cout << "Rule COMMAND\n";
                   rb.passString(tmp);
                   break;
            case 5 :
                   parser2.passString(tmp);
                   //cout << "Inference COMMAND\n";
                   params = parser2.get_Vector();
                   if(parser2.label == ""){/*cout<<"\nNo Label Exists"<<endl;*/}
                   if(parser2.label != ""){/*cout << "\nLabel : "<< parser2.label << endl;*/}
                   //for(int k = 0; k <params.size();k++){
                      //cout << k << " : " << params[k] <<endl;
                   //}
                   name = parser2.name;
                   size = params.size();
                   myVec = INFERENCE(kb,rb,name,size,params);
                   tempMap.clear();
                   //cout<< myVec.size();
                   for(unsigned int i=0; i<myVec.size(); i++){
                      for(unsigned int j=0; j<myVec[i].info.size(); j++){
                        cout << myVec[i].info[j] << ", ";
                      }
                   }cout <<endl;
                   /*
                   for (std::multimap<unsigned int, vector<Node> >::iterator it=tempMap.begin(); it!=tempMap.end();++it){
                        cout << "Map Index: " << it->first << endl;
                        for(unsigned int j=0; j<it->second.size(); j++){
                             for(int i=0; i< it->second[j].info[i].size(); i++){
                             cout << it->second[j].info[i] << endl;
                             }
                         }
                   }*/
                   break;
            case 6 :
                   //cout << "DROP Command\n";
		   DROP(rb,kb,tmp);
                   break;
            case 7 :
                   //cout << "DUMP Command\n";
                   DUMP(rb,kb,tmp);
                   break;
            case 8 :
                   cout << "LOAD Command\n";
                   LOAD(rb,kb, tmp);
                   break;
          }
        }
       file_input.clear();
       //cout<<"File Vector Cleared "<<endl;
      }
    input_file.close();
    //cout<<"File Parsed Done " <<endl;
    }

  }
  else{
    cout << "File : " << file_name << "Does Not Exist\n" << endl;
  }

}

void Transactions::DUMP(RB &rb, KB &kb, string file){
    ofstream file_name;
    file_name.open(file);
    rb.print_values(file_name);
    kb.print_values(file_name);
    file_name.close();
}

void Transactions::DROP(RB &rb, KB &kb, string s1){
	rb.search_stringmap(s1);
	kb.search_stringmap(s1);
}

vector<Node> Transactions::INFERENCE(KB& kb, RB& rb, string s1, unsigned int params, vector<string> v){
    //cout<<"testing"<<endl;
    std::vector<Node> temp;
    std::vector<Node> temp2;
    std::vector<Node> temp3;
    vector< vector<string> > empty;
    bool found = false;
    globalflag = 0;
    for (std::multimap<unsigned int, Node>::iterator it=rb.rulemap.begin();
            it!=rb.rulemap.end();++it){ //loops through map
        if(it->second.info[1+params] == "AND" && it->first == params && it->second.info[0] == s1){ //if right rule is found
            //AND = true;
            found = true;
            vector<Node> someVec;
            vector<Node> classyVec;
            vector<Node> toomuchVec;
            vector<string> strVec;
            vector< vector<string> > holder;
            unsigned int x=2+params;
            //unsigned int counter = 3+params; //what does this do?
            for(unsigned int y=x+params+1; y<it->second.info.size(); y+=params+1){ //this will loop through the rule
                for(unsigned int j=0; j<v.size(); j++){ //pushes v into temporary strVec
                    strVec.push_back(v[j]);
                }
                if(x==2+params){ //return all facts if its the first fact/rule
                    globalAND = x;
                    pop_elements(kb, rb, params, it->second.info, v, empty); //puts all first facts into tempMap
                    //someVec = ANDINFERENCE3(kb, rb, it->second.info[x], params, strVec);
                    for (std::multimap<unsigned int, vector<Node> >::iterator it=tempMap.begin();
                    it!=tempMap.end();++it){ //put tempMap into someVec then clear(need to make sure this works)
                        someVec = it->second;
                    }
                    tempMap.clear();
                    globalAND+=(params+1);
                }else{//this is for 3+ facts/rules
                    globalAND+=(params+1);
                    for (std::multimap<unsigned int, vector<Node> >::iterator it=tempMap.begin();
                    it!=tempMap.end();++it){ //put map into a vec and return that
                        classyVec = it->second;
                        cout << it->first << endl;
                        for(unsigned int j=0; j<someVec.size(); j++){
                            someVec.push_back(classyVec[j]);
                        }
                    }
                    tempMap.clear();
                }
                for(unsigned int j=y+1; j<y+1+params; j++){
                for(unsigned int i=x+1; i<x+1+params; i++){
                    if(it->second.info[i] == it->second.info[j]){ // checks for a hit
                        for(unsigned int k=0; k<someVec.size(); k++){ //loops through someVec
                            strVec[j-y-1] = someVec[k].info[i-x];
                            //classyVec = INFERENCE(kb, rb, it->second.info[y], params, strVec);
                            holder.push_back(strVec);
                        }
                    }
                }
                }
                pop_elements(kb, rb, params, it->second.info, v, holder);
                someVec.clear();
                strVec.clear();
                //holder.clear();
                x+=params+1;
            }

            for (std::multimap<unsigned int, vector<Node> >::iterator it=tempMap.begin();
                it!=tempMap.end();++it){ //put map into a vec and return that
                someVec = it->second;
                
                for(unsigned int j=0; j<someVec.size(); j++){
                    toomuchVec.push_back(someVec[j]);
                }
                someVec.clear();
            }
            return toomuchVec;
        }else{
        if(it->first == params && it->second.info[0] == s1){ //if the right rule is found
            found = true;
            pop_elements(kb, rb, params, it->second.info, v, empty);
            //for(int i=2+params; i<it->second.info.size(); i+=(params+1)){//loops through info
                //search_facts3(kb, rb, it->second.info[i], params, v); // father, 2

            //}
            if(globalflag == 0){//if there is a nested rule
                //cout << "Here"<<endl;
                /*for(int i = 0; i <extrarules.size(); i++){
                    cout<< extrarules[i] <<endl;
                }*/
                for(unsigned int i=0; i<extrarules.size(); i++){
                    temp = INFERENCE(kb, rb, extrarules[i], params, v);
                    for(unsigned int j=0; j<temp.size(); j++){
                        temp2.push_back(temp[j]);
                    }
                    temp.clear();
                }
            } else{
            //cout <<" Here "<<endl;
            for (std::multimap<unsigned int, vector<Node> >::iterator it=tempMap.begin();
                it!=tempMap.end();++it){ //put map into a vec and return that
                temp = it->second;
                /*for(int i = 0; i<temp.size(); i++){
                   for(int j = 0; j <temp[i].info.size();j++){
                      cout<< temp[i].info[j]<<endl;
                   }
                }*/
                for(unsigned int j=0; j<temp.size(); j++){
                    temp2.push_back(temp[j]);
                }
                temp.clear();
            }
            }
        }
        }
    }
    if(found == false){//if query is on a fact and not a rule
        //search_facts3(kb, rb, s1, params, v); //wont work as of now
        vector<string> myTempy;
        myTempy.push_back(s1);
        Threads::init_thread(kb, rb, params, myTempy, v);
        for (std::multimap<unsigned int, vector<Node> >::iterator it=tempMap.begin();
                it!=tempMap.end();++it){
            temp = it->second;
            for(unsigned int j=0; j<temp.size(); j++){
                temp2.push_back(temp[j]);
            }
            temp.clear();
        }
    }
    return temp2;
}

string Threads::search_facts3(KB kb, RB rb, string s1, unsigned int params, vector <string> v, int id) { // changed Trans to Thread
    mtx.lock();
    cout<<"Thread Index: "<<id<<": "<<this_thread::get_id()<<endl;
    std::vector<Node> temp;
    std::vector<Node> temp2;
    globalflag = 0;
    for (std::multimap<unsigned int, Node>::iterator it=kb.factmap.begin(); it!=kb.factmap.end(); ++it) {
      // puts all facts that align with s1 and params in temp vec
        if(it->first == params && it->second.info[0] == s1){ //checks type of fact and number of parameters
            globalflag++;
            temp.push_back(it->second); //pushes fact into temp vec
        }
    }
    bool myB;
    //this code is for filtering
    for(unsigned int j=0; j<temp.size(); j++){ //loops through temp vector
        unsigned int count = 0;
        for(unsigned int i=0; i<v.size(); i++){ //loops through parameter vector
            string str = v[i];
            if(str[0] == '$'){
                count++;
            }else{
                if(temp[j].info[i+1] == str){
                    myB = true;
                }else{
                    myB = false;
                }
            }
        }
        if(count == v.size()){ myB = true; }
        if(myB == true){ temp2.push_back(temp[j]); }
    }
    if(globalflag == 0){//if fact is not found and it is a rule(may not find fact or rule)
        //globalflag = 1;
        extrarules.push_back(s1);
    }else{//do i need this else?
    tempMap.insert(std::pair<int, vector<Node> >(globalcount, temp2));
    globalcount++;
    }
    return s1;
}

void Transactions::pop_elements(KB& kb, RB& rb, int key, vector<string> v_parse_str, vector<string> v,
    vector< vector<string> > holder) {
    int result = 1; //to check the validity of the parameters passed
    if(!(v_parse_str.at(1+key) == "OR" || v_parse_str.at(1+key) == "AND")) { //Checking the existence of an operator
        status = -1;
    }
    if(v_parse_str.at(1+key) == "OR") { //Adds the parameters to be compared in a temporary vector
        for(int i = 0; i < key; i++) {
        temp_vec.push_back(v_parse_str[i+1]);
    }
    for(vector<string>::iterator l = v_parse_str.begin() + key + 2; l != v_parse_str.end(); l+=(key+1)) {
        result = compare_vec(temp_vec, l+1,l+1+key);
        if(result == -1) continue;
        else {
         accum_iter(l);
        }
    }
    temp_vec.clear();
    Threads::init_thread(kb, rb, key, send_vec, v);
    send_vec.clear();
    }
       else if(v_parse_str.at(1+key) == "AND") {
        if(globalAND == key+2){
            send_vec.push_back(v_parse_str[globalAND]);
            Threads::init_thread(kb, rb, key, send_vec, v);
            send_vec.clear();
        }else{
            Threads::init_threadAND(kb, rb, key, v_parse_str[globalAND], holder);
        }
    }
}

int Transactions::compare_vec(vector<string> temp_vec, vector<string>::iterator str, vector<string>::iterator fin){
  int count = 0;
    for(vector<string>::iterator it = str; it != fin; it++, count++) {
      if(temp_vec[count] != *it) return -1;
    }
    return 1;
}

 void Transactions::accum_iter(vector<string>::iterator rule_pred) {
   send_vec.push_back(*rule_pred);
 }
/*
vector<Node> Transactions::INFERENCE(KB& kb, RB& rb, string s1, int params,
        vector <string>& v){
    std::vector<Node> temp;
    std::vector<Node> temp2;
    bool found;

    for (std::multimap<int, Node>::iterator it=rb.rulemap.begin();
            it!=rb.rulemap.end();++it){ //loops through map
        if(it->second.info[1] == "AND" && it->first == params && it->second.info[0] == s1){
            found = true;
            vector<Node> someVec;
            vector<Node> classyVec;
            vector<Node> toomuchVec;
           unsigned  int x=2;
           unsigned  int y=x+params+1;
            for(unsigned int j=y+1; j<y+1+params; j++){
                for(unsigned int i=x+1; i<x+1+params; i++){
                    if(it->second.info[i] == it->second.info[j]){ // j=7, i=5
                        someVec = INFERENCE(kb, rb, it->second.info[x], params, v);
                        for(unsigned int k=0; k<someVec.size(); k++){
                            v[j-(params+4)] = someVec[k].info[i-(params-1)];
                            classyVec = INFERENCE(kb, rb, it->second.info[y], params, v);
                            for(unsigned int j=0; j<classyVec.size(); j++){
                                toomuchVec.push_back(classyVec[j]);
                            }
                            classyVec.clear();
                        }
                    }
                }
            }
            return toomuchVec;
        }else{
        //newparam = params;
        if(it->first == params && it->second.info[0] == s1){ //if the right rule is found
            found = true;
            for(unsigned  int i=2; i<it->second.info.size(); i++){//loops through info
                temp = search_facts3(kb, rb, it->second.info[i], params, v); // father, 2
                for(unsigned int j=0; j<temp.size(); j++){
                    temp2.push_back(temp[j]);
                }
                temp.clear();
            }
        }
        }
    }
    if(found == false){
        temp2 = search_facts3(kb, rb, s1, params, v);
    }
    return temp2;
}


vector<Node> Transactions::search_facts3(KB& kb, RB& rb, string s1, int params, vector <string>& v){ // father, 2
    std::vector<Node> temp;
    std::vector<Node> temp2;
    int flag = 0;
    for (std::multimap<int, Node>::iterator it=kb.factmap.begin();
            it!=kb.factmap.end();++it){ // puts all facts that align with s1 and params in temp vec
        if(it->first == params && it->second.info[0] == s1){ //checks type of fact and number of parameters
            flag++;
            temp.push_back(it->second); //pushes fact into temp vec
        }
    }
    bool myB;
    for(unsigned int j=0; j<temp.size(); j++){ //loops through temp vector
       unsigned int count = 0;
        for(unsigned int i=0; i<v.size(); i++){ //loops through parameter vector
            string str = v[i];
            if(str[0] == '$'){
                count++;
            }else{
                if(temp[j].info[i+1] == str){
                    myB = true;
                }else{
                    myB = false;
                }
            }
        }
        if(count == v.size()){ myB = true; }
        if(myB == true){ temp2.push_back(temp[j]); }
    }
    if(flag == 0){ temp2 = INFERENCE(kb, rb, s1, params, v); }//return false;
    return temp2;
}
*/


/*int main(){
   KB kb;
   RB rb;
   Transactions test;
   test.LOAD(rb,kb,"input.sri");
   //cout <<"KB\n";
   //kb.print();
   //cout <<"RB\n";
   //rb.print();
   test.DUMP(rb,kb,"dump_test.sri");

 return 0;
}*/
