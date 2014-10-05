#ifndef DRAW2D
#define DRAW2D

#include <iostream>
#include <math.h>
using namespace std;

//////////////////////////////////
//								//
//   Line Drawing Algorithm		//
//								//
//////////////////////////////////

// Draw pixel
void drawpixel(int x, int y){
	cout << x << " " << y << endl;
}

// Draw line(k=inf)
void x_straight_draw(int x, int y1, int y2){
	if (y2 < y1){
		swap(y1, y2);
	}
	for (int y = y1; y <= y2; y++){
		drawpixel(x, y);
	}
	return;
}

// Digit Diffential Algorithm(Line)
void dda(int x1, int y1, int x2, int y2){
	// k = inf
	if (x1 == x2){
		x_straight_draw(x1, y1, y2);
	}
	float k = ((float)y2 - y1) / (x2 - x1);
	if (abs(k) <= 1){ // k <= 1
		if (x2 < x1){
			swap(x1, x2);
			swap(y1, y2);
		}
		float y = y1;
		drawpixel(x1, y1);
		for (int x = x1 + 1; x < x2; x++){
			y = y + k;
			drawpixel(x, (int)lroundf(y));
		}
	}
	else{ // k > 1
		float kr = 1 / k;
		if (y2 < y1){
			swap(x1, x2);
			swap(y1, y2);
		}
		float x = x1;
		drawpixel(x1, y1);
		for (int y = y1 + 1; y < y2; y++){
			x = x + kr;
			drawpixel((int)lroundf(x), y);
		}
	}
	drawpixel(x2, y2);
}

// Bresenham Mid-Point Algorithm(Line)
void bresenham(int x1, int y1, int x2, int y2){
	if (x1 == x2){
		x_straight_draw(x1, y1, y2);
	}
	float inc = 1;
	if ((x2 > x1) == (y2 < y1)){
		inc = -1;
	}
	float k = abs(((float)y2 - y1) / (x2 - x1));
	if (k <= 1){
		if (x2 < x1){
			swap(x1, x2);
			swap(y1, y2);
		}
		float y = y1;
		drawpixel(x1, y1);
		float e = -0.5;
		for (int x = x1 + 1; x < x2; x++){
			e = e + k;
			if (e > 0){
				y = y + inc;
				e--;
			}
			drawpixel(x, y);
		}
	}
	else{
		float kr = 1 / k;
		if (y2 < y1){
			swap(x1, x2);
			swap(y1, y2);
		}
		float x = x1;
		drawpixel(x1, y1);
		float e = -0.5;
		for (int y = y1 + 1; y < y2; y++){
			e = e + kr;
			if (e > 0){
				x = x + inc;
				e--;
			}
			drawpixel(x, y);
		}
	}
	drawpixel(x2, y2);
}

// Advanced Bresenham Mid-Point Algorithm
void advanced_bresenham(int x1, int y1, int x2, int y2){
	if (x1 == x2){
		x_straight_draw(x1, y1, y2);
	}
	float inc = 1;
	if ((x2 > x1) == (y2 < y1)){
		inc = -1;
	}
	float k = abs(((float)y2 - y1) / (x2 - x1));
	if (k <= 1){
		if (x2 < x1){
			swap(x1, x2);
			swap(y1, y2);
		}
		int y = y1;
		drawpixel(x1, y1);
		int e = x1 - x2;
		k = (int) 2 * k * (x2 - x1);
		for (int x = x1 + 1; x < x2; x++){
			e = e + k;
			if (e > 0){
				y = y + inc;
				e = e - 2 * (x2 - x1);
			}
			drawpixel(x, y);
		}
	}
	else{
		float kr = 1 / k;
		if (y2 < y1){
			swap(x1, x2);
			swap(y1, y2);
		}
		int x = x1;
		drawpixel(x1, y1);
		int e = y1 - y2;
		kr = (int) 2 * kr * (y2 - y1);
		for (int y = y1 + 1; y < y2; y++){
			e = e + kr;
			if (e > 0){
				x = x + inc;
				e = e - 2 * (y2 - y1);
			}
			drawpixel(x, y);
		}
	}
	drawpixel(x2, y2);
}

//////////////////////////////////
//								//
//   Circle Drawing Algorithm	//
//								//
//////////////////////////////////

// draw eight symmetry points with shift(x0, y0)
void eight_way_draw(int x, int y, int x0, int y0){
	cout << x + x0 << " " << y + y0 << endl;
	cout << x + x0 << " " << -y + y0 << endl;
	cout << -x + x0 << " " << y + y0 << endl;
	cout << -x + x0 << " " << -y + y0 << endl;
	cout << y + x0 << " " << x + y0 << endl;
	cout << -y + x0 << " " << x + y0 << endl;
	cout << y + x0 << " " << -x + y0 << endl;
	cout << -y + x0 << " " << -x + y0 << endl;
}

// draw four symmetry points with shift(x0, y0)
void four_way_draw(int x, int y, int x0, int y0){
	cout << x + x0 << " " << y + y0 << endl;
	cout << x + x0 << " " << -y + y0 << endl;
	cout << -x + x0 << " " << y + y0 << endl;
	cout << -x + x0 << " " << -y + y0 << endl;
}

// Mid-Point Algorithm with Circle
void mid_point_circle(int x0, int y0, int R){
	int x = 0;
	int y = R;
	eight_way_draw(x, y, x0, y0);
	float d = 1.25 - R;

	while (x < y){
		if (d < 0){
			x++;
			d = d + 2 * x + 1;
		}
		else{
			x++;
			y--;
			d = d + 2 * (x - y) + 1;
		}
		eight_way_draw(x, y, x0, y0);
	}
}

void bresenham(int x0, int y0, int R){
	int x = x0;
	int y = y0 + R;
	four_way_draw(x, y, x0, y0);
	float d = 2 - 2 * R;
	float delta = 0;
	while (y > 0){
		if (d < 0){
			delta = 2 * d + 2 * y - 1;
			if (delta <= 0){
				x++;
				d = d + 2 * x + 1;
			}
			else{
				x++;
				y--;
				d = d + 2 * x - 2 * y + 2;
			}
		}else if(d > 0){
			delta = 2 * d - 2 * x - 1;
			if (delta > 0){
				y--;
				d = d - 2 * y + 1;
			}
			else{
				x++;
				y--;
				d = d + 2 * x - 2 * y + 2;
			}
		}
		else{
			x++;
			y--;
			d = d + 2 * x - 2 * y + 2;
		}
		four_way_draw(x, y, x0, y0);
	}
}

//////////////////////////////////
//								//
//   Ellipse Drawing Algorithm	//
//								//
//////////////////////////////////

// Mid-Point Algorithm with Ellipse
void mid_point_ellipse(int x0, int y0, int a, int b){
	int x = 0;
	int y = b;
	four_way_draw(x, y, x0, y0);
	int a2 = a; int b2 = b;	
	float d = b2 + a2 * (0.25 - b);
	while (b2 * (x-1) < a2 * (y-0.5)){ // high part
		if (d < 0){
			x++;
			d = d + b2 * (2 * x + 1);
		}
		else{
			x++;
			y--;
			d = d + b2 * (2 * x + 1) - a2 * (2 * y);
		}
		four_way_draw(x, y, x0, y0);
	}
	d = sqrt(b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2);
	while (y > 0){ // low part
		if (d < 0){
			x++;
			y--;
			d = d + b2 * (2 * x + 1) - a2 * (2 * y);
		}
		else{
			y--;
			d = d - a2 * (2 * y - 1);
		}
		four_way_draw(x, y, x0, y0);
	}
}

void scanline_polygon(int x[], int y[]){

}

int* xd;
int* yd;
int count = 0;

bool is_block(int x[], int y[], int x0, int y0, int n, int xd[], int yd[]){
	bool isblock = false;
	for (int i = 0; i < n; i++){
		if (x[i] == x0 && y[i] == y0){
			isblock = true;
		}
	}
	for (int i = 0; i < 20; i++){
		if (xd[i] == x0 && yd[i] == y0){
			isblock = true;
		}
	}
	return isblock;
}

void area_filling_undecorated(int x[], int y[], int x0, int y0, int n){
	drawpixel(x0, y0);
	xd[::count] = x0; yd[::count] = y0;
	::count++;
	bool isblockl = is_block(x, y, x0 - 1, y0, n, xd, yd);
	bool isblockr = is_block(x, y, x0 + 1, y0, n, xd, yd);
	bool isblocku = is_block(x, y, x0, y0 + 1, n, xd, yd);
	bool isblockd = is_block(x, y, x0, y0 - 1, n, xd, yd);
	if (!(isblockl && isblockr && isblocku && isblockd)){
		if (!isblockl){
			area_filling_undecorated(x, y, x0 - 1, y0, n);
		}
		if (!isblockr){
			area_filling_undecorated(x, y, x0 + 1, y0, n);
		}
		if (!isblocku){
			area_filling_undecorated(x, y, x0, y0 + 1, n);
		}
		if (!isblockd){
			area_filling_undecorated(x, y, x0, y0 - 1, n);
		}
	}
}

void area_filling(int x[], int y[], int x0, int y0, int n){
	int count = 0;
	xd = new int[20];
	yd = new int[20];
	area_filling_undecorated(x, y, x0, y0, n);
}

#endif