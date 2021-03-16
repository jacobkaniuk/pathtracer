#include "serializers.h"

BMPSerializer::BMPSerializer(const char* file_path, const uint8_t& width, const uint8_t& height, const BitDepth& bit_depth, std::vector<Pixel>& pixel_data, const uint8_t& compression) {
    this->_file_path = file_path;
    this->_width = width;
    this->_height = height;
    this->_bit_depth = bit_depth_value(bit_depth);
    this->_compression = compression;
    this->_set_pixel_data(pixel_data);
};
BMPSerializer::BMPSerializer(const char* file_path, ImageBuffer& image_buffer){
    this->_file_path = file_path;
    this->_width = image_buffer.width();
    this->_height = image_buffer.height();
    this->_bit_depth = bit_depth_value(image_buffer.bit_depth());
    this->_set_pixel_data(image_buffer.pixel_data());
};
BMPSerializer::BMPSerializer(const BMPSerializer& copy){

};

void BMPSerializer::_write_to_file(const char* file_path){

};

void BMPSerializer::write_to_file(const char* file_path, ImageBuffer& image_buffer){

};

void BMPSerializer::_set_pixel_data(std::vector<Pixel> pixel_data){
    // make space based on the bit depth we're dealing with. data/pixel values are read by
    // the BMP format by using the bit depth flag as an offset for each pixel's channel. since we
    // know our image buffer's pixels store 4 signed longs, each of which take 64 bits, if we're
    // only exporting an 8 or 16 bit image, we need to calculate this size ourselves so both buffers align
    _pixel_data = static_cast<uint8_t*>(malloc(pixel_data.size() * (_bit_depth/sizeof(uint8_t))));
    int index = 0;
    for (auto& p : pixel_data){\
        // TODO shift and mask our 64 bit values to convert them to current bit depth so they
        // align correctly in our _pixel_data byte array
        signed long r, g, b;
        r =p[0]; g = p[1]; b =p[2];
        uint8_t end, mid, base;
        for (int i=0;i<3;i++){
            ;
        }
    }    
};

void BMPSerializer::_set_pixel_data(uint8_t* pixel_data){
    _pixel_data = pixel_data;
};