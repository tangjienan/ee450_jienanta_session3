#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>


int main(int argc, char *argv[]){
	
	
	int status;
	char *port = "23679"; //default port number on server, will need to change
	char *IP   = "127.0.0.1"; //hardcoded IP address
	struct addrinfo hints; //maybe we dont need this 
	struct addrinfo *servinfo; // this will point to the result
	memset(&hints, 0, sizeof hints); // make sure struct is empty
	hints.ai_family   = AF_UNSPEC; //dont care IPV4 or IPV6
	hints.ai_socktype = SOCK_STREAM;//TCP stream sockets
	if( (status = getaddrinfo(IP,port, &hints, &servinfo)) != 0 ){
		fprintf(stderr,"getaddrinfo error: %s\n", gai_strerror(status));
		exit(1);
	}
	// servinfo has only one server information .. after checked
	
	// TCP socket() part
	int s; //socket
	s = socket(servinfo->ai_family, servinfo->ai_socktype,servinfo->ai_protocol);
	//error checking 	
	if( s  == -1) {
		printf("error in creating socket\n");
		exit(1);
	}
	//aboved part is the same as the server part
	
	//TCP client connect to the server
	int connect_check = connect(s, servinfo->ai_addr, servinfo -> ai_addrlen);
	if(connect_check == -1){
		printf("the client connection fail\n");
		exit(1);
	}
	//sending client message to server, beef 5.7
	char *msg1 = "message1"; //testing message send to server
	char *msg2 = "message2"; //testing message send to server
	int len, bytes_sent;
	len = strlen(msg1);
	//client send, then receive//


	printf("The client is up and ready\n");
	//reading from the file input 
	// reading the file and send the corresponding message to different backend server
	//char * fileName = "job.txt";
	char * fileName = argv[1];
	FILE * file = fopen(fileName,"r");
	char line[256];
	int index = 0;
	int i = 1;	
	int num_line = 0;
	while(fgets(line,sizeof(line),file)){
		//printf("%s",line);
		//append index infront of each line
		i = 254;
		for(i = 254; i  >= 0; i--){
			line[i+1] = line[i];			
		}
		line[0] = (char)index + '!';
		index = index + 1;
		//printf("this is the new string %s\n", line);
		if(line[1] == 'a'){
			//printf("this is and\n");
			//line[255] = '\0';
			bytes_sent = send(s,line,256,0);
		}
		else if(line[1] == 'o'){
			//printf("this is or\n");
			//line[255] = '\0';
			bytes_sent = send(s,line,256,0);
		}
		else{
		}
		num_line = num_line + 1;	
			//printf("nothing\n");
	}
	char line2[3];
	line2[2] = '\0';
	//printf("sending the ending message\n");
	bytes_sent = send(s,line2,3,0);
	fclose(file);
	//finish reading file

	printf("The client has successfully finished sending %d lines to the edge server.\n", num_line);
	printf("The client has successfully finished receiving all computation results from the edge server.\n");

 

	
	//bytes_sent = send(s,msg1,len,0);
	if(bytes_sent == -1){
		printf("client sending error\n");
		exit(1);
	}
	//receive return data from the edge server 
	printf("The final computation results are:  \n");
	while(1){
		//printf("printing the output in order\n");
		char buffer[256];
	//memset(&buffer, 0, sizeof buffer); // make sure struct is empty
		bzero(buffer,256);
		int check_recv = recv(s,buffer,256,0);
		//loop through the return output, print out everything after '=' 
		int index = 0;
		int flag  = 0;
		//printf("the client received result %s\n",buffer);
		for(index = 0; index < 256; index++){
			if(buffer[index] == '=' && index != 0){
				flag =1;
				continue;			
			}
			if(flag == 1){
				flag = 2;
				continue;			
			}
			if(flag == 2){
				printf("%c",buffer[index]);
			}
		}
		printf("\n");
		if(check_recv <= 5){

			//printf("error in receiving in client side\n");
			break;
		}
	}
	close(s);
	return 0;
}








	
