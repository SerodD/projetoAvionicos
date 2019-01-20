/*-------------------------------------------------------
	Instituto Superior Técnico - 1st Semester 18/19

	Integrated Avionic Systems


	FILE general.h
	Contains the includes, defines, global variables and functions used in the program


	Authors:
		Francisco Castro, 78655
		Diogo Dores,
		Pedro Angélico, 

	Date: 
    23-01-2019
---------------------------------------------------------*/

#ifndef SAI_GENERAL_H
#define SAI_GENERAL_H

// Includes --------------------------------------------------------------------

#include "math.h"
#include "stdint.h"
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <inttypes.h>
#include <g2.h>
#include <g2_X11.h>
#include <vlc/vlc.h>


// Defines ---------------------------------------------------------------------
#define PI 3.14159265358979323846

//TCAS resolution values
/*#define ALT_ERROR 20                    	//ft
#define ROC_CLIMB2ROUTE 2000*0.3048/60    	//fpm->m/s
#define ROC_DESCEND2ROUTE -2000*0.3048/60  	//fpm->m/s
#define ROC_CLIMB 1500*0.3048/60          	//fpm->m/s
#define ROC_DESCEND -1500*0.3048/60       	//fpm->m/s
#define ROC_CLIMB_NOW 2500*0.3048/60       	//fpm->m/s
#define ROC_DESCEND_NOW -2500*0.3048/60    	//fpm->m/s */

#define CHECK_SUM 32

//Communications constants
#define B_PORT 8000
#define B_ADDRESS "192.168.1.255"

#define STATUS_SIZE 30

#define DT 1
#define TIMEOUT 10

//G2 Window
#define WINDOWX 910
#define WINDOWY 520

// Sound alerts
//#define NUM_ALERTS_RA 5
//#define NUM_ALERTS_TA 3

// Structs Definitions----------------------------------------------------------

typedef struct Coord {
    double lat;         // [deg]
    double lon;         // [deg]
    double alt;         // [ft]
} CoordAir;

typedef struct Marker_Beacons {
    int im;
    int om;
    int mm;
} MB;

typedef struct Message {
    CoordAir APos;
    MB mb;
    uint32_t CS;
} message;

// aircraft position
typedef struct POS {
    // cartesian coordinates
    double x;
    double y;
    double z;
    // geodetic coordinates
    double lat;
    double lon;
    double alt;
} POS;


// aircraft structure
typedef struct AC {
    POS pos;
    MB mb;
} AC_t;

// airport structire
typedef struct Airport_pos {
    POS inicial;
    POS final;
    POS point_intersection;
    double glidepath;           //[º]
} Airport;

typedef struct ENU_pos{
    double e;
    double n;
    double u;
} ENU;

// Global variables-------------------------------------------------------------

struct Inputs inputs;
int port;
char address[STATUS_SIZE];

int allow_dynamics;/*, allow_tcas,  range_mode;*/
int exiting, receiving, sending;
/*int desired_ROC;
double range; */

// used to play alert sounds
//int alert_TA, alert_RA, silent;


// Functions--------------------------------------------------------------------



#endif //SAI_GENERAL_H
