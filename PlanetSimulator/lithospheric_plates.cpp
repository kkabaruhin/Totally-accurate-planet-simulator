#include <windows.h>
#include <iostream>
#include "lithospheric_plates.h"

using namespace System::Drawing;
using namespace System::Drawing::Imaging;

double distance_between_points(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

geomap::geomap(int new_width, int new_height, int new_count_of_plates, double speed, double level_of_unevenness) {
	this->width = new_width;
	this->height = new_height;
	this->count_of_plates = new_count_of_plates;
	this->years = 0;
	altitude_map = new double* [width];
	for (int i = 0; i < width; i++)
	{
		altitude_map[i] = new double[height];
		for (int j = 0; j < height; j++)
			altitude_map[i][j] = 0;
	}
	min_altitude = 0;
	max_altitude = 0;

	double area = this->width * this->height;
	double sum_area_plates = area * level_of_unevenness; 

	plates = new plate[count_of_plates]{};

	for (int i = 0; i < count_of_plates; i++) {
		double x, y, delta_x, delta_y, r;
		x = rand() % (this->width - 1) + 1;
		y = rand() % (this->height - 1) + 1;
		delta_x = ((rand() + 1) % (int)(speed * 1000 * 2) * (rand() % 2 * 2 - 1)) / 100.0; 
		delta_y = ((rand() + 1) % (int)(speed * 1000 * 2) * (rand() % 2 * 2 - 1)) / 100.0; 
		r = (((rand() + 1) % 1000 - 500) / 1000.0 + 1) * sqrt(sum_area_plates / (3.14159 * count_of_plates));
		plate current_plate{ x, y, delta_x, delta_y , r };
		plates[i] = current_plate;
	}
}

geomap::~geomap() {
	delete[] plates;
	for (int i = 0; i < width; i++)
		delete[] altitude_map[i];
	delete[] altitude_map;
};

Bitmap^ geomap::create_bitmap_of_plates() {

	Bitmap^ bmp = gcnew Bitmap(this->width, this->height, PixelFormat::Format32bppArgb);
	for (int i = 0; i < count_of_plates; i++)
	{
		bmp->SetPixel((int)(plates[i].x), (int)(plates[i].y), Color::Red);
		bmp->SetPixel((int)(plates[i].x), (int)(plates[i].y), Color::Red);
		bmp->SetPixel((int)(plates[i].x), (int)(plates[i].y), Color::Red);
		bmp->SetPixel((int)(plates[i].x), (int)(plates[i].y), Color::Red);
	}
	for (int i = 1; i < this->width; i++) {
		for (int j = 1; j < this->height; j++) {
			for (int k = 0; k < count_of_plates; k++) {
				if (abs(distance_between_points(i, j, plates[k].x, plates[k].y) - plates[k].r) < 2) {
					bmp->SetPixel(i, j, Color::Black);
				}
			}
		}
	}
	return bmp;
}

Bitmap^ geomap::create_bitmap_of_height() {
	Bitmap^ bmp = gcnew Bitmap(width, height, PixelFormat::Format32bppArgb);

	for (int i = 1; i < width; i++) {
		for (int j = 1; j < height; j++) {

			bmp->SetPixel(i, j, get_altitude_color(altitude_map[i][j]));
		}
	}
	return bmp;
}
	
void geomap::change_altitude_map() {
	for (int i = 1; i < width; i++) {
		for (int j = 1; j < height; j++) {
			int count = 0;
			for (int k = 0; k < count_of_plates; k++) 
				if (distance_between_points(i, j, plates[k].x, plates[k].y) < plates[k].r)
					++count;
			altitude_map[i][j] += (count - 1);
			min_altitude = min(min_altitude, altitude_map[i][j]);
			max_altitude = max(max_altitude, altitude_map[i][j]);
		}
	}
}

void geomap::do_one_step() {
	double g = 1;
	for (int i = 0; i < count_of_plates; i++) {
		for (int j = 0; j < count_of_plates; j++) {
			if (i == j) continue;
			if (distance_between_points(plates[i].x, plates[i].y, plates[j].x, plates[j].y) > plates[i].r + plates[j].r) continue;
			double repulsive_force = g / distance_between_points(plates[i].x, plates[i].y, plates[j].x, plates[j].y);
			double speed = distance_between_points(plates[i].x, plates[i].y, plates[i].x + plates[i].delta_x, plates[i].y + plates[i].delta_y);
			double resistance_force = speed / plates[i].r;
			double multiplier = repulsive_force / resistance_force;

			double a1, b1, c1, a2, b2, c2;
			a1 = plates[i].x - plates[j].x;
			b1 = plates[i].y - plates[j].y;
			c1 = sqrt(a1 * a1 + b1 * b1);
			c2 = sqrt(plates[i].delta_x * plates[i].delta_x + plates[i].delta_y * plates[i].delta_y);
			double t = c1 / c2;
			a2 = a1 / t;
			b2 = b1 / t;

			plates[i].delta_x = plates[i].delta_x + multiplier * a2 * (plates[j].r * plates[j].r / (plates[i].r * plates[i].r));
			plates[i].delta_y = plates[i].delta_y + multiplier * b2 * (plates[j].r * plates[j].r / (plates[i].r * plates[i].r));


		}
		double new_x, new_y;
		new_x = plates[i].x + plates[i].delta_x;
		new_y = plates[i].y + plates[i].delta_y;

		if (new_x <= 1 || new_x >= width)
			plates[i].delta_x = -plates[i].delta_x;

		if (new_y <= 1 || new_y >= height)
			plates[i].delta_y = -plates[i].delta_y;

		new_x = plates[i].x + plates[i].delta_x;
		new_y = plates[i].y + plates[i].delta_y;

		if (new_x <= 1 || new_x >= width || new_y <= 1 || new_y >= height)
			continue;

		plates[i].x = new_x;
		plates[i].y = new_y;

	}
	++years;
	change_altitude_map();
}

double** geomap::get_copy_altitude_map() {
	double** new_altitude_map;
	new_altitude_map = new double* [width];
	for (int i = 0; i < width; i++)
	{
		new_altitude_map[i] = new double[height];
		for (int j = 0; j < height; j++)
			new_altitude_map[i][j] = altitude_map[i][j];
	}
	return new_altitude_map;
}

System::Drawing::Color geomap::get_altitude_color(double altitude) {
	
	double multiplier = (abs(altitude - min_altitude) / (max_altitude - min_altitude));

	if (multiplier <= 0 || multiplier > 1 || multiplier != multiplier)
		multiplier = 0;
	int curr_red = (int)(altitude_left_red + (altitude_right_red - altitude_left_red) * multiplier);
	int curr_green = (int)(altitude_left_green + (altitude_right_green - altitude_left_green) * multiplier);
	int curr_blue = (int)(altitude_left_blue + (altitude_right_blue - altitude_left_blue) * multiplier);

	return System::Drawing::Color::FromArgb(curr_red, curr_green, curr_blue);
}
