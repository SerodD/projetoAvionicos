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

#include "stdint.h"
#include <math.h>
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

// Airport Data
#define RUNWAY_LENGTH 3805.1232
#define ELEVATION 100.2792
#define RUNWAY_DIRECTION 0.471238898038 // Runway 03, 27º in radians

// ILS Data
#define GLIDE_SLOPE_ANGLE 0.060441582629//3.46304759174
#define LAT_GS 0.676652003505//38.769304
#define LON_GS -0.1595642834//-9.142360
#define LAT_LOC 0.677185027058//38.799844
#define LON_LOC -0.15927951548//-9.126044

#define LAT_GS_BASE 0.673867644843//38.609772
#define LON_GS_BASE -0.16103337939//-9.226533
#define HEIGHT_GS_BASE 1070.87127232
#define HEIGHT_GS_CONE 18545.4158479
#define RADIUS_GS_CONE 777.283221757

#define LAT_LOC_BASE 0.670361156202//38.408865
#define LON_LOC_BASE -0.162700291//-9.322040
#define HEIGHT_LOC_BASE 8264.2184068
#define HEIGHT_LOC_CONE 47014.2521303
#define RADIUS_LOC_CONE 8289.8811284

#define CHECK_SUM 32

//Communications constants
#define B_PORT 8100
#define B_ADDRESS "127.0.0.1"

#define STATUS_SIZE 30

#define DT 1
#define TIMEOUT 10

//G2 Window
#define WINDOWX 1000
#define WINDOWY 550

// Structs Definitions----------------------------------------------------------

typedef struct Coord {
    double lat;         // [deg]
    double lon;         // [deg]
    double alt;         // [ft]
} CoordAir;

typedef struct CoordXYZ {
    double x;         // [deg]
    double y;         // [deg]
    double z;         // [ft]
} XYZ;

typedef struct Marker_Beacons {
    int im;
    int om;
    int mm;
} MB;

typedef struct Message {
    CoordAir APos;
    MB mb;
} MSG;

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
typedef struct Aircraft {
    POS pos;
    MB mb;
} AC;

// airport structure
typedef struct Airport_pos {
    POS point_intersection_gs;
    POS point_intersection_loc;
    POS point_base_gs;
    POS point_base_loc;
    double glidepath;           //[º]
} AIRPORT;

typedef struct ENU_pos{
    double e;
    double n;
    double u;
} ENU;

typedef struct ILS_STATUS {
	MB mb;
	double hor_dev;
	double ver_dev;
	int LOC_STATUS;
	int GS_STATUS;
} ILS;

// Global variables-------------------------------------------------------------

int port, exiting, receiving;
char address[STATUS_SIZE];
AC aircraft;
ILS info_ils;
int device;
int vd;

// Functions--------------------------------------------------------------------

// com.c
void *listener(void *vargp);
AC msg_to_ac(MSG msg);
void print_msg(MSG msg);
MSG initialize_msg(MSG msg);
int initialize_listener(void);

//coord.c
POS xyz2llh(POS pos);
POS llh2xyz(POS pos);
ENU xyz2enu(POS pos_ac, POS pos_radar);

//graphics.c
void delay(unsigned int milliseconds);
double *get_x_pos_circle(double y, double x_cen, double y_cen, double radius);
double *get_y_pos_circle(double x, double x_cen, double y_cen, double radius);
void g2_init (int *vd, int *d);
void g2_display (int *d);
void loc_off(int *d);
void loc_on(int *d);
void gs_off(int *d);
void gs_on(int *d);
void om_on(int* d);
void om_off(int* d);
void mm_on(int* d);
void mm_off(int* d);
void im_on(int* d);
void im_off(int* d);
void *update_devs(void *vargp);

// ILS.c
double rad2deg(double rad);
double dot_product(double v[3], double u[3], int size);
void subArray(double a[3], double b[3], double* c);
double array_module(double* array, int size);
double angle_btw2_vects(double* a, double* b);
void airport_init(AIRPORT* info);
void aircraft_init_or_upd(MSG message, AC* aircraft);
int check_lobe(POS tip, POS base, POS aircraft, double height, double radius);
void init_or_upd_ils(AIRPORT info_apt, AC info_ac, ILS* info_ils);

// sound.c
void *sound(void *vargp);


#endif //SAI_GENERAL_H
