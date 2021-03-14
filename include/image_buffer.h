#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include <vector>
#include "Pixel.h"

class ImageBuffer
{
private:
	std::vector<Pixel *> _pixels;
	int _width;
	int _height;
	BitDepth _bitdepth;
	Pixel *_at(const int &x, const int &y);

public:
	ImageBuffer(const int & width, const int & height, const BitDepth& bit_depth, const color::Color& fill_color);
	ImageBuffer(const int &width, const int &height, const BitDepth &bit_depth);
	ImageBuffer();
	~ImageBuffer(){};
	void set_pixel(const int &x, const int &y, const color::Color &color);
	Pixel *get_pixel(const int &x, const int &y);

	void fill(const color::Color &color);
	void fill(std::vector<Pixel *> &pixels, const color::Color &color);

	void fill_min();
	void fill_max();
};

#endif // IMAGEBUFFER_H