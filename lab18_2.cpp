#include<iostream>
using namespace std;

struct Rect{
	double x,y,w,h;
};

double overlap(Rect* R1, Rect* R2) {
    double x_left   = max(R1->x, R2->x);
    double y_top    = min(R1->y, R2->y);
    double x_right  = min(R1->x + R1->w, R2->x + R2->w);
    double y_bottom = max(R1->y - R1->h, R2->y - R2->h);
    if (x_right <= x_left || y_bottom >= y_top) return 0;
    return (x_right - x_left) * (y_top - y_bottom);
}

int main(){
	Rect R1 = {1,1,5,5};
	Rect R2 = {2,2,5,5};	
	cout << overlap(&R1,&R2);
	
	return 0;
}
