#include "Pixel.h"

void Pixel::_set_new_min(const BitDepth & bit_depth)
{
	switch (bit_depth) {
	// Signed/positive values
	case BitDepth::R8G8B8:
	case BitDepth::R8G8B8A8:
	case BitDepth::A8:
		_min_value = 0;
		_max_value = 255;
		break;
	case BitDepth::R16G16B16:
	case BitDepth::R16G16B16A16:
	case BitDepth::A16:
		_min_value = 0;
		_max_value = 65'536;
		break;
	case BitDepth::R32G32B32:
	case BitDepth::R32G32B32A32:
	case BitDepth::A32:
		_min_value = 0;
		_max_value = 2'147'483'647;
		break;

	// Unsigned/negative values
	case BitDepth::NEG_R8G8B8:
	case BitDepth::NEG_R8G8B8A8:
	case BitDepth::NEG_A8:
		_min_value = -127;
		_max_value = 128;
		break;
	case BitDepth::NEG_R16G16B16:
	case BitDepth::NEG_R16G16B16A16:
	case BitDepth::NEG_A16:
		_min_value = -32'767;
		_max_value = 32'768;
		break;
	case BitDepth::NEG_R32G32B32:
	case BitDepth::NEG_R32G32B32A32:
	case BitDepth::NEG_A32:
		_min_value = -1'073'741'823;
		_max_value = 1'073'741'823;
		break;
	}
}

Pixel::Pixel(const color::ColorRGB& color) : _x(color.r), _y(color.g), _z(color.b), _w(nullptr){};
Pixel::Pixel(const color::ColorRGBA& color): _x(color.r), _y(color.g), _z(color.b), _w(color.a){};
Pixel::Pixel(const color::ColorCMYK& color): _x(color.c), _y(color.m), _z(color.y), _w(color.k){};

void Pixel::_convert_depth(WIDE& min, WIDE& max)
{
	_x = std::clamp(_x, min, max);
	_y = std::clamp(_y, min, max);
	_y = std::clamp(_z, min, max);
	_y = std::clamp(_w, min, max);
}

void Pixel::change_bit_depth(const BitDepth & bit_depth)
{
	_bit_depth = bit_depth;
}

Pixel::set_color(const color::ColorRGB& color){
	_x = color.r;
	_y = color.g;
	_z = color.b;
	_w = nullptr;
};
Pixel::set_color(const color::ColorRGBA& color){
	_x = color.r;
	_y = color.g;
	_z = color.b;
	_w = color.a;
};
Pixel::set_color(const color::ColorCMYK& color){
	_x = color.c;
	_y = color.m;
	_z = color.y;
	_w = color.k;
};
	