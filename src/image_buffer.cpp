#include <assert.h>
#include "image_buffer.h"
#include "constants.h"

using constants::image::pixel::colors::BLACK;


ImageBuffer::ImageBuffer(const int & width, const int & height, const BitDepth& bit_depth) : _width(width), _height(height), _bitdepth(bit_depth)
{
	_pixels.reserve(width*height);
	fill(BLACK);
};

ImageBuffer::ImageBuffer(const int & width, const int & height, const BitDepth& bit_depth, const color::Color& fill_color) : _width(width), _height(height), _bitdepth(bit_depth)
{
	_pixels.reserve(width*height);
	fill(fill_color);
};

ImageBuffer::ImageBuffer()
{
	_width = 1920;
	_height = 1080;
	_pixels.reserve(_width*_height);
	fill(BLACK);
};

Pixel* ImageBuffer::_at(const int& x, const int& y)
{
	assert (0 <= x <= _width);
	assert (0 <= y <= _height);
	// convert from 2D coordinate into 1D coord as data is stored 1D
	return _pixels[_width*y + (x + 1)];
};

void ImageBuffer::set_pixel(const int & x, const int & y, const color::Color& color)
{
	assert (0 <= x <= _width);
	assert (0 <= y <= _height);
	// convert from 2D coordinate into 1D coord as data is stored 1D
	_pixels[_width*y + (x + 1)]->set_color(color);
}

Pixel* ImageBuffer::get_pixel(const int & x, const int & y)
{
	assert (0 <= x <= _width);
	assert (0 <= y <= _height);
	return _at(x, y);
}
