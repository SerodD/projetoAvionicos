/*-------------------------------------------------------
  Instituto Superior Técnico - 1st Semester 18/19

  Integrated Avionic Systems


  	FILE graphics.c
  	"Contains the functions related to the graphic displays"


  Authors:
    Francisco Castro, 78655
    Diogo Dores, 
    Pedro Angélico,

  Date: 
    23-01-2019
---------------------------------------------------------*/

#include "general.h"

double rad2deg(double rad) {
	double deg;
	deg = (rad * 180)/PI;
	return deg;
}

double dot_product(double v[3], double u[3], int size)
{
    double result = 0.0;
    for (int i = 0; i < size; i++)
        result += v[i]*u[i];
    return result;
}

void subArray(double a[3], double b[3], double* c) 
{ 
    int i;
        for(i=0; i< 3;i++){
                c[i]=a[i]-b[i];
        } 
} 

double array_module(double* array, int size) {
	double result = 0.0;
	for(int i=0; i< size;i++) 
        	result += pow(array[i], 2);
	result = sqrt(result);
	return result;
}

double angle_btw2_vects(double* a, double* b) {

        double dot = dot_product(a, b, 3);    
        double det = a[0]*b[1] - b[0]*a[1];
        double angle = atan2(det, dot);
        
        return angle;
}

/*
Initialize airport parameters
*/
void airport_init(AIRPORT* info) {	
    	// Glide Slope Antenna Position
	info->point_intersection_gs.lat = LAT_GS;
	info->point_intersection_gs.lon = LON_GS;
	info->point_intersection_gs.alt = ELEVATION;
	info->point_intersection_gs = llh2xyz(info->point_intersection_gs);
	/*printf("*************point_intersection_gs*************\n");
	printf("X %lf, Y %lf, Z %lf\n", info->point_intersection_gs.x, info->point_intersection_gs.y, info->point_intersection_gs.z);
        printf("X %lf, Y %lf, Z %lf", info->point_intersection_gs.lat, info->point_intersection_gs.lon, info->point_intersection_gs.alt);
	printf("**************************\n\n");*/
	
	// Glide Slope Range Limit Position
	info->point_base_gs.lat = LAT_GS_BASE;
	info->point_base_gs.lon = LON_GS_BASE;
	info->point_base_gs.alt = HEIGHT_GS_BASE;
	info->point_base_gs = llh2xyz(info->point_base_gs);
	/*printf("**************point_base_gs************\n");
	printf("X %lf, Y %lf, Z %lf", info->point_base_gs.x, info->point_base_gs.y, info->point_base_gs.z);
	printf("**************************\n\n");*/
	
	
        // Localizer Antenna Position
	info->point_intersection_loc.lat = LAT_LOC;
	info->point_intersection_loc.lon = LON_LOC;
	info->point_intersection_loc.alt = ELEVATION;
	info->point_intersection_loc = llh2xyz(info->point_intersection_loc);
	/*printf("*************point_intersection_loc*************\n");
	printf("X %lf, Y %lf, Z %lf", info->point_intersection_loc.x, info->point_intersection_loc.y, info->point_intersection_loc.z);
	printf("**************************\n\n");*/
	
	// Localizer Range Limit Position
	info->point_base_loc.lat = LAT_LOC_BASE;
	info->point_base_loc.lon = LON_LOC_BASE;
	info->point_base_loc.alt = HEIGHT_LOC_BASE;
	info->point_base_loc = llh2xyz(info->point_base_loc);
	/*printf("*************point_base_loc*************\n");
	printf("X %lf, Y %lf, Z %lf", info->point_base_loc.x, info->point_base_loc.y, info->point_base_loc.z);
	printf("**************************\n\n");*/
	//sleep(10000);

	info->glidepath = GLIDE_SLOPE_ANGLE;
}

/*
Check if the aircraft is inside the radiation of
the Localizer or the Glide Slope. A cone was considered.
0 -> outside the volume
1 -> inside the volume
*/
int check_lobe(POS tip, POS base, POS aircraft, double height, double radius) {

	double p_minus_x[] = {aircraft.x - tip.x, aircraft.y - tip.y, aircraft.z - tip.z};
	double dir_module = sqrt(pow(base.x - tip.x, 2) + pow(base.y - tip.y, 2) + pow(base.z - tip.z, 2));
	double dir[] = {(base.x - tip.x)/dir_module, (base.y - tip.y)/dir_module, (base.z - tip.z)/dir_module}; // normalized
	double cone_dist = dot_product(p_minus_x, dir, 3);
	double dir_times_cone_dist[] = {cone_dist * dir[0], cone_dist * dir[1], cone_dist * dir[2]};
	double cone_radius;
	double orth_distance;
	
	return 1;
	
	if((pow(aircraft.x - tip.x, 2) + pow(aircraft.y - tip.y, 2) + pow(aircraft.z - tip.z, 2)) > pow(height, 2)) {
		printf("0\n");
		return 0;
	}

	if(cone_dist < 0 || cone_dist >height) {
		printf("1\n");
		return 0; 
	}
	
	cone_radius = (cone_dist / height) * radius;

	double* c = (double*) malloc(3 * sizeof(double));
	subArray(p_minus_x, dir_times_cone_dist, c);

	orth_distance = array_module(c, 3);

	if(orth_distance >= cone_radius) {
		printf("2\n");
		return 0;
	}
	else {
		printf("3\n");
		return 1;
	}
}

/*
Initialize or Update ILS Status
*/
void init_or_upd_ils(AIRPORT info_apt, AC info_ac, ILS* info_ils) {
	
	double north_loc[3] = {0, 1, 0};
	double north_gs[3] = {1, 0, 0};
	double ac_enu_array_loc[3];
	double ac_enu_array_gs[3];
	double angle_hor;
	double angle_ver;
	int check_lobe_gs;
	int check_lobe_loc;
	ENU ac_enu;

	if(info_ac.mb.im == 1) {
		info_ils->mb.im = 1;
	}
	else {
		info_ils->mb.im = 0;
	}
	
	if(info_ac.mb.mm == 1) {
		info_ils->mb.mm = 1;
	}
	else {
		info_ils->mb.mm = 0;
	}
	
	if(info_ac.mb.om == 1) {
		info_ils->mb.om = 1;
	}
	else {
		info_ils->mb.om = 0;
	}

	ac_enu = xyz2enu(info_ac.pos, info_apt.point_intersection_loc);
	ac_enu_array_loc[0] = ac_enu.e;
	ac_enu_array_loc[1] = ac_enu.n;
	ac_enu_array_loc[2] = 0;
	angle_hor = rad2deg(RUNWAY_DIRECTION - angle_btw2_vects(ac_enu_array_loc, north_loc));
	
	printf("EAST %lf, NORTH %lf, UP %lf\n", ac_enu.e, ac_enu.n, ac_enu.u);

	ac_enu = xyz2enu(info_ac.pos, info_apt.point_intersection_gs);
	ac_enu_array_gs[0] = ac_enu.n; 
	ac_enu_array_gs[1] = ac_enu.u;
	ac_enu_array_gs[2] = 0;
	angle_ver = rad2deg(angle_btw2_vects(ac_enu_array_gs, north_gs) - GLIDE_SLOPE_ANGLE);
	
	printf("EAST %lf, NORTH %lf, UP %lf\n", ac_enu.e, ac_enu.n, ac_enu.u);
	
	printf("Angle Ver %lf, Angle Hor %lf\n\n", angle_ver, angle_hor);
	printf("Dist2gs %lf\n\n", array_module(ac_enu_array_gs, 3));
	printf("Dist2loc %lf\n\n", array_module(ac_enu_array_loc, 3));

	// Check if aircraft is inside the Glide Slope Lobe
	if (angle_hor >= -10.0 && angle_hor <= 10.0 && angle_ver >= -5.0 && angle_ver <= 10.0 && array_module(ac_enu_array_gs, 3) <= HEIGHT_GS_CONE) {
                check_lobe_gs = 1;
	}
	else {
		check_lobe_gs = 0;
	}
	
	// Check if the aircraft is inside the Localizer Lobe
	if (angle_hor >= -20.0  && angle_hor <= 20.0 && angle_ver >= -10.0 && angle_ver <= 20.0 && array_module(ac_enu_array_loc, 3) <= HEIGHT_LOC_CONE) {
	        check_lobe_loc = 1;
	}
	else {
		check_lobe_loc = 0;
	}
	
	//check_lobe_loc = 1;
	//check_lobe_gs = 1;
	
	// Check if the aircraft is inside Localizer Lobe
	if (check_lobe_loc == 1) {
	        info_ils->hor_dev = angle_hor;
	        info_ils->LOC_STATUS = 1;
	}
	else {
	        info_ils->LOC_STATUS = 0; // if outside, 0
	        info_ils->hor_dev = 0;
	}

	printf("EAST %lf, NORTH %lf, UP %lf\n", ac_enu.e, ac_enu.n, ac_enu.u);
	
	// Check if aircraft is inside Glide Slope Lobe
        if (check_lobe_gs == 1) {
                info_ils->ver_dev = angle_ver;
                info_ils->GS_STATUS = 1;
        }
	else {
	        info_ils->GS_STATUS = 0; // if outside, 0
	        info_ils->ver_dev = 0;
	}

	printf("EAST %lf, NORTH %lf, UP %lf\n", ac_enu.e, ac_enu.n, ac_enu.u);
}
