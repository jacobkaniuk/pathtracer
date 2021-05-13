#include <assert.h>
#include <mutex>

#include "image_buffer.h"

using namespace constants::layer::pixel::colors;


ImageBuffer::ImageBuffer(const display::resolution& resolution, const BitDepth& bit_depth, const color::Color& fill_color) : _bitdepth(bit_depth)
{
	_width = display::get_resolution_values(resolution).first;
	_height = display::get_resolution_values(resolution).second;
	_pixels.reserve(_width*_height);
	fill_buffer(fill_color);
};

ImageBuffer::ImageBuffer(const int & width, const int & height, const BitDepth& bit_depth, const color::Color& fill_color) : _width(width), _height(height), _bitdepth(bit_depth)
{
	_pixels.reserve(width*height);
	fill_buffer(fill_color);
};

ImageBuffer::ImageBuffer(const ImageBuffer& copy): _pixels(copy._pixels), _width(copy._width), _height(copy._height), _bitdepth(copy._bitdepth){};

ImageBuffer::ImageBuffer(ImageBuffer&& rval_copy):  _pixels(rval_copy._pixels), _width(rval_copy._width), _height(rval_copy._height), _bitdepth(rval_copy._bitdepth){};

ImageBuffer::ImageBuffer(): _bitdepth(BitDepth::R8G8B8A8), _width(1920), _height(1080) {
	_pixels.reserve(_width*_height);
	fill_buffer(RGBA::EMPTY);
};

void ImageBuffer::fill_buffer(const color::Color& color) {
	for (int i=0;i<=_width*_height;i++){
		_pixels.push_back(Pixel(color, _bitdepth));
	}
};

Pixel& ImageBuffer::_at(const int& x, const int& y) {
	assert (0 <= x <= _width);
	assert (0 <= y <= _height);
	// convert from 2D coordinate into 1D coord as data is stored 1D
	return _pixels.at(_width*y + (x + 1));
};

Pixel& ImageBuffer::_at(const int& index) {
	assert (0 <= index <= size());
	return _pixels.at(index);
};

void ImageBuffer::set_pixel(const int & x, const int & y, const color::Color& color) {
	assert (0 <= x <= _width);
	assert (0 <= y <= _height);
	// convert from 2D coordinate into 1D coord as data is stored 1D
	_at(x,y).set_color(color);
}

void ImageBuffer::set_pixel(int index, const color::Color &color){
	
	_at(index).set_color(color);
};

void ImageBuffer::set_pixel(int index, WIDE x, WIDE  y, WIDE z, WIDE w){
	assert(0 <= index >= size());
	_at(index).set_value(x,y,z,w);
};

Pixel& ImageBuffer::get_pixel(const int & x, const int & y) {
	assert (0 <= x <= _width);
	assert (0 <= y <= _height);
	return _at(x, y);
}

Pixel& ImageBuffer::get_pixel(const int& index) {
	assert (0 <= index <= size());
	return _at(index);
}

void ImageBuffer::clear(){
	WIDE min_val = _pixels[0].min_value();
	for (auto& p : _pixels){
		p[0] = min_val;
		p[1] = min_val;
		p[2] = min_val;
		p[3] = min_val;
	}
}

void ImageBuffer::fill(const color::Color &color) {
	for (auto & p : _pixels){
		color::Color col = color;
		//std::cout << col.x() << col.y() << col.z() << col.w() << std::endl;
		p.set_color(color);
	}
};
void ImageBuffer::fill(std::vector<Pixel> &pixels, const color::Color &color) {
	for (auto& p : pixels){
		p.set_color(color);
	}
};
void ImageBuffer::fill_min(){
	for (auto & p : _pixels){
		p.set_color(RGBA::BLACK);
	}
};
void ImageBuffer::fill_max(){
	for (auto & p : _pixels){
		p.set_color(RGBA::WHITE);
	}
};
