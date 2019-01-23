/*-------------------------------------------------------
	Instituto Superior Técnico - 1st Semester 18/19

	Integrated Avionics Systems


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
	receiving = 0;
	AIRPORT airport;
	airport_init(&airport);
	g2_init (&vd, &device);
	g2_display (&device);
	//Create threads to run different functions in parallel
	pthread_t thread_listener, thread_sound, thread_g2;
	pthread_create(&thread_listener, NULL, listener, NULL);
	while(1){
		printf("a espera\n");
		if (receiving == 2)
		{
			break;
		}
	}
	pthread_create(&thread_sound, NULL, sound, NULL);
	pthread_create(&thread_g2, NULL, update_devs, NULL);
	
	
	/*printf("lat: %lf long: %lf alt: %lf\n", airport.point_intersection_gs.lat, airport.point_intersection_gs.lon,airport.point_intersection_gs.alt);
	printf("x: %lf y: %lf z: %lf\n",airport.point_intersection_gs.x, airport.point_intersection_gs.y, airport.point_intersection_gs.z);
	printf("GP: %lf\n",airport.glidepath);*/

	while(exiting == 0){
		/*printf("lat: %lf long: %lf alt: %lf\n",aircraft.pos.lat, aircraft.pos.lon,aircraft.pos.alt);
		printf("x: %lf y: %lf z: %lf\n",aircraft.pos.x, aircraft.pos.y, aircraft.pos.z);
		printf("om: %d mm: %d im: %d\n",aircraft.mb.om,aircraft.mb.mm,aircraft.mb.im);*/
		init_or_upd_ils(airport, aircraft, &info_ils);
		printf("om: %d mm: %d im: %d\n",info_ils.mb.om,info_ils.mb.mm,info_ils.mb.im);
		printf("Hor_dev: %lf Ver_dev: %lf\n",info_ils.hor_dev,info_ils.ver_dev);
		printf("LOC_STATUS: %d GS_STATUS: %d\n",info_ils.LOC_STATUS,info_ils.GS_STATUS);
		sleep(2);

	}

	pthread_join(thread_listener, NULL);	
	pthread_join(thread_sound, NULL);
	pthread_join(thread_g2, NULL);
	printf("\nThank you for using our ILS.\n");

	exit(0);
}

