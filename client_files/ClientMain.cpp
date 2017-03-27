#include "common.h"


void terminate_with_error( const char* error_msg, int sock ){
	printf("%s\n", error_msg);
	perror("Socket error");
	if (sock != -1 ){ close(sock); exit(1);}
}



int main(int argc, char ** argv)
{

	if( argc == 2 ){
		//printf("Usage: ./client <server -address>\n");
		//exit(1);
	}
        else if (argc < 2 || argc > 3) {
                printf("Usage: ./client <server -address>\n");
		exit(1);
        }       
	int sock;
	struct sockaddr_in serverAddr;
	socklen_t sin_size = sizeof(struct sockaddr_in);

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("error creating socket");
		exit(1);
	}

	memset((char*) &serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9999);
	struct hostent *server = gethostbyname(argv[1]);
	
	if(server==NULL) terminate_with_error("DNE",sock);

	memcpy((char* ) &serverAddr.sin_addr.s_addr, (char*) server->h_addr, server->h_length);
	memset(&(serverAddr.sin_zero),0,8);
	
	if(connect(sock,(sockaddr *)&serverAddr,sizeof(serverAddr)) == -1) terminate_with_error("DNE",sock);
        if (argc == 3){
            string temp = "LOAD ";
            temp += argv[2];
            char input[1024];
            strcpy(input,temp.c_str());
            send(sock,input,1023,0);
        }
	while(1){
             size_t pos;
             string temp;
             string input;
             char buffer[1024];
             char in[1024];
             char q[] ="quit";
             string cmp;
             memset(buffer,0,1024);
             cout<<"CLI> ";
             getline(cin,input);
             strcpy(in,input.c_str());
             send(sock, in, 1023,0);
             recv(sock,buffer,1023,0);
             cmp = buffer;
             pos = cmp.find_first_of(".");
             temp = cmp.substr(pos+1);
             if(cmp == "quit"){
                 //cout<<"Breaking"<<endl; 
                 break;
             }
             else if( cmp == "clear"){system("clear");}
             else if( temp == "sri"){
                 cout << "File : " << cmp << " Created"<<endl;
             }
             else{
             //cout << buffer<<endl;
             }
        }
	close(sock);
}
