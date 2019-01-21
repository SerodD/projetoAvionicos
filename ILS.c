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

/*
  Function: delay
  Handles delay
*/

void delay(unsigned int milliseconds){

    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

/*
  Function: deg2rad
  Converts from degrees to radians 
*/
float deg2rad(int a)
{
	float b;
	float c;

	c=a;
	b=c/180*PI;

	return b;
}

double dot_product(double v[], double u[], int n)
{
    double result = 0.0;
    for (int i = 0; i < n; i++)
        result += v[i]*u[i];
    return result;
}

double* subArray(double a[], double b[], int size) 
{ 
        int i;
	double c[];
        for(i=0; i< size;i++) 
                c[i]=a[i]-b[i]; 
	return c;
} 

double array_module(double* array, int size) {
	double result = 0.0;
	for(int i=0; i< size;i++) 
        	result += pow(array[i], 2);
	result = sqrt(result);
	return result;
}

double angle_btw2_vects(double a[], double b[], int size) {

        double dot = dot_product(a, b, sizeof(a));    
        double lenSq1 = pow(array_module(a, sizeof(a)), 2);
        double lenSq2 = pow(array_module(b, sizeof(b)), 2);
        double angle = acos(dot/sqrt(lenSq1 * lenSq2))
        
        return angle;
}

/*
Initialize airport parameters
*/
void airport_init(AIRPORT* info) {
        // Runway Initial Position
	/*info->runway_init_pos.lat = LAT_INI;
	info->runway_init_pos.lon = LON_INI;
	info->runway_init_pos.alt = AIRPORT_ELEVATION;
	info->runway_init_pos.x = llh2xyz(info->runway_init_pos);
	info->runway_init_pos.y = llh2xyz(info->runway_init_pos);
	info->runway_init_pos.z = llh2xyz(info->runway_init_pos);*/
	
	// Runway Final Position
	/*info->runway_final_pos.lat = LAT_FIN;
	info->runway_final_pos.lon = LON_FIN;
	info->runway_final_pos.alt = AIRPORT_ELEVATION;
	info->runway_final_pos.x = llh2xyz(info->runway_final_pos);
	info->runway_final_pos.y = llh2xyz(info->runway_final_pos);
	info->runway_final_pos.z = llh2xyz(info->runway_final_pos);*/
	
        // Glide Slope Antenna Position
	info->point_intersection_gs.lat = LAT_GS;
	info->point_intersection_gs.lon = LON_GS;
	info->point_intersection_gs.alt = AIRPORT_ELEVATION;
	info->point_intersection_gs.x = llh2xyz(info->point_intersection_gs);
	info->point_intersection_gs.y = llh2xyz(info->point_intersection_gs);
	info->point_intersection_gs.z = llh2xyz(info->point_intersection_gs);
	
	// Glide Slope Range Limit Position
	info->point_base_gs.lat = LAT_GS;
	info->point_base_gs.lon = LON_GS;
	info->point_base_gs.alt = AIRPORT_ELEVATION;
	info->point_base_gs.x = llh2xyz(info->point_base_gs);
	info->point_base_gs.y = llh2xyz(info->point_base_gs);
	info->point_base_gs.z = llh2xyz(info->point_base_gs);
	
        // Localizer Antenna Position
	info->point_intersection_loc.lat = LAT_LOC;
	info->point_intersection_loc.lon = LON_LOC;
	info->point_intersection_loc.alt = AIRPORT_ELEVATION;
	info->point_intersection_loc.x = llh2xyz(info->point_intersection_loc);
	info->point_intersection_loc.y = llh2xyz(info->point_intersection_loc);
	info->point_intersection_loc.z = llh2xyz(info->point_intersection_loc);
	
	// Localizer Range Limit Position
	info->point_base_loc.lat = LAT_LOC;
	info->point_base_loc.lon = LON_LOC;
	info->point_base_loc.alt = AIRPORT_ELEVATION;
	info->point_base_loc.x = llh2xyz(info->point_base_loc);
	info->point_base_loc.y = llh2xyz(info->point_base_loc);
	info->point_base_loc.z = llh2xyz(info->point_base_loc);

	info->glidepath = GLIDE_SLOPE_ANGLE;
}

/*void init_rny_planes(RNY_PLANES* planes) {
        planes->a_hor = -89272761.686172;
        planes->b_hor = -28151500.462264;
        planes->c_hor = 175459820.6445;
        planes->d_hor = -1.2649170285033*pow(10, 15);
        
        planes->a_ver = 1407641.5879537;
        planes->b_ver = -19815225.036967;
        planes->c_ver = -2280660.921759;
        planes->d_ver = -85523176872;
}*/

/*XYZ project_point_hor(AC info_ac, Airport info_rny_planes) {
        XYZ proj;
        double t;
        
        t = -(info_rny_planes.d_hor + info_rny_planes.c_hor * info_ac.pos.z + info_rny_planes.b_hor * info_ac.pos.y + info_rny_planes.a_hor * info_ac.pos.x)/(pow(info_rny_planes.c_hor, 2) + pow(info_rny_planes.b_hor, 2) + pow(info_rny_planes.a_hor, 2));
        
        proj.x = info_rny_planes.a_hor * t + info_ac.pos.x;
        proj.y = info_rny_planes.b_hor * t + info_ac.pos.y;
        proj.z = info_rny_planes.c_hor * t + info_ac.pos.z;
        
        return proj;    
}

XYZ project_point_ver(AC info_ac, Airport info_rny_planes) {
        XYZ proj;
        
        t = -(info_rny_planes.d_ver + info_rny_planes.c_ver * info_ac.pos.z + info_rny_planes.b_ver * info_ac.pos.y + info_rny_planes.a_ver * info_ac.pos.x)/(pow(info_rny_planes.c_ver, 2) + pow(info_rny_planes.b_ver, 2) + pow(info_rny_planes.a_ver, 2));
        
        proj.x = info_rny_planes.a_ver * t + info_ac.pos.x;
        proj.y = info_rny_planes.b_ver * t + info_ac.pos.y;
        proj.z = info_rny_planes.c_ver * t + info_ac.pos.z;
               
        return proj;     
}*/

/*
Initialize or update aircraft parameters
*/
void aircraft_init_or_upd(MSG message, AC* aircraft) {
	aircraft->pos.lat = message.APos.lat;
	aircraft->pos.lon = message.APos.lon;
	aircraft->pos.alt = message.APos.alt;

	aircraft->mb.im = message.mb.im;
	aircraft->mb.mm = message.mb.mm;
	aircraft->mb.om = message.mb.om;
}

/*
Check if the aircraft is inside the radiation of
the Localizar or the Glide Slope. A cone was considered.
0 -> outside the volume
1 -> inside the volume
*/
int check_lobe(POS tip, POS base, POS aircraft, double height, double radius) {

	double p_minus_x[] = [aircraft.x - tip.x, aircraft.y - tip.y, aircraft.z - tip.z];
	double dir_module = sqrt(pow(base.x - tip.x, 2) + pow(base.y - tip.y, 2) + pow(base.z - tip.z, 2));
	double dir[] = [(base.x - tip.x)/dir_module, (base.y - tip.y)/dir_module, (base.z - tip.z)/dir_module]; // normalized
	double dir_times_cone_dist = [cone_dist *(base.x - tip.x), cone_dist *(base.y - tip.y), cone_dist *(base.z - tip.z)];
	cone_dist = dot_product(p_minus_x, dir, sizeof(p_minus_x));

	if(cone_dist <= 0 || cone_dist >=height) {
		return 0;
	}

	cone_radius = (cone_dist / height) * radius;
	orth_distance = array_module(subArray(p_minus_x, dir_times_cone_dist), 3);

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
	if (check_lobe(info_apt.point_intersection_loc, info_apt.point_base_loc, info_ac.pos, LOC_CONE_HEIGHT, LOC_CONE_RADIUS) == 1) {
	        
	        
	        //double ac_loc[] = subArray([info_apt.point_intersection_loc.x, info_apt.point_intersection_loc.y, info_apt.point_intersection_loc.z], project_point_hor(info_ac, info_rny), 3);
	             
	        info_ils->hor_dev = RUNWAY_DIRECTION - angle_btw2_vects(xyz2enu(info_ac.pos, info_apt.point_intersection_loc), [0 1], 2);
	        info_ils->LOC_STATUS = 1;
	}
	else {
	        info_ils->LOC_STATUS = 0; // if outside, 0
	        info_ils->hor_dev = 0;
	}
	
	// Check if aircraft is inside Glide Slope Lobe
        if (check_lobe(info_apt.point_intersection_gs, info_apt.point_base_gs, info_ac.pos, GS_CONE_HEIGHT, GS_CONE_RADIUS) == 1) {
        
                //double ac_gs[] = subArray([info_apt.point_intersection_gs.x, info_apt.point_intersection_gs.y, info_apt.point_intersection_gs.z], project_point_ver(info_ac, info_rny), 3);
                
                info_ils->ver_dev = angle_btw2_vects(xyz2enu(info_ac.pos, info_apt.point_intersection_gs), [0 1 0], 3) - GS_ANGLE;
                info_ils->GS_STATUS = 1;
        }
	else {
	        info_ils->GS_STATUS = 0; // if outside, 0
	        info_ils->ver_dev = 0;
	}
}

