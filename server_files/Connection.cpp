#include "Connection.h"
//Constructor: Call parent Thread Constructor
Connection::Connection(TCPSocket * p_tcpSocket): Thread()
{
 tcpSocket = p_tcpSocket; // Set the TCP socket
 next_connection = NULL; // Set the next pointer to NULL
}
// A modifier that sets the pointer of the next connection
void Connection::setNextConnection(Connection * connection){next_connection = connection;}
// A Selectot that returned a pointer to the next connection
Connection * Connection::getNextConnection (){return next_connection;}
// Destructor: delete the TCP socket if set
Connection::~Connection(){if ( tcpSocket != NULL ) delete (tcpSocket);}

void * Connection::threadMainBody (void * arg) { // Main thread body for serving the connection
   Transactions action;
   KB kb;
   RB rb;
   size_t pos;
   Inference_parse parser;
   map<string, int> commands;
   commands["quit"] = 1;
   commands["clear"] = 2;
   commands["FACT"] = 3;
   commands["RULE"] = 4;
   commands["INFERENCE"] = 5;
   commands["DROP"] = 6;
   commands["DUMP"] = 7;
   commands["LOAD"] = 8;
 int run = 1;
 while(run != 0){
 char command[1024]; // A buffer for holding the file name
 char q [] = "quit";
 string cmp;
 memset (command,0,1024); // Initialize the buffer
 int read_bytes = tcpSocket->readFromSocket(command,1023); // read from socket the file name to be fetched
 //cout << command <<endl;
 if ( read_bytes > 0) { // If read successfully
    cmp = command;
    cout << cmp<<endl;
    string word;
    string name;
    string tmp;
    vector<string> parsed_input;
    vector<string> params;
    istringstream iss(cmp);
    while(iss >> word) parsed_input.push_back(word);
    pos = cmp.find_first_of(" ");
    tmp = cmp.substr(pos +1);
    if(cmp.empty()){//Do Nothing ... Maybe
    }
    else if(commands.find(parsed_input.at(0)) == commands.end()){
        string msg = "CLI: "+cmp+" : Command Not Found\n";
        //cout << msg <<endl;
        char in[1024];
        strcpy(in,msg.c_str());
        tcpSocket->writeToSocket(in,1023);
    }
    else{
        char in[1024];
        int i = commands[parsed_input.at(0)];
        parser.passString(tmp);
        int size;
        vector<Node> myVec;
        switch(i){
            case 1:
               //Quit
               cout<<"Quit Command"<<endl;
               tcpSocket->writeToSocket(command,1023);
               tcpSocket->shutDown();
               return NULL;
            case 2:
               //CLEAR
                cout<<"Clear Command"<<endl;
		//system("clear");
                tcpSocket->writeToSocket(command,1023);
		break;
	    case 3:
		//FACT
                cout<<"Fact Command"<<endl;
		kb.passString(tmp);
                tcpSocket->writeToSocket(command,1023);
		break;
	    case 4:
		//RULE
                cout<<"RULE Command"<<endl;
		rb.passString(tmp);
                tcpSocket->writeToSocket(command,1023);
		break;
	    case 5:
		//INFERENCE
                cout<<"INFERENCE Command"<<endl;
		params = parser.get_Vector();
		size = params.size();
		//if(parser.label == ""){/*cout<< label DNE << endl; */}
		//if(parser.label != ""){/*cout<<parser.label DNE << endl;*/}
		for(unsigned int k = 0; k < params.size(); k++){
			cout << k << " : " << params[k] << endl;
		}
		name = parser.name;
		cout << size << endl;

		myVec = action.INFERENCE(kb,rb,name,size,params);	
			for(unsigned int i = 0; i < myVec.size(); i++){
				for(unsigned int j = 0; j < myVec[i].info.size(); j++){
					cout << myVec[i].info[j] << ", ";
				}
			}
                tcpSocket->writeToSocket(command,1023);
		break;
	    case 6:
		//DROP
                cout<<"Drop Command"<<endl;
		action.DROP(rb,kb,tmp);
                tcpSocket->writeToSocket(command,1023);
                break;
	    case 7:
		//DUMP
                cout<<"DUMP Command"<<endl;
		action.DUMP(rb,kb,tmp);
                strcpy(in,tmp.c_str());
                tcpSocket->writeToSocket(in,1023);
		break;
	    case 8:
                cout<<"LOAD Command"<<endl;
		action.LOAD(rb, kb, tmp);
                tcpSocket->writeToSocket(command,1023);
		break;
	}
      }
    }
  }
return NULL;
}
// Clean up file name
 /*
 if ( file_name[strlen(file_name)-1]=='\n' || file_name[strlen(file_name)-1]== '\r') file_name[strlen(file_name)-1] = 0;
 if ( file_name[strlen(file_name)-1]=='\n' || file_name[strlen(file_name)-1]=='\r') file_name[strlen(file_name)-1] = 0;
 FILE * f = fopen(file_name,"r"); // Try to open the file
 if ( f != NULL) { // If opened
 fseek (f,0,2); // Seek to the end of the file
 long fsize = ftell(f); // Get current location which represents the size
 char * buffer = (char *) calloc(fsize+1,sizeof(char)); // Allocate a buffer with the file size to read the content
 fseek (f,0,0); // Seek the beginning of the file
 fread(buffer,1,fsize,f); // Read the whole file into the buffer
 tcpSocket->writeToSocket(buffer,fsize); // Write the buffer to the socket
 free(buffer); // Free the buffer
 fclose(f); // Close the file
 }
 else {
 perror("Error With File\n"); // Print an error message
 tcpSocket->writeToSocket("Error\n",6);// Write error to the socket
 }
 }*/
