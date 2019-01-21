/************* UDP CLIENT CODE *******************/

#include "general.h"


int main(){
  int clientSocket, portNum, nBytes;
  char buffer[1024];
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

  while(1){

  	message msg;

  	/* escrever mensagem a enviar em baixo */

  	msg.APos.lat = 0;
	msg.APos.lon = 0;
	msg.Apos.alt = 0;
	msg.mb.im = 0;
	msg.mb.om = 0;
	msg.mb.mm = 0;
    
    /*Send message to server*/
    sendto(clientSocket,msg,sizeof(message),0,(struct sockaddr *)&serverAddr,addr_size);


  }

  return 0;
}