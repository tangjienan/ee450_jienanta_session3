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

//compile gcc -o edge edge.c -I.
// run   ./edge
//read 5.7

int main(int argc, char *argv[]){
	// this part is from beej
	//printf("The edge server is up and running\n");
	int status;
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);
	struct addrinfo hints; //maybe we dont need this 
	struct addrinfo *servinfo; // this will point to the result
	char *port = "23679"; //default port number, will need to change
	char *IP   = "127.0.0.1"; //hardcode IP address
	memset(&hints, 0, sizeof hints); // make sure struct is empty
	hints.ai_family   = AF_UNSPEC; //dont care IPV4 or IPV6
	hints.ai_socktype = SOCK_STREAM;//TCP stream sockets
	if( ( status = getaddrinfo(IP,port, &hints, &servinfo)) != 0 ){
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
	//finish create descriptot
	
	//TCP bind() part
	int check_bind = bind(s, servinfo->ai_addr, servinfo->ai_addrlen);
	if(check_bind == -1){
		close(s);
		printf("error in binding\n");
		perror("server bind");
		exit(1);
	}
	/* connect is for client	
	
	//TCP connect() part
	int check_connect = connect(s, servinfo->ai_addr, servinfo->ai_addrlen);
	if(check_connect == -1){
		printf("error in connect\n");
		exit(1);
	}
	*/
	
	// server listen part
	int check_Listen = listen(s,5); //number of connection allowed to queue is 5//
	if(check_Listen == -1){
		printf("error in listen\n");
		exit(1);
	}
	printf("The edge server is up and ready\n");
	//server accept part
	struct sockaddr_in client_addr; // var to store client address
	int client_len = sizeof(client_addr); // size of the client address
	int check_accept = accept(s, (struct sockaddr *)&client_addr, &client_len); // child socket
	if(check_accept == -1){
		printf("error in accept\n");
		exit(1);	
	}
	//printf("the server accept the address\n");
	
	//server recv() part
	
	
	
	
	//forward the received message to the and server and or server
	//two udp connection//
	//int UDPstatus1, UDPstatus2;
	struct addrinfo UDPhints1,UDPhints2,UDPhints; //maybe we dont need this 
	struct addrinfo *UDPservinfo1, *UDPservinfo2,*UDPservinfo; // this will point to the result
	char *UDPport  = "24679"; //edge udp port
	char *UDPport1 = "22679"; //udp port1
	char *UDPport2 = "21679"; //udp port2
	//char *IP   = "127.0.0.1"; //hardcode IP address, same ip address as in the same machine 
	memset(&UDPhints,  0, sizeof hints); // make sure struct is empty
	memset(&UDPhints1, 0, sizeof hints); // make sure struct is empty
	memset(&UDPhints2, 0, sizeof hints); // make sure struct is empty
	UDPhints.ai_family   = AF_UNSPEC; //dont care IPV4 or IPV6
	UDPhints.ai_socktype = SOCK_DGRAM;//UDP stream sockets
	UDPhints1.ai_family   = AF_UNSPEC; //dont care IPV4 or IPV6
	UDPhints1.ai_socktype = SOCK_DGRAM;//UDP stream sockets
	UDPhints2.ai_family   = AF_UNSPEC; //dont care IPV4 or IPV6
	UDPhints2.ai_socktype = SOCK_DGRAM;//UDP stream sockets
	if( ( getaddrinfo(IP,UDPport, &UDPhints, &UDPservinfo)) != 0 ){
		fprintf(stderr,"getaddrinfo error for UDP port2: %s\n", gai_strerror(status));
		exit(1);
	}
	
	if( ( getaddrinfo(IP,UDPport1, &UDPhints1, &UDPservinfo1)) != 0 ){
		fprintf(stderr,"getaddrinfo error for UDP port1: %s\n", gai_strerror(status));
		exit(1);
	}
	if( ( getaddrinfo(IP,UDPport2, &UDPhints2, &UDPservinfo2)) != 0 ){
		fprintf(stderr,"getaddrinfo error for UDP port2: %s\n", gai_strerror(status));
		exit(1);
	}
	
	// UDP socket() part
	int UDPs1, UDPs2,UDPs; //socket
	UDPs1 = socket(UDPservinfo1->ai_family, UDPservinfo1->ai_socktype,UDPservinfo1->ai_protocol);
	UDPs2 = socket(UDPservinfo2->ai_family, UDPservinfo2->ai_socktype,UDPservinfo2->ai_protocol);
	UDPs  = socket(UDPservinfo->ai_family, UDPservinfo->ai_socktype,UDPservinfo->ai_protocol);
	check_bind = bind(UDPs, UDPservinfo->ai_addr, UDPservinfo->ai_addrlen);
	if(check_bind == -1){
		printf("binding the udp port for edge server fail\n");
	}
	if( UDPs1  == -1 || UDPs2 == -1 || UDPs == -1) {
		printf("error in creating one of the UDP socket\n");
		close(UDPs1);
		close(UDPs2);
		close(UDPs);
		exit(1);
	}
	//after receiving from client, send data to backend one by one
	char buffer[256]; //buffer to read client data into
	bzero(buffer,256);
	//double buffer to store each of the return value
	char store[100][256];
	int index = 0; // index for storing to the double array
	int j = 0;
	int line_or = 0;
	int line_and = 0;
	//
	
	int check_rec = recv(check_accept, buffer,256,0);
	while(1){
	int new_flag = 0;
	while( check_rec > 5 ){
		new_flag = 1;
		//printf("this is the message from client: %s\n",buffer);
		if(buffer[1] == 'a'){
			//printf("this is and and this is the messafe %s\n", buffer);
			buffer[255] = '\0';
			int check1 = sendto(UDPs, buffer,256,0,UDPservinfo1->ai_addr,UDPservinfo1->ai_addrlen);
			if(check1 == -1){
				printf("couldn't send to the server_and\n");
			}
			char buffer1[256]; //buffer to read client data into
			bzero(buffer1,256);
			while(recvfrom(UDPs,buffer1,256,0,UDPservinfo1->ai_addr,&UDPservinfo1->ai_addrlen) < 1 ){
			}
			//printf("this is the result return by the backend server_and  %s \n" , buffer1);
			for(j  = 0; j < 256; j++){
				store[index][j]  = buffer1[j];
			}
			store[index][j] = '\0';
			line_and = line_and + 1; //line count
				
		}
		else if(buffer[1] == 'o'){
			//printf("this is or and this is the messgae %s\n",buffer);
			buffer[255] = '\0';
			sendto(UDPs, buffer,256,0,UDPservinfo2->ai_addr,UDPservinfo2->ai_addrlen);
			char buffer2[256]; //buffer to read client data into
			bzero(buffer2,256);
			while(recvfrom(UDPs,buffer2,256,0,UDPservinfo2->ai_addr,&UDPservinfo2->ai_addrlen) < 1){
			}
			//printf("this is the result return by the backend server_or  %s \n" , buffer2);
			for(j  = 0; j < 256; j++){
				store[index][j]  = buffer2[j];
				
			}
			store[index][j] = '\0';
			line_or = line_or + 1; //line count
		}
		else{
			//printf("nothing\n");
		}
		index = index + 1;
		bzero(buffer,256);
		check_rec = recv(check_accept, buffer,256,0);
		if(buffer[2] == '\0'){
			
			break;
		}
	}
	if(new_flag ==1){
	printf("The edge server has received %d lines from the client using TCP over port %s\n", line_and + line_or, port);
	printf("The edge server has successfully sent %d lines to Backend-Server OR.\n", line_or);
	printf("The edge server has successfully sent %d lines to Backend-Server AND.\n", line_and);
	//sending the buffer to indicate end of file
	char line2[3];
	line2[2] = '\0';
	sendto(UDPs, line2,3,0,UDPservinfo1->ai_addr,UDPservinfo1->ai_addrlen);
	sendto(UDPs, line2,3,0,UDPservinfo2->ai_addr,UDPservinfo2->ai_addrlen);

	printf("The edge server start receiving the computation results from Backend-Server OR and Backend-Server AND using UDP port %s\n",UDPport);
	printf("The computation results are:\n");
	
	
	//end of creating to UDP socket for edge to connect, ready to send data.
	//send to data to the two udp server
	
	
	//send data back to client 
	//loop through the store array to send it to the client in order 
	int index2 = 0;
	int cur_order = 0;
	int len, bytes_sent;
	int new_length = line_or + line_and;	
	for(cur_order = 0; cur_order < new_length; cur_order++){
		index2 = 0;
		while(store[index2][0] != (char) ((cur_order) + '!') ){		
			index2 = index2 + 1;
		}
		//this is the line we need to send back to the client
		int temp = 1;
		//printf("%s\n",store[cur_order]);
		for(temp = 1; temp < 256; temp++){
			printf("%c",store[cur_order][temp]);
		}
		printf("\n");
		bytes_sent = send(check_accept,store[cur_order],256,0);		
	}
	printf("The edge server has successfully finished receiving all computation results from the Backend-Server OR and Backend-Server AND.\n");
	printf("The edge server has successfully finished sending all computation results to the client\n");
	bytes_sent = send(check_accept,line2,3,0);	
	}//new flag 
	}
	//added while loop
	char *msg1 = "hello from the edge server"; //testing message send to client
	
	freeaddrinfo(servinfo);
	close(check_accept);
	close(UDPs);
	close(UDPs1);
	close(UDPs2);
}
