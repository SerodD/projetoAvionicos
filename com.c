/*-------------------------------------------------------
	Instituto Superior Técnico - 1st Semester 18/19

	Integrated Avionic Systems


	FILE coord.c
	Contains all of the functions that convert position and velocities into different coordinte systems


	Authors:
		Francisco Castro, 78655
		Diogo Dores, 
		Pedro Angélico,

	Date: 
    23-01-2019
---------------------------------------------------------*/

#include "general.h"

int initialize_listener(void)
{
	int sd, rc;
	struct sockaddr_in local_addr;
	int broadcast = 1;

	// Creates UDP sockets
	sd=socket(AF_INET, SOCK_DGRAM, 0);
	if(sd<0) {	// in case of error
		printf("LISTENER: cannot open socket\n");
		exit(1);
	}

	// Sets the broadcast
	if (setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcast,sizeof(broadcast)) == -1) {
	      perror("setsockopt (SO_BROADCAST)");
	      exit(1);
	}

	// Binds the local server port
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = inet_addr(B_ADDRESS);
	local_addr.sin_port = htons(B_PORT);
	memset(local_addr.sin_zero, '\0', sizeof local_addr.sin_zero); 
	 
	rc = bind (sd, (struct sockaddr *) &local_addr,sizeof(local_addr));
	if(rc<0) {
		printf("LISTENER: cannot bind port number \n");
		exit(1);
	}

	printf("LISTENER: waiting for data on port UDP %u\n", port);

	return sd;
}



message initialize_msg(message msg)
{
	msg.APos.lat = 0;
	msg.APos.lon = 0;
	msg.Apos.alt = 0;
	msg.mb.im = 0;
	msg.mb.om = 0;
	msg.mb.mm = 0;
	return msg;
}



/*
	Function: print_msg
	Prints all of the parameters of a message 
*/
void print_msg(message msg)
{
	printf("\n*-------Message-------*\n");
	printf("AP: %f %f %f\n", msg.APos.lat, msg.APos.lon, msg.Apos.alt);
	printf("AV: %d %d %d\n", msg.mb.im, msg.mb.om, msg.mb.mm);
	printf("\n");
}

/*
	Function: msg_to_ac
	Stores the data from the messages in the aircraft structure
*/
AC msg_to_ac(message msg)
{
	AC ac;
	ac.pos.lat=msg.APos.lat;
	ac.pos.lon=msg.APos.lon;
	ac.pos.alt=msg.APos.alt;
	ac.pos = llh2xyz(ac.pos);
	ac.mb.im = msg.mb.im;
	ac.mb.om = msg.mb.om;
	ac.mb.mm = msg.mb.mm;

	return ac;
}


/*
	Function: listener
	Listens for intruder's messages in the network 
*/
void *listener(void *vargp){

	printf("\n***************Listener***********************\n");

	// Creates the server UDP broadcast socket
	int sd = initialize_listener();

	int n;
	struct sockaddr_in ILS_addr;
	socklen_t  addr_size;

	// Initialize message variable
	message msg;
	msg = initialize_msg(msg);

	// Control variable to guarantee that only one message is being received at a time
	receiving = 0;

	// Program stays in a cycle until the user presses CTRL+C
	while(exiting == 0) {

		if(receiving==0) {
			receiving = 1;
			// Receives message
			addr_size = sizeof(ILS_addr);
			n = recvfrom(sd, msg, sizeof(message) , 0, (struct sockaddr *) &ILS_addr, &addr_size);
			printf("\nReceived %d bytes from %s\n", n, inet_ntoa(ILS_addr.sin_addr));
			if(n<0) {
				printf("LISTENER: cannot receive data \n");
				receiving=0;
				continue;
			}


			// Stores the message data in the aircraft structure
			aircraft = msg_to_ac(msg);
			print_msg(message msg);
			receiving=0;
		}


	}


	close(sd);
	return NULL;

}