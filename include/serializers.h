#ifndef SERIALIZERS_H
#define SERIALIZERS_H

#include <vector>
#include <cmath>
#include <cstdint>
#include <filesystem>

#include "pixel.h"
#include "image_buffer.h"

class Serializer {
protected:
    const char* _file_path;
    const char* _name;
    const char* _ext_type;
    uint32_t _width;
    uint32_t _height;
    uint8_t _bit_depth;
    bool _has_alpha;
    uint8_t _bits_per_channel;

    virtual void _write_to_file(void) = 0;
};

class BMPSerializer : Serializer {
// Format info pulled from http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm
protected:
    void _set_pixel_data(std::vector<Pixel> pixel_data);
    void _set_pixel_data(uint8_t* pixel_data);
    void _write_to_file(const char* file_path);
private: 
    // Header
    char _header_signature[2]={'B', 'M'};
    uint32_t _file_size;         // width * height * sizeof(bit_depth) * 3
    uint32_t _reserved = 0;
    uint32_t _data_offset = 0;
    // InfoHeader
    uint32_t _size = 40;
    uint32_t _width;             // image width
    uint32_t _height;            // image height
    uint16_t _planes = 1;
    uint16_t _bits_per_pixel;    // channel bit depth (1 monochrome, 4 bit palletized, 8 bit palletized, 16 bit, 24bit)
    uint32_t _compression;       //0 = BI_RGB no compression, 1 = BI_RLE8 8bit RLE encoding, 2 = BI_RLE4 4bit RLE encoding
    uint32_t _image_size;        // It is valid to set this =0 if Compression = 0
    uint32_t _x_pixels_per_m;    // horizontal resolution: pixels/meter
    uint32_t _y_pixels_per_m;    // vertical resolution: pixels/meter
    uint32_t _colors_used = std::pow(2, _bits_per_pixel);       // number of colors in the color pallet 2^_bits_per_pixel/bit depth
    uint32_t _imporant_colors = 0;    
    // PixelData
    uint8_t* _pixel_data;        // array holding all pixel data. pixels will be written out using offsets of byte * bit depth

public:
    BMPSerializer(const char* file_path, const uint8_t& width, const uint8_t& height, const BitDepth& bit_depth, std::vector<Pixel>& pixel_data, const uint8_t& compression=0);
    BMPSerializer(const char* file_path, ImageBuffer& image_buffer);
    BMPSerializer(const BMPSerializer& copy);
    ~BMPSerializer(){};
    void static write_to_file(const char* file_path, ImageBuffer& image_buffer);
};

#endif // SERIALIZERS_H