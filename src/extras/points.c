/*
* points:  Implements examples from sections 6.1 and 6.2
*/

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Constants

#define XMAX 320
#define YMAX 200

// Macros

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

// Define the point and rectangle structures

struct point {
	int x;
	int y;
};

struct rect {
	struct point p1;
	struct point p2;
};

/*
 * makepoint():  creates a point for 'x' and 'y' components
 */

static struct point makepoint(const int x, const int y) {

	struct point temp;

	temp.x = x;
	temp.y = y;

	return temp;
}

/*
 * addpoint():  adds two points
 */

static struct point addpoint(struct point p1, const struct point p2) {

	p1.x += p2.x;
	p1.y += p2.y;

	return p1;
}

/*
 * origindist(): returns the distance between a point and the origin
 */

static double origindist(const struct point pt) {
	return sqrt((double)pt.x * pt.x + (double)pt.y * pt.y);
};

/*
 * canonrect(): canonicalize the coordinates of a rectangle
 */

static struct rect canonrect(const struct rect r) {

	struct rect temp;

	temp.p1.x = min(r.p1.x, r.p2.x);
	temp.p1.y = min(r.p1.y, r.p2.y);
	temp.p2.x = max(r.p1.x, r.p2.x);
	temp.p2.y = max(r.p1.y, r.p2.y);

	return temp;
}

/*
 * ptinrect(): returns true if p is inside r
 */

static bool ptinrect(const struct point p, struct rect r) {

	struct rect temp;

	temp = canonrect(r);

	return p.x >= temp.p1.x && p.x < temp.p2.x && p.y >= temp.p1.y && p.y < temp.p2.y;
};

/*
 * main
 */

int main(void) {

	struct point  pt;
	struct point  origin = { 0, 0 };
	struct point  maxpt = { XMAX, YMAX };
	struct point  middle;
	struct point  outside;
	struct rect   screen;
	struct rect   noncanon;
	struct rect   canon;
	struct point *porigin;  // A pointer to the origin point

	// Assign a value to a point using a function

	pt = makepoint(10, 20);

	// Assign two points to a rectangle (using assignment of elements and a point)

	screen.p1.x = 0;
	screen.p1.y = 0;
	screen.p2   = maxpt;

	// Make a non-canonical rectangle

	noncanon.p1 = makepoint(200, 400);
	noncanon.p2 = makepoint(113, 42);

	// Make more points using functions

	middle = makepoint((screen.p1.x + screen.p2.x) / 2,
		               (screen.p1.y + screen.p2.y) / 2);

	outside = addpoint(maxpt, maxpt);

	// Make a canonical rectangle out of one that we know is not

	canon = canonrect(noncanon);

	// Make a pointer to a point structure

	porigin = &origin;

	// Display results

	printf("Point 'pt' is at coordinates (%d, %d)\n", pt.x, pt.y);
	printf("Point 'origin' is at coordinate (%d, %d)\n", (*porigin).x, (*porigin).y);
	printf("Or, when we access it another way with '->' it is still at (%d, %d)\n", porigin->x, porigin->y);
	printf("Point 'maxpt' is at coordinates (%d, %d)\n", maxpt.x, maxpt.y);
	printf("This point added with itself is (%d, %d)\n", outside.x, outside.y);
	printf("The distance between 'pt' and the origin is %f\n", origindist(pt));
	printf("Rectangle 'screen' is defined by points (%d, %d) and (%d, %d)\n", screen.p1.x, screen.p1.y, screen.p2.x, screen.p2.y);
	printf("The midpoint between these two points is (%d, %d)\n", middle.x, middle.y);
	printf("Is the midpoint inside the rectangle 'screen'?  %s\n", ptinrect(middle, screen) ? "Yes" : "No");	
	printf("Is point (%d, %d) inside the rectangle 'screen'?  %s\n", outside.x, outside.y, ptinrect(outside, screen) ? "Yes" : "No");
	printf("A non-canonical rectange example is defined by (%d, %d) and (%d, %d)\n", noncanon.p1.x, noncanon.p1.y, noncanon.p2.x, noncanon.p2.y);
	printf("And it's canonical version is (%d, %d) and (%d, %d)\n", canon.p1.x, canon.p1.y, canon.p2.x, canon.p2.y);

	exit(EXIT_SUCCESS);
}