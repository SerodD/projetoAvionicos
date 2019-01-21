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
Functions to draw ILS lines
*/
double *get_x_pos_circle(double y, double x_cen, double y_cen, double radius) {
	double* x = malloc(2);
	double a = 1;
	double b = -2 * x_cen;
	double c = pow(x_cen, 2) + pow(y - y_cen, 2) - pow(radius, 2);
	double x1 = (-b + sqrt(pow(b, 2) - 4*a*c))/(2*a);
	double x2 = (-b - sqrt(pow(b, 2) - 4*a*c))/(2*a);
	x[0] = x1;
	x[1] = x2;
	
	return x;
}

double *get_y_pos_circle(double x, double x_cen, double y_cen, double radius) {
	double* y = malloc(2);
	double a = 1;
	double b = -2 * y_cen;
	double c = pow(y_cen, 2) + pow(x - x_cen, 2) - pow(radius, 2);
	double y1 = (-b + sqrt(pow(b, 2) - 4*a*c))/(2*a);
	double y2 = (-b - sqrt(pow(b, 2) - 4*a*c))/(2*a);
	y[0] = y1;
	y[1] = y2;
	
	return y;
}

/*
  Function: g2_init
  Opens and initializes a G2 window
*/
void g2_init (int *vd, int *d)
{
	*vd = g2_open_vd();
	*d = g2_open_X11(WINDOWX, WINDOWY);
	g2_attach(*vd,*d);

	return;
}
	
/*
  Function: g2_display
  Builds the ILS display
*/

void g2_display (int *d)
{
	//Outer Marker Display	
	g2_pen(*d, g2_ink(*d, 0.8, 1, 1));
	g2_filled_rectangle(*d, 0, 400, 150, 550);

	g2_flush(*d);
	
	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 0, 400, 150, 550); 

	g2_flush(*d);

	g2_set_font_size(*d, 100);
	g2_string(*d, 45, 445, "O");   

	//Middle Marker Display
	g2_pen(*d, g2_ink(*d, 1, 1, 0.5));
	g2_filled_rectangle(*d, 150, 400, 300, 550);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 150, 400, 300, 550);

	g2_set_font_size(*d, 100);
	g2_string(*d, 180, 445, "M"); 

	//Inner Marker Display
	g2_pen(*d, g2_ink(*d, 0.4, 1, 0.6));
	g2_filled_rectangle(*d, 300, 400, 450, 550);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 300, 400, 450, 550);

	g2_set_font_size(*d, 100);
	g2_string(*d, 360, 445, "I");  

	// Painel Digital
	g2_pen(*d, g2_ink(*d, 1, 1, 0.9));
	g2_filled_rectangle(*d, 0, 0, 450, 400);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 0, 0, 450, 400);

	// Desvio Vertical

	g2_set_font_size(*d, 30);
	g2_string(*d, 77, 320, "Desvio Vertical [Degrees]");

	g2_flush(*d);

	g2_pen(*d, 0);
	g2_filled_rectangle(*d, 75, 250, 375, 290);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 75, 250, 375, 290);

	g2_flush(*d);

	// Desvio Horizontal

	g2_set_font_size(*d, 30);
	g2_string(*d, 60, 130, "Desvio Horizontal [Degrees]");

	g2_flush(*d);

	g2_pen(*d, 0);
	g2_filled_rectangle(*d, 75, 60, 375, 100);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 75, 60, 375, 100);

	g2_flush(*d);

	// ILS display

	g2_pen(*d, g2_ink(*d, 0.5, 0.4, 0.5));
	g2_filled_rectangle(*d, 450, 0, WINDOWX, WINDOWY);

	g2_pen(*d, 1);
	g2_rectangle(*d, 450, 0, WINDOWX, WINDOWY);

	g2_set_font_size(*d, 20);
	g2_string(*d, 460, 520, "ILS display");

	g2_pen(*d, 0);	
	g2_filled_circle(*d, 725, 275, 270);

	g2_pen(*d, 1);	
	g2_filled_circle(*d, 725, 275, 260);

	g2_pen(*d, 0);
	g2_circle(*d, 725, 275, 10);

	g2_pen(*d, 0);
	g2_set_line_width(*d, 1);
	g2_line(*d, 725, 15, 725, 535);
	g2_line(*d, 465, 275, 985, 275);

	g2_pen(*d, 1);
	g2_set_line_width(*d, 5);
	g2_line(*d, 450, 0, 450, 550);

	g2_pen(*d, 0);
	g2_set_line_width(*d, 1);

	for(int i = 0; i<=20; i++) {
		g2_line(*d, 465+i*26, 270, 465+i*26, 280);
		g2_line(*d, 720, 15+i*26, 730, 15+i*26);	
	}

	//Localizer marker
	
	g2_pen(*d, g2_ink(*d, 1, 0.5, 0.3));
	g2_filled_rectangle(*d, 460, 10, 550, 50);	

	g2_pen(*d, 1);
	g2_rectangle(*d, 460, 10, 550, 50);

	g2_pen(*d, 0);	
	g2_set_font_size(*d, 40);
	g2_string(*d, 465, 15, "LOC");

	//Glide Slope marker

	g2_pen(*d, g2_ink(*d, 1, 0.5, 0.3));
	g2_filled_rectangle(*d, 900, 10, 990, 50);	

	g2_pen(*d, 1);
	g2_rectangle(*d, 900, 10, 990, 50);

	g2_pen(*d, 0);	
	g2_set_font_size(*d, 40);
	g2_string(*d, 920, 15, "GS");
}

/*
If aircraft doesn't receive the signal from the LOC
*/
void loc_off(int *d) {
	g2_pen(*d, 19);
	g2_filled_rectangle(*d, 460, 10, 550, 50);	

	g2_pen(*d, 1);
	g2_rectangle(*d, 460, 10, 550, 50);

	g2_pen(*d, 0);	
	g2_set_font_size(*d, 40);
	g2_string(*d, 465, 15, "LOC");
}

void loc_on(int *d) {
	g2_pen(*d, g2_ink(*d, 1, 0.5, 0.3));
	g2_filled_rectangle(*d, 460, 10, 550, 50);	

	g2_pen(*d, 1);
	g2_rectangle(*d, 460, 10, 550, 50);

	g2_pen(*d, 0);	
	g2_set_font_size(*d, 40);
	g2_string(*d, 465, 15, "LOC");
}

/*
If aircraft doesn't receive the signal from the GLIDE
*/
void gs_off(int *d) {
	g2_pen(*d, 19);
	g2_filled_rectangle(*d, 900, 10, 990, 50);	

	g2_pen(*d, 1);
	g2_rectangle(*d, 900, 10, 990, 50);

	g2_pen(*d, 0);	
	g2_set_font_size(*d, 40);
	g2_string(*d, 920, 15, "GS");
}

void gs_on(int *d) {
	g2_pen(*d, g2_ink(*d, 1, 0.5, 0.3));
	g2_filled_rectangle(*d, 900, 10, 990, 50);	

	g2_pen(*d, 1);
	g2_rectangle(*d, 900, 10, 990, 50);

	g2_pen(*d, 0);	
	g2_set_font_size(*d, 40);
	g2_string(*d, 920, 15, "GS");
}

//If aircraft is in OM Marker, it flashes blue
void om_on(int* d) {
	g2_pen(*d, g2_ink(*d, 0.8, 1, 1));
	g2_filled_rectangle(*d, 0, 400, 150, 550);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 0, 400, 150, 550); 
		
	g2_set_font_size(*d, 100);
	g2_string(*d, 45, 445, "O");

	delay(200);

	g2_pen(*d, 3);
	g2_filled_rectangle(*d, 0, 400, 150, 550);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 0, 400, 150, 550); 
		
	g2_set_font_size(*d, 100);
	g2_string(*d, 45, 445, "O");
	delay(200);
}

//After passing by OM, the lighter turns back to the normal color
void om_off(int* d){
	g2_pen(*d, g2_ink(*d, 0.8, 1, 1));
	g2_filled_rectangle(*d, 0, 400, 150, 550);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 0, 400, 150, 550); 
		
	g2_set_font_size(*d, 100);
	g2_string(*d, 45, 445, "O");
}

/*
If aircraft is in MM Marker, it flashes red
*/
void mm_on(int* d) {
	g2_pen(*d, 19);
	g2_filled_rectangle(*d, 150, 400, 300, 550);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 150, 400, 300, 550);

	g2_set_font_size(*d, 100);
	g2_string(*d, 180, 445, "M");

	delay(150);

	g2_pen(*d, g2_ink(*d, 1, 1, 0.5));
	g2_filled_rectangle(*d, 150, 400, 300, 550);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 150, 400, 300, 550);

	g2_set_font_size(*d, 100);
	g2_string(*d, 180, 445, "M");
	delay(150);
}

/*
After passing by MM, the lighter turns back to the normal color
*/
void mm_off(int* d){
	g2_pen(*d, g2_ink(*d, 1, 1, 0.5));
	g2_filled_rectangle(*d, 150, 400, 300, 550);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 150, 400, 300, 550);

	g2_set_font_size(*d, 100);
	g2_string(*d, 180, 445, "M");
}

/*
If aircraft is in MM Marker, it flashes red
*/
void im_on(int* d) {
	g2_pen(*d, 0);
	g2_filled_rectangle(*d, 300, 400, 450, 550);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 300, 400, 450, 550);

	g2_set_font_size(*d, 100);
	g2_string(*d, 360, 445, "I");

	delay(100);

	g2_pen(*d, g2_ink(*d, 0.4, 1, 0.6));
	g2_filled_rectangle(*d, 300, 400, 450, 550);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 300, 400, 450, 550);

	g2_set_font_size(*d, 100);
	g2_string(*d, 360, 445, "I");
	delay(100);
}

/*
After passing by MM, the lighter turns back to the normal color
*/
void im_off(int* d){
	g2_pen(*d, g2_ink(*d, 0.4, 1, 0.6));
	g2_filled_rectangle(*d, 300, 400, 450, 550);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 300, 400, 450, 550);

	g2_set_font_size(*d, 100);
	g2_string(*d, 360, 445, "I");
}

/*
  Function: deg2rad
  Converts from degrees to radians 
*/

void update_devs(int *d, ILS status) {
	char s_hor[20], s_ver[20];
	double* y = malloc(2);
	double* x = malloc(2);

	sprintf(s_hor,"%.2f", status.hor_dev);
	sprintf(s_ver,"%.2f", status.ver_dev);	

	// Update Vertical Panel	
	g2_pen(*d, 0);
	g2_filled_rectangle(*d, 75, 250, 375, 290);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 75, 250, 375, 290);

	g2_pen(*d, 1);
	g2_set_font_size(*d, 30);
	g2_string(*d, 170, 260, s_hor);

	// Update Horizontal Panel
	g2_pen(*d, 0);
	g2_filled_rectangle(*d, 75, 60, 375, 100);

	g2_pen(*d, 1);	
	g2_set_line_width(*d, 1);
	g2_rectangle(*d, 75, 60, 375, 100);

	g2_pen(*d, 1);
	g2_set_font_size(*d, 30);
	g2_string(*d, 170, 70, s_ver);

	
	// Clean display

	g2_pen(*d, 1);	
	g2_filled_circle(*d, 725, 275, 260);

	g2_pen(*d, 0);
	g2_circle(*d, 725, 275, 10);

	g2_pen(*d, 0);
	g2_set_line_width(*d, 1);
	g2_line(*d, 725, 15, 725, 535);
	g2_line(*d, 465, 275, 985, 275);

	g2_pen(*d, 1);
	g2_set_line_width(*d, 5);
	g2_line(*d, 450, 0, 450, 550);

	g2_pen(*d, 0);
	g2_set_line_width(*d, 1);

	for(int i = 0; i<=20; i++) {
		g2_line(*d, 465+i*26, 270, 465+i*26, 280);
		g2_line(*d, 720, 15+i*26, 730, 15+i*26);	
	}	

	// Update ILS lines
	g2_pen(*d, 25);
	g2_set_line_width(*d, 5);
	if(status.hor_dev >= 20 || status.hor_dev <= -20) {
		// don't print any line; OUT OF RANGE
	}
	else {
		y = get_y_pos_circle(-status.hor_dev + 725, 725, 275, 260);
		//printf("X %lf Y_1 %lf  Y_2 %lf\n", -status.hor_dev + 725, y[0], y[1]);
		g2_line(*d, -status.hor_dev + 725, y[0], -status.hor_dev + 725, y[1]);
	}

	if(status.ver_dev >= 10 || status.ver_dev <= -10) {
		// don't print any line; OUT OF RANGE
	}
	else {
		x = get_x_pos_circle(-status.ver_dev + 275, 725, 275, 260);
		printf("Y %lf X_1 %lf  X_2 %lf\n", -status.ver_dev + 275, x[0], x[1]);
		g2_line(*d, x[0], -status.ver_dev + 275, x[1], -status.ver_dev + 275);
	}
}

float deg2rad(int a)
{
	float b;
	float c;

	c=a;
	b=c/180*PI;

	return b;
}	
