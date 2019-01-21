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
/*
	Function: intHandler
	To exit after user presses CTRL-C
*/
void intHandler(int sig){
	exiting = 1;
}

int main(int argc, char const *argv[])
{


	//To detect CTRL+C
	signal(SIGINT, intHandler);
	exiting = 0;

	//Create alarm interruption
	struct sigaction  sa;
	sa.sa_handler=ALARMhandler;
	sigaction(SIGALRM, &sa, NULL);

	//Create threads to run different functions in parallel
	pthread_t thread_listener, thread_sound;
	pthread_create(&thread_listener, NULL, listener, NULL);
	pthread_create(&thread_sound, NULL, sound, NULL);
	
	while(exiting == 0){
	}

	pthread_join(thread_listener, NULL);	
	ppthread_join(thread_sound, NULL);
	printf("\nThank you for using our ILS.\n");

	exit(0);
}

