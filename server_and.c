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
	//printf("the server and is up and ready\n");
	struct addrinfo UDPhints1,UDPhints; //maybe we dont need this 
	struct sockaddr_in address;
	
	socklen_t addrlen = sizeof(address);
	
	struct addrinfo *UDPservinfo1, *UDPservinfo; // this will point to the result
	char *UDPport1 = "22679"; //udp port1
	char *UDPport  = "24679"; //udp port
	
	char *IP   = "127.0.0.1"; //hardcode IP address, same ip address as in the same machine 
	
	memset(&UDPhints1, 0, sizeof UDPhints1); // make sure struct is empty
	UDPhints1.ai_family   = AF_UNSPEC; //dont care IPV4 or IPV6
	UDPhints1.ai_socktype = SOCK_DGRAM;//UDP stream sockets
	
	memset(&UDPhints, 0, sizeof UDPhints); // make sure struct is empty
	UDPhints.ai_family   = AF_UNSPEC; //dont care IPV4 or IPV6
	UDPhints.ai_socktype = SOCK_DGRAM;//UDP stream sockets

	if( ( getaddrinfo(IP,UDPport1, &UDPhints1, &UDPservinfo1)) != 0 ){
		fprintf(stderr,"getaddrinfo error for UDP port1");
		exit(1);
	}

	if( ( getaddrinfo(IP,UDPport, &UDPhints, &UDPservinfo)) != 0 ){
		fprintf(stderr,"getaddrinfo error for UDP port1");
		exit(1);
	}
	// UDP socket() part
	int UDPs1,UDPs; //socket
	UDPs1 = socket(UDPservinfo1->ai_family, UDPservinfo1->ai_socktype,UDPservinfo1->ai_protocol);
	if( UDPs1  == -1) {
		printf("error in creating one of the UDP socket\n");
		exit(1);
	}
	UDPs = socket(UDPservinfo->ai_family, UDPservinfo->ai_socktype,UDPservinfo->ai_protocol);
	if( UDPs  == -1) {
		printf("error in creating one of the UDP socket\n");
		exit(1);
	}
	int check_bind = bind(UDPs1, UDPservinfo1->ai_addr, UDPservinfo1->ai_addrlen);
	if(check_bind == -1){
		close(UDPs1);
		printf("error in binding\n");
		perror("server bind");
		exit(1);
	}
	printf("The server AND is up and running UDP on port %s\n",UDPport1);
	char buffer[256]; //buffer to read client data into
	//memset(&buffer, 0, sizeof buffer); // make sure struct is empty
	bzero(buffer,256);
	int message_len = 0;
	int flag = 0;
	int flag2 = 0;
	int line = 0;
	char order = '0'; // var to store the order information
	//UDPservinfo2->ai_addr,&UDPservinfo2->ai_addrlen
	while(1){
		//message_len = recvfrom(UDPs1,buffer,256,0,(struct sockaddr *)&address, &addrlen); 
		message_len = recvfrom(UDPs1,buffer,256,0,UDPservinfo->ai_addr,&UDPservinfo->ai_addrlen); 
		int new_flag2 = 0;
		if( message_len >  5 ){
			line = line + 1;
			//printf("this is the message from client : %s\n",buffer);
			if(flag == 0){
				printf("The Server AND start receiving lines from the edges server for AND computation.The computation results are:\n");
				flag = 1;
			}


			
			char numbuffer1[256]; //buffer to convert the order
			bzero(numbuffer1,256);
			char numbuffer11[256]; //buffer to convert the order
			bzero(numbuffer11,256);			
			
			char numbuffer2[256]; //buffer to convert the order
			bzero(numbuffer2,256);	
			char numbuffer22[256]; //buffer to convert the order
			bzero(numbuffer22,256);
				

			char numbuffer3[256]; //buffer to convert the order
			bzero(numbuffer3,256);
				
	
			int numindex1 = 0;
			int numindex2 = 0;	

			int numindex11 = 0;
			int numindex22 = 0;			



			order = buffer[0];
			int i = 0;
			int flag1 = 0;
			int flag2 = 0;
			
			unsigned num1 = 0;
			unsigned num2 = 0;
			int length1 = 0;
			int length2 = 0;
			for(i = 0; i < strlen(buffer);i++){
				if(buffer[i] == ',' && flag1 == 0){
					flag1 = 1;
					continue;
				}
				if(buffer[i] == ',' && flag1 == 1){
					flag1 = 2;
					flag2 = 1;
					continue;				
				}
				if(buffer[i] == '\n' && flag2 == 1){
					flag2 = 2;
									
				}
				if(flag1 == 1){
					if(buffer[i] == '1'){
						num1 = num1^1;
						numbuffer1[numindex1] = '1';						
					}
					else{
						num1 = num1^0;	
						numbuffer1[numindex1] = '0';				
					}
					num1 = num1<<1;
					length1 = length1 + 1;	
					numindex1 = numindex1 + 1;			
				}

				if(flag2 == 1){
					if(buffer[i] == '1'){
						num2 = num2^1;	
						numbuffer2[numindex2] = '1';						
					}
					else{
						num2 = num2^0;
						numbuffer2[numindex2] = '0';						
					}
					num2 = num2<<1;	
					length2 = length2 + 1;	
					numindex2 = numindex2 + 1;			
				}	
					
			}
			char buffer2[256]; //buffer to read client data into
			bzero(buffer2,256);
			

			//pad zero to the shorter length
			
			//flip num1 and num2 here 
			//printf("store inside the number buffer1 %s\n", numbuffer1);
			//printf("store inside the number buffer2 %s\n", numbuffer2);
			numindex1 = numindex1 - 1;
			numindex2 = numindex2 - 1;
			int flip_index = 0;
			int new_index = 0;
			num1 = 0;
			flip_index = 0;
			num2 = 0;
			new_index = 0;
			//printf("%s",numbuffer1); //1100				
	
			//pad zero to numbufer11 and numbuffer22 to make them equal size
			int bufferindex = 0;   
			bzero(numbuffer22,256); //clear to zero
			bzero(numbuffer11,256); //clear to zero
			numbuffer11[0] = order;
			numbuffer22[0] = order;
			//printf("numindex1 , numindex2 , length1, length2 %d , %d, %d,%d\n",numindex1,numindex2, length1,length2);
			if(length2 > length1){
			while(length2 > length1){
				//pad zero infront of
				
				numbuffer11[bufferindex] = '0';
				bufferindex = bufferindex + 1;
				length1 = length1 + 1; 
				//printf("padding zero %s\n",numbuffer11);
			}
			int padindex = 0;
			numindex1 = numindex1 + 1;
			numindex2 = numindex2 + 1;
			for(padindex = 0; padindex < numindex1; padindex++){
				//printf("bufferindex, padindex %d,%d \n",bufferindex,padindex);
				numbuffer11[bufferindex] = numbuffer1[padindex];
				bufferindex = bufferindex + 1;			
			}
			numbuffer11[bufferindex] = '~';
			numbuffer2[bufferindex] = '~';
			numbuffer3[bufferindex] = '~';
			int i7 = 0;
			for(i7 = 0; i7 < 256; i7++){
				numbuffer1[i7] = numbuffer11[i7];
			}
			}
			else if(length1 > length2){
				while(length1 > length2){
				//pad zero infront of
				//printf("padding zero %s\n",numbuffer11);
				numbuffer22[bufferindex] = '0';
				bufferindex = bufferindex + 1;
				length2 = length2 + 1; 
			}
			int padindex = 0;
			numindex1 = numindex1 + 1;
			numindex2 = numindex2 + 1;
			for(padindex = 0; padindex < numindex2; padindex++){
				//printf("bufferindex, padindex %d,%d \n",bufferindex,padindex);
				numbuffer22[bufferindex] = numbuffer2[padindex];
				bufferindex = bufferindex + 1;			
			}
			numbuffer22[bufferindex] = '~';
			numbuffer1[bufferindex] = '~';
			numbuffer3[bufferindex] = '~';
			int i7 = 0;
			for(i7 = 0; i7 < 256; i7++){
				numbuffer2[i7] = numbuffer22[i7];
			}
			}
			else{
			numbuffer2[numindex1+1] = '~';
			numbuffer1[numindex1+1] = '~';
			numbuffer3[numindex1+1] = '~';	
			}
			numbuffer1[255] = '\0';
			numbuffer2[255] = '\0';
			numbuffer3[255] = '\0';
			//printf("this is the padding number1 %s\n",numbuffer1);
			//printf("this is the padding number2 %s\n",numbuffer2);
			

			//calculating num3
			int k = 0;
			while(numbuffer1[k] != '~'){
				if(numbuffer1[k] == '1' && numbuffer2[k] == '1'){
					numbuffer3[k] = '1';
				}
				else{
					numbuffer3[k] = '0';
				}
				k++;
			}
			//printf("the answer is %s\n",numbuffer3);
			
			//puting result to buffer2
			buffer2[0] = order;
			int j = 0;
			int index = 1;
			int zero_flag = 0;
			//for loop to read into the first number
			for(j = 0; j < 256; j++){
				if(numbuffer1[j] == '1'){
					buffer2[index] = '1';
					index = index + 1;
					zero_flag = 1;
				}
				else if(numbuffer1[j] == '~'){
					//printf("end of the number\n");
					break;
				}
				else{
					if(zero_flag == 1){
						buffer2[index] = '0';
						index = index + 1;
					}
				}
			}
			if(zero_flag == 0){
				buffer2[index] = '0';
				index = index + 1;
			}
			//printf("buffer after first number %s\n", buffer2);
			
			j  = 0;
			zero_flag = 0;
			// or
			buffer2[index] = ' ';
			index = index + 1;
			buffer2[index] = 'a';
			index = index + 1;
			buffer2[index] = 'n';
			index = index + 1;
			buffer2[index] = 'd';
			index = index + 1;
			buffer2[index] = ' ';
			index = index + 1;
			//for the second number//
			for(j = 0; j < 256; j++){
				if(numbuffer2[j] == '1'){
					buffer2[index] = '1';
					index = index + 1;
					zero_flag = 1;
				}
				else if(numbuffer2[j] == '~'){
					//printf("end of the number\n");
					break;
				}
				else{
					if(zero_flag == 1){
						buffer2[index] = '0';
						index = index + 1;
					}
				}
			}
			if(zero_flag == 0){
				buffer2[index] = '0';
				index = index + 1;
			}
			
			j  = 0;
			zero_flag = 0;
			//for the third number
			buffer2[index] = ' ';
			index = index + 1;
			buffer2[index] = '=';
			index = index + 1;
			buffer2[index] = ' ';
			index = index + 1;
			
			for(j = 0; j < 256; j++){
				if(numbuffer3[j] == '1'){
					buffer2[index] = '1';
					index = index + 1;
					zero_flag = 1;
				}
				else if(numbuffer3[j] == '~'){
					//printf("end of the number\n");
					break;
				}
				else{
					if(zero_flag == 1){
						buffer2[index] = '0';
						index = index + 1;
					}
				}
			}
			if(zero_flag == 0){
				buffer2[index] = '0';
				index = index + 1;
			}
			
			buffer2[255] = '\0';
			
			//printf("this is the message %s\n", buffer2);
			int z = 0;
			//print out the message
			for(z = 1; z < 256; z++){
				printf("%c",buffer2[z]);
			}
			
			
			
			
			
			
			buffer2[255] = '\0';
			//printf("this is the message send back to the edge server %s\n",buffer2);
			//recvfrom(UDPs1,buffer,256,0,(struct sockaddr *)&address, &addrlen)
			sendto(UDPs1,buffer2,256,0,UDPservinfo->ai_addr,UDPservinfo->ai_addrlen);
			printf("\n");	
			//printf("message length received from edge %d  and flag2 %d\n",message_len, new_flag2);
		}
		if( message_len < 5 &&  new_flag2 == 0){
			printf("The Server AND has successfully received %d lines from the edge server and finished all AND computation.\n",line);
			printf("The Server AND has successfully finished sending all computation results to the edge server.\n");
			new_flag2 = 1;
		}

		
	}
	//printf("this is the message from client : %s\n",buffer);
	//printf("out of the while loop now\n");
	close(UDPs1);
}
