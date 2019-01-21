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

double dot_product(double v[3], double u[3])
{
    double result = 0.0;
    for (int i = 0; i < 3; i++)
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

double angle_btw2_vects(double* a, double* b, int size) {

        double dot = dot_product(a, b);    
        double lenSq1 = pow(array_module(a, sizeof(a)), 2);
        double lenSq2 = pow(array_module(b, sizeof(b)), 2);
        double angle = acos(dot/sqrt(lenSq1 * lenSq2));
        
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
	
	// Glide Slope Range Limit Position
	info->point_base_gs.lat = LAT_GS_BASE;
	info->point_base_gs.lon = LON_GS_BASE;
	info->point_base_gs.alt = HEIGHT_GS_BASE;
	info->point_base_gs = llh2xyz(info->point_base_gs);
	
        // Localizer Antenna Position
	info->point_intersection_loc.lat = LAT_LOC;
	info->point_intersection_loc.lon = LON_LOC;
	info->point_intersection_loc.alt = ELEVATION;
	info->point_intersection_loc = llh2xyz(info->point_intersection_loc);
	
	// Localizer Range Limit Position
	info->point_base_loc.lat = LAT_LOC_BASE;
	info->point_base_loc.lon = LON_LOC_BASE;
	info->point_base_loc.alt = HEIGHT_LOC_BASE;
	info->point_base_loc = llh2xyz(info->point_base_loc);

	info->glidepath = GLIDE_SLOPE_ANGLE;
}

/*
Check if the aircraft is inside the radiation of
the Localizar or the Glide Slope. A cone was considered.
0 -> outside the volume
1 -> inside the volume
*/
int check_lobe(POS tip, POS base, POS aircraft, double height, double radius) {

	double p_minus_x[] = {aircraft.x - tip.x, aircraft.y - tip.y, aircraft.z - tip.z};
	double dir_module = sqrt(pow(base.x - tip.x, 2) + pow(base.y - tip.y, 2) + pow(base.z - tip.z, 2));
	double dir[] = {(base.x - tip.x)/dir_module, (base.y - tip.y)/dir_module, (base.z - tip.z)/dir_module}; // normalized
	double cone_dist = dot_product(p_minus_x, dir);
	double dir_times_cone_dist[] = {cone_dist *(base.x - tip.x), cone_dist *(base.y - tip.y), cone_dist *(base.z - tip.z)};

	/*if(cone_dist <= 0 || cone_dist >=height) {
		return 0; 
	}*/

	double cone_radius = (cone_dist / height) * radius;
	//int i;
    /*for(i=0; i< 3;i++){
        printf("a[i]:%lf b[i]:%lf\n", p_minus_x[i], dir_times_cone_dist[i]);
     } */
    //sleep(10);
	double* c = (double*) malloc(3 * sizeof(double));
	subArray(p_minus_x, dir_times_cone_dist, c);
	//printf("c[i]: %lf %lf %lf \n", c[0], c[1], c[2]);

	double orth_distance = array_module(c, 3);
	
	return 1; // Está sempre a retornar 1

	if(orth_distance >= cone_radius) {
		return 0;
	}

	if((pow(aircraft.x - tip.x, 2) + pow(aircraft.y - tip.y, 2) + pow(aircraft.z - tip.z, 2)) <= pow(radius, 2)) {
		return 1;
	}
	else {
		return 0;
	}
}

/*
Initialize or Update ILS Status
*/
void init_or_upd_ils(AIRPORT info_apt, AC info_ac, ILS* info_ils) {

         //double rny_centerline[] = subArray([info_apt.point_intersection_loc.x, info_apt.point_intersection_loc.y, info_apt.point_intersection_loc.z], [info_apt.point_intersection_gs.x, info_apt.point_intersection_gs.y, info_apt.point_intersection_gs.z], 3);
	
	double north_2[] = {0, 1};
	double north_3[] = {0, 1, 0};
	ENU ac_enu;
	double ac_enu_array[3];

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
	
	// Check if aircraft is inside Localizer Lobe
	if (check_lobe(info_apt.point_intersection_loc, info_apt.point_base_loc, info_ac.pos, HEIGHT_LOC_CONE, RADIUS_LOC_CONE) == 1) {
	        
	        //double ac_loc[] = subArray([info_apt.point_intersection_loc.x, info_apt.point_intersection_loc.y, info_apt.point_intersection_loc.z], project_point_hor(info_ac, info_rny), 3);
			ac_enu = xyz2enu(info_ac.pos, info_apt.point_intersection_loc);
			ac_enu_array[0] = ac_enu.e, 
			ac_enu_array[1] = ac_enu.n; 
			ac_enu_array[2] = ac_enu.u;
	        info_ils->hor_dev = RUNWAY_DIRECTION - angle_btw2_vects(ac_enu_array, north_2, 2);
	        info_ils->LOC_STATUS = 1;
	}
	else {
	        info_ils->LOC_STATUS = 0; // if outside, 0
	        info_ils->hor_dev = 0;
	}
	
	// Check if aircraft is inside Glide Slope Lobe
        if (check_lobe(info_apt.point_intersection_gs, info_apt.point_base_gs, info_ac.pos, HEIGHT_GS_CONE, RADIUS_GS_CONE) == 1) {
        
                //double ac_gs[] = subArray([info_apt.point_intersection_gs.x, info_apt.point_intersection_gs.y, info_apt.point_intersection_gs.z], project_point_ver(info_ac, info_rny), 3);
                ac_enu = xyz2enu(info_ac.pos, info_apt.point_intersection_gs);
                ac_enu_array[0] = ac_enu.e, 
				ac_enu_array[1] = ac_enu.n; 
				ac_enu_array[2] = ac_enu.u;
                info_ils->ver_dev = angle_btw2_vects(ac_enu_array, north_3, 3) - GLIDE_SLOPE_ANGLE;
                info_ils->GS_STATUS = 1;
        }
	else {
	        info_ils->GS_STATUS = 0; // if outside, 0
	        info_ils->ver_dev = 0;
	}
}

