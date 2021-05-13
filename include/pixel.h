#ifndef PIXEL_H
#define PIXEL_H

#include <math.h>
#include <cmath>
#include <algorithm>
#include <unordered_map>

#include "color.h"
#include "constants.h"

#define WIDE signed long long int

enum BitDepth {
	// Unsigned values
	R8G8B8,
	R16G16B16,
	R32G32B32,
	// including alpha channels
	R8G8B8A8,
	R16G16B16A16,
	R32G32B32A32,
	A8,
	A16,
	A32,

	// Signed values
	NEG_R8G8B8,
	NEG_R16G16B16,
	NEG_R32G32B32,
	// including alpha channels
	NEG_R8G8B8A8,
	NEG_R16G16B16A16,
	NEG_R32G32B32A32,
	NEG_A8,
	NEG_A16,
	NEG_A32,
};

int bit_depth_value(const BitDepth& bit_depth);

class Pixel
{
private:
	void _set_range_from_bit_depth(const BitDepth& bit_depth);
	void _convert_depth(WIDE& min, WIDE& max);
	
	BitDepth _bit_depth;
	// pixel data range
	WIDE _max_value;
	WIDE _min_value;
	// pixel data values
	WIDE _x;
	WIDE _y;
	WIDE _z;
	WIDE _w;

public:
	Pixel(const color::Color& color, const BitDepth& bit_depth = R8G8B8A8);
	Pixel(bool empty = true, const BitDepth& bit_depth = R8G8B8A8);
	~Pixel() {};

	const color::ColorRGBA value() { return color::ColorRGBA(_x, _y, _z, _w); };
	
	void set_x(WIDE x){ _x = x;};
	void set_y(WIDE y){ _y = y;};
	void set_z(WIDE z){ _z = z;};
	void set_w(WIDE w){ _w = w;};

	const WIDE& max_value(){return _max_value;};
	const WIDE& min_value(){return _min_value;};

	void set_color(const color::Color& color);
	void set_value(WIDE x, WIDE y, WIDE z, WIDE w);
		
	void change_bit_depth(const BitDepth& bit_depth);
	BitDepth current_bit_depth() { return _bit_depth; }

	WIDE& operator [] (const int& index);
	const bool operator ==(const Pixel& other) const;
};

#endif // PIXEL_H