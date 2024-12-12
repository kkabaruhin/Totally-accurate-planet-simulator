#pragma once
#include <windows.h>
#include <iostream>

double distance_between_points(double x1, double y1, double x2, double y2);

using namespace System::Drawing;
using namespace System::Drawing::Imaging;

class geomap {
private:
	struct plate
	{
		double x, y, delta_x, delta_y, r;
	};

	plate* plates;
	double** altitude_map;
	double min_altitude, max_altitude;
	int width, height, count_of_plates;
	unsigned long long years;
	void change_altitude_map();
public:
	/*const int altitude_left_red = 212;
	const int altitude_left_green = 127;
	const int altitude_left_blue = 16;
	const int altitude_right_red = 181;
	const int altitude_right_green = 47;
	const int altitude_right_blue = 14;*/
	const int altitude_left_red = 0;
	const int altitude_left_green = 255;
	const int altitude_left_blue = 0;
	const int altitude_right_red = 255;
	const int altitude_right_green = 0;
	const int altitude_right_blue = 0;
	
	geomap(int new_width, int new_height, int new_count_of_plates, double speed = 1, double level_of_unevenness = 0.5);
	~geomap();
	Bitmap^ create_bitmap_of_plates();
	Bitmap^ create_bitmap_of_height();
	void do_one_step();
	double** get_copy_altitude_map();
	System::Drawing::Color get_altitude_color(double altitude);
	int get_width() {return width;};
	int get_height() {return height;};
	double get_min_altitude() {return min_altitude;};
	double get_max_altitude() {return max_altitude;};
	unsigned long long get_years() {return years;};
};