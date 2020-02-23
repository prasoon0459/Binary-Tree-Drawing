#include <GL/glut.h>
#include <cmath>
#include "drawings.h"
#include <bits/stdc++.h>
using namespace std;


/**
@brief Function to draw circle using 8-way symmetry
@param x x-coordinate of point on circle 
@param y y-cordinate of point on circle
@param x0 center of circle
@param y0 center of circle
*/
void symmetric(int x, int y, int x0, int y0) {

	glBegin(GL_POINTS);
	    glVertex2i(x+x0,y+y0);
	    glVertex2i(-x+x0,y+y0);
	    glVertex2i(x+x0,-y+y0);
	    glVertex2i(-x+x0,-y+y0);
	    glVertex2i(y+x0,x+y0);
	    glVertex2i(-y+x0,x+y0);
	    glVertex2i(y+x0,-x+y0);
	    glVertex2i(-y+x0,-x+y0);
	glEnd();
}


/** @brief Draws circle using the mid-point algo
@param x0 x coordinate of the centre of circle
@param y0 y coordinate of the centre of circle
@param r radius
*/
void drawCircle(int x0, int y0, int r){
	/* @remark Scan conversion starts at top most point of the circle.*/
	int x = 0, y = r;                       /* @remark coordinates assuming centre at (0,0)*/
	int d = 1-r;                            /* @remark decision variable */
	int delE = 3, delSE = -2 * r + 5;   /* @remark updating decision variable -'d'.*/


	/* @remark Plot the first point*/
	symmetric(x, y, x0, y0);

	while(y > x)
	{
		if(d < 0)			                /* @remark If d < 0, East coordinate is to be selected. */
			{
			d += delE;
			delE += 2;
			delSE += 2; 	}
		else								/* @remark South-East coordinate is selected.*/
		{
			d += delSE;                   
			delE += 2;
			delSE += 4;
			y--;
		}
		x++;
		symmetric(x, y, x0, y0);             /* @remark Plot the symmetrical points*/
	}
}

void drawNode(int x0, int y0, int r, char t, bool showLabels) 
{
	drawCircle(x0, y0,r);
	if(showLabels){
		const unsigned char c = t;
		glRasterPos2f(x0 - 4, y0);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
	}
}
/* @brief Implements Bresenham's line drawing algorithm
	@param x1 x coordinate of first point on line
	@param y1 y coordinate of first point on line
	@param x2 x coordinate of last point on line
	@param y2 y coordinate of last point on line*/

void drawLine(int x1, int y1, int x2, int y2) 
{
	int dy = abs(y2-y1);
	int dx = abs(x2-x1);
	int x, y;
	int d, incrE, incrNE;
	int x_dir, y_dir;

	x_dir = (x2 > x1) ? 1 : -1;
	y_dir = (y2 > y1) ? 1 : -1;

	if (dy <= dx) { 						/* @remark |slope| <= 1, scan column-wise  */
	d = 2*dy - dx;
	incrE = 2 * dy;
	incrNE = 2 * (dy - dx);
	    x = x1; y = y1;
		for(int i=1;i <= dx; i++) {
			if(d <= 0) {
                d += incrE;
			}
 	        else {
				d += incrNE;
				y = y+y_dir;
	        }

			glBegin(GL_POINTS);
			glVertex2i(x, y);
	        glEnd();
	        x = x + x_dir;
		}
	}
	else { 									/* @remark |slope| >= 1, scan row-wise */
		d = 2*dx - dy;
		incrE = 2 * dx;
		incrNE = 2 * (dx - dy);
		y = y1; x = x1;
		for (int i=0; i < dy; i++) {
			if (d < 0) {
				d += incrE;
			}
            else {
				d += incrNE;
				x = x + x_dir;
			}
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
       		 y = y + y_dir;
	     }
	}

}
/*
@param x1 centre on parent node
@param y1 centre point on parent node
@param x2 centre point on son 
@param y2 center point on son
@param r radius of node
*/
void connectNodes(int x1, int y1, int x2, int y2, int r)
{
    float xl, xr, yl, yr;

    /* @brief Distance between two nodes. */
    float d = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

    /* @remark Locate the point on the circumference of the node to draw line from.*/
    xl = x1 + r*(x2-x1)/d;
    yl = y1 + r*(y2-y1)/d;

    xr = x2 + r*(x1-x2)/d;
    yr = y2 + r*(y1-y2)/d;

	/* @brief Draw line.*/
	drawLine(xl, yl, xr, yr);
}