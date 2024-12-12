#include <cmath>
#include "lithospheric_plates.h"

using namespace System::Drawing;
using namespace System::Drawing::Imaging;

const int left_red = 0;
const int left_green = 255;
const int left_blue = 0;
const int right_red = 159;
const int right_green = 39;
const int right_blue = 8;


Bitmap^ create_bitmap_of_height( geomap* const  my_geomap) {
	double** height_map = my_geomap->get_copy_altitude_map();
	int width, height;
	double min_altitude, max_altitude;
	min_altitude = my_geomap->get_min_altitude();
	max_altitude = my_geomap->get_max_altitude();
	width = my_geomap->get_width();
	height = my_geomap->get_height();
	Bitmap^ bmp = gcnew Bitmap(width, height, PixelFormat::Format32bppArgb);

	for (int i = 1; i < width; i++) {
		for (int j = 1; j < height; j++) {
			int curr_red = abs(right_red - round(height_map[i][j] * abs(right_red - left_red) / max_altitude));
			int curr_green = abs(right_green - round(height_map[i][j] * abs(right_green - left_green) / max_altitude));
			int curr_blue = abs(right_blue - round(height_map[i][j] * abs(right_blue - left_blue) / max_altitude));
		
			bmp->SetPixel(i, j, System::Drawing::Color::FromArgb(curr_red, curr_green, curr_blue));
		}
	}
	return bmp;
}