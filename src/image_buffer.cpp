#include <assert.h>
#include <mutex>

#include "image_buffer.h"
#include "constants.h"

void LOG(const char* message){std::cout << message << std::endl;};

using constants::image::pixel::colors::BLACK;


std::pair<int, int> get_resolution_values(const constants::image::resolutions& resolution) {
    std::unordered_map<constants::image::resolutions, std::pair<int, int>> resolutions_to_values = {
		// common 16:9 resolutions
		{constants::image::resolutions::res_360,    std::make_pair(640, 360)},
		{constants::image::resolutions::res_540,    std::make_pair(960, 540)},
        {constants::image::resolutions::res_720,    std::make_pair(1280, 720)},
        {constants::image::resolutions::res_1080,   std::make_pair(1920, 1080)},
        {constants::image::resolutions::res_4k,     std::make_pair(3840, 2160)},
        {constants::image::resolutions::res_8k,     std::make_pair(7680, 4320)},
	};

    return resolutions_to_values[resolution];
};

ImageBuffer::ImageBuffer(const constants::image::resolutions& resolution, const BitDepth& bit_depth, const color::Color& fill_color) : _bitdepth(bit_depth)
{
	_width = get_resolution_values(resolution).first;
	_height = get_resolution_values(resolution).second;
	_pixels.reserve(_width*_height);
	fill_buffer(fill_color);
};

ImageBuffer::ImageBuffer(const int & width, const int & height, const BitDepth& bit_depth, const color::Color& fill_color) : _width(width), _height(height), _bitdepth(bit_depth)
{
	_pixels.reserve(width*height);
	fill_buffer(fill_color);
};

ImageBuffer::ImageBuffer() {
	_bitdepth = BitDepth::R8G8B8A8;
	_width = 1920;
	_height = 1080;
	_pixels.reserve(_width*_height);
	fill_buffer(BLACK);
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
	return _pixels[_width*y + (x + 1)];
};

void ImageBuffer::set_pixel(const int & x, const int & y, const color::Color& color) {
	assert (0 <= x <= _width);
	assert (0 <= y <= _height);
	// convert from 2D coordinate into 1D coord as data is stored 1D
	_at(x,y).set_color(color);
}

Pixel& ImageBuffer::get_pixel(const int & x, const int & y) {
	assert (0 <= x <= _width);
	assert (0 <= y <= _height);
	return _at(x, y);
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
		p.set_color(constants::image::pixel::colors::BLACK);
	}
};
void ImageBuffer::fill_max(){
	for (auto & p : _pixels){
		p.set_color(constants::image::pixel::colors::WHITE);
	}
};

void ImageBuffer::dump(std::filebuf& file_buffer, std::ostream& output) {
	std::mutex mutex;
	std::scoped_lock write_lock(mutex);
	for (int i=0; i<_height;i++){
		for (int j=0; j<_width;j++){
			output << _at(j,i).value();
		}
	}
};