#include <GL/glut.h>
#include <cmath>
#include "drawings.h"

using namespace std;


/**
Function to draw circle using 8-way symmetry
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


/**
Draws nodes using the mid-point algo
(x0,y0) denotes the centre of circle with 'r' as its radius.
*/
void drawNode(int x0, int y0, int r)
{
	///Scan conversion starts at top most point of the circle.
	int x = 0, y = r;                       /// coordinates assuming centre at (0,0)
	int d = 1-r;                            /// decision variable
	int delE = 3, delSE = -2 * r + 5;   /// updating decision variable -'d'.


	///Plot the first point
	symmetric(x, y, x0, y0);

	while(y > x)
	{
		if(d < 0)			                /// If d < 0, East coordinate is to be selected.
			{
			d += delE;
			delE += 2;
			delSE += 2; 	}
		else								/// South-East coordinate is selected.
		{
			d += delSE;                   
			delE += 2;
			delSE += 4;
			y--;
		}
		x++;
		symmetric(x, y, x0, y0);             ///Plot the symmetrical points
	}
}


void drawLine(int x1, int y1, int x2, int y2) {
	int dy = abs(y2-y1);
	int dx = abs(x2-x1);
	int x, y;
	int d, incrE, incrNE;
	int x_dir, y_dir;

	x_dir = (x2 > x1) ? 1 : -1;
	y_dir = (y2 > y1) ? 1 : -1;

	if (dy <= dx) { 						/// |slope| <= 1, scan column-wise
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
	else { 									/// |slope| >= 1, scan row-wise
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

void connectNodes(int x1, int y1, int x2, int y2, int r)
{
    float xl, xr, yl, yr;

    //Distance between two nodes.
    float d = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

    //Locate the point on the circumference of the node to draw line from.
    xl = x1 + r*(x2-x1)/d;
    yl = y1 + r*(y2-y1)/d;

    xr = x2 + r*(x1-x2)/d;
    yr = y2 + r*(y1-y2)/d;

	//Draw line.
	drawLine(xl, yl, xr, yr);
}