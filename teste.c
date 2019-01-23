/************* UDP CLIENT CODE *******************/
// gcc -g -Wall -std=gnu99 -pedantic -o teste teste.c -lm -lrt -lpthread

#include "general.h"


int main(){
	int clientSocket;
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	/*Create UDP socket*/

	clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

	/*Configure settings in address struct*/
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(B_PORT);
	serverAddr.sin_addr.s_addr = inet_addr(B_ADDRESS);
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
	/*Initialize size variable to be used later on*/
	addr_size = sizeof serverAddr;

	char info[] = "38.755616,-9.148965,99,100,100,10,0,10,10,0,0,1";
	/* tamanho da string a receber 48 posições*/
	/* escrever mensagem a enviar em baixo */
	/*Send message to server*/
	sendto(clientSocket,&info,(sizeof(char)*100),0,(struct sockaddr *)&serverAddr,addr_size);

	close(clientSocket);
	return 0;
}