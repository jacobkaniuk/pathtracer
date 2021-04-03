#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "pixel.h"

using constants::image::pixel::colors::BLACK;

class ImageBuffer
{
private:
	std::vector<Pixel> _pixels;
	int _width;
	int _height;
	BitDepth _bitdepth;
	Pixel& _at(const int &x, const int &y);

public:
	ImageBuffer(const constants::image::resolutions& resolution, const BitDepth& bit_depth=BitDepth::R8G8B8, const color::Color& fill_color=BLACK);
	ImageBuffer(const int & width, const int & height, const BitDepth& bit_depth=R8G8B8, const color::Color& fill_color=BLACK);
	ImageBuffer();
	~ImageBuffer(){};

	int width() const {return _width;};
	int height() const {return _height;};
	BitDepth bit_depth() const {return _bitdepth;};
	std::vector<Pixel> pixel_data() const {return _pixels;};
	
	void fill_buffer(const color::Color& color);
	void set_pixel(const int &x, const int &y, const color::Color &color);
	Pixel& get_pixel(const int &x, const int &y);

	void fill(const color::Color &color);
	void fill(std::vector<Pixel> &pixels, const color::Color &color);

	void fill_min();
	void fill_max();

	void dump(std::filebuf& file_buffer, std::ostream& output);
};

#endif // IMAGEBUFFER_H