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
	geomap(int new_width, int new_height, int new_count_of_plates, double speed = 1, double level_of_unevenness = 0.5);
	~geomap();
	Bitmap^ create_bitmap_of_plates();
	void do_one_step();
	Bitmap^ create_bitmap_of_height();
	double** geomap::get_altitude_map() {
		double** new_altitude_map;
		std::copy(altitude_map, altitude_map + width * height, new_altitude_map);
		return new_altitude_map;
	}
	int get_width() {return width;};
	int get_height() {return height;};
	double get_min_altitude() {return min_altitude;};
	double get_max_altitude() {return max_altitude;};
	unsigned long long get_years() {return years;};
};