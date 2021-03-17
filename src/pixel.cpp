#include <assert.h>
#include <iostream>
#include <map>

#include "pixel.h"

using constants::image::pixel::colors::BLACK;

Pixel::Pixel(const color::Color& color, const BitDepth& bit_depth): _bit_depth(bit_depth){
	_set_range_from_bit_depth(_bit_depth); 
	set_color(color);
};

Pixel::Pixel(const color::Color& color): _bit_depth(BitDepth::R8G8B8A8) {
	_set_range_from_bit_depth(_bit_depth); 
	set_color(color);
};

Pixel::Pixel(const BitDepth& bit_depth): _bit_depth(bit_depth){
	_set_range_from_bit_depth(bit_depth); 
	set_color(BLACK);
};

Pixel::Pixel(bool empty): _bit_depth(BitDepth::R8G8B8A8){
	_set_range_from_bit_depth(_bit_depth);
	
	if (!empty){
		set_color(BLACK);	
	}
};

Pixel::Pixel()
{
	_bit_depth = BitDepth::R8G8B8A8;
	_set_range_from_bit_depth(_bit_depth); 
	set_color(BLACK);
};

void Pixel::_set_range_from_bit_depth(const BitDepth & bit_depth)
{
	switch (bit_depth) {
	// Unsigned/positive values
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

	// Signed/negative values
	case BitDepth::NEG_R8G8B8:
	case BitDepth::NEG_R8G8B8A8:
	case BitDepth::NEG_A8:
		_min_value = -128;
		_max_value = 127;
		break;
	case BitDepth::NEG_R16G16B16:
	case BitDepth::NEG_R16G16B16A16:
	case BitDepth::NEG_A16:
		_min_value = -32'768;
		_max_value = 32'767;
		break;
	case BitDepth::NEG_R32G32B32:
	case BitDepth::NEG_R32G32B32A32:
	case BitDepth::NEG_A32:
		_min_value = -2'147'483'648;
		_max_value = 2'147'483'647;
		break;
	}
}

void Pixel::_convert_depth(WIDE& min, WIDE& max)
{
	_x = std::clamp(_x, min, max);
	_y = std::clamp(_y, min, max);
	_z = std::clamp(_z, min, max);
	_w = std::clamp(_w, min, max);
}

void Pixel::change_bit_depth(const BitDepth & bit_depth)
{
	_bit_depth = bit_depth;
	_set_range_from_bit_depth(_bit_depth);
}

void Pixel::set_color(const color::Color& color){
	switch(_bit_depth){
		case BitDepth::A8:
		case BitDepth::A16:
		case BitDepth::A32:
		case BitDepth::R8G8B8:
		case BitDepth::R8G8B8A8:
		case BitDepth::R16G16B16:
		case BitDepth::R16G16B16A16:
		case BitDepth::R32G32B32:
		case BitDepth::R32G32B32A32:
			// cast as float before we set to correct value based on current bit depth	
			_x = (WIDE)(float)(color.x() * _max_value);
			_y = (WIDE)(float)(color.y() * _max_value);
			_z = (WIDE)(float)(color.z() * _max_value);
			_w = (WIDE)(float)(color.w() * _max_value);
		case BitDepth::NEG_A8:
		case BitDepth::NEG_A16:
		case BitDepth::NEG_A32:
		case BitDepth::NEG_R8G8B8:
		case BitDepth::NEG_R8G8B8A8:
		case BitDepth::NEG_R16G16B16:
		case BitDepth::NEG_R16G16B16A16:
		case BitDepth::NEG_R32G32B32:
		case BitDepth::NEG_R32G32B32A32:
			// cast as float before we set to correct value based on current bit depth	
			_x = (WIDE)(float)((_max_value - _min_value) * color.x() + _min_value);
			_y = (WIDE)(float)((_max_value - _min_value) * color.y() + _min_value);
			_z = (WIDE)(float)((_max_value - _min_value) * color.z() + _min_value);
			_w = (WIDE)(float)((_max_value - _min_value) * color.w() + _min_value);
	}
};

 WIDE& Pixel::operator [] (const int& index) {
	 assert (index >= 0 && index <= 3);
	 switch (index) {
		case 0:
			return _x;
			break;
		case 1:
			return _y;
			break;
		case 2:
			return _z;
			break;
		case 3:
			return _w;
			break;
	 }
};

int bit_depth_value(const BitDepth& bit_depth){
	std::unordered_map<int, int> enum_to_values = {
		// 8 bit color
		{BitDepth::A8, 8},
		{BitDepth::R8G8B8, 8},
		{BitDepth::R8G8B8A8, 8},
		{BitDepth::NEG_A8, 8},
		{BitDepth::NEG_R8G8B8, 8},
		{BitDepth::NEG_R8G8B8A8, 8},
		// 16 bit color
		{BitDepth::A16, 16},
		{BitDepth::R16G16B16, 16},
		{BitDepth::R16G16B16A16, 16},
		{BitDepth::NEG_A16, 16},
		{BitDepth::NEG_R16G16B16, 16},
		{BitDepth::NEG_R16G16B16A16, 16},
		// 32 bit color
		{BitDepth::A32, 32},
		{BitDepth::R32G32B32, 32},
		{BitDepth::R32G32B32A32, 32},
		{BitDepth::NEG_A32, 32},
		{BitDepth::NEG_R32G32B32, 32},
		{BitDepth::NEG_R32G32B32A32, 32}
	};

	return enum_to_values[bit_depth];
};
