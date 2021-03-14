#ifndef PIXEL_H
#define PIXEL_H

#include <math.h>
#include <cmath>
#include <algorithm>

// pixel data will be stored as 
#define WIDE long long int

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

/*
class PixelData
{
private:
	WIDE _x;
	WIDE _y;
	WIDE _z;
	WIDE _w;

public:
	PixelData();
	PixelData(const WIDE& x, const WIDE& y, const WIDE& z, const WIDE& w);
	~PixelData();
	friend class Pixel;
};

PixelData::PixelData()
{
}

inline PixelData::PixelData(const WIDE & x, const WIDE & y, const WIDE & z, const WIDE & w) : _x(x), _y(y), _z(z), _w(w) {};

PixelData::~PixelData()
{
}
*/

class Pixel
{
private:
	void _set_new_min(const BitDepth& bit_depth);
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
	Pixel(const color::ColorRGB& color);
	Pixel(const color::ColorRGBA& color);
	Pixel(const color::ColorCMYK& color);
	Pixel(const BitDepth& bit_depth = R8G8B8) { _set_new_min(bit_depth); };
	~Pixel() {};

	set_color(const color::ColorRGB& color);
	set_color(const color::ColorRGBA& color);
	set_color(const color::ColorCMYK& color);
	
	Pixel* value() { return this; };
	void change_bit_depth(const BitDepth& bit_depth);
	BitDepth current_bit_depth() { return _bit_depth; }
};

#endif // PIXEL_H