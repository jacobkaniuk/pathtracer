#include <stdio.h>

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

void BMPSerializer::_write_to_file(const char* file_path, ImageBuffer& image_buffer){
    std::filebuf dump_file;
	dump_file.open(std::string(file_path).c_str(), std::ios::out);
	std::ostream os(&dump_file);
    _set_pixel_data(image_buffer.pixel_data());    
};

void BMPSerializer::write_to_file(const char* file_path, ImageBuffer& image_buffer){

};

void BMPSerializer::_set_pixel_data(std::vector<Pixel> pixel_data){
    // make space based on the bit depth we're dealing with. data/pixel values are read by
    // the BMP format by using the bit depth flag as an offset for each pixel's channel. since we
    // know our image buffer's pixels store 4 signed longs, each of which take 64 bits, if we're
    // only exporting an 8 or 16 bit image, we need to calculate this size ourselves so both buffers align
    char channel_count = 4;
    // 8bits/8 -> 1 byte per channel // 16bits/8 -> 2 bytes per channel
    char channel_size = bit_depth_value(pixel_data[0].current_bit_depth()) / 8;  
    int buffer_size = (pixel_data.size()-1) * channel_count * channel_size;
    _pixel_data = new uint8_t[buffer_size];

for (int i=0; i < pixel_data.size()-1; i++ ){
            switch (pixel_data[0].current_bit_depth())
            {
            case BitDepth::A8:
            case BitDepth::R8G8B8:
            case BitDepth::R8G8B8A8:
                _pixel_data[(i*4)-1] = pixel_data[i][3];  // A
                _pixel_data[(i*4)-2] = pixel_data[i][0];  // R
                _pixel_data[(i*4)-3] = pixel_data[i][1];  // G
                _pixel_data[(i*4)-4] = pixel_data[i][2];  // B
                break;
            case BitDepth::A16:
            case BitDepth::R16G16B16:
            case BitDepth::R16G16B16A16:
            // shift and mask the first 16 bits of our 64 bit values to in order to write to our 8 bit array
            // correctly. the BMP reader will use the flag _bits_per_pixel value to determine the offset when
            // reading in the data byte by byte.
                // ie. 65'535 -> 1111 1111 1111 1111 -> base 8 bits 255, tail 8 bits 255
                //                                          (1111 1111)     (1111 1111)
                //     32'767 -> 0111 1111 1111 1111 -> base 8 bits 127, tail 8 bits 255
                //                                          (0111 1111)     (1111 1111)
                
                // base nibbles ( first 8 bits of 16 bit)
                _pixel_data[(i*8)-2] = (pixel_data[i][3] >> 8) & 0xff;  // A
                _pixel_data[(i*8)-4] = (pixel_data[i][0] >> 8) & 0xff;  // R
                _pixel_data[(i*8)-6] = (pixel_data[i][1] >> 8) & 0xff;  // G
                _pixel_data[(i*8)-8] = (pixel_data[i][2] >> 8) & 0xff;  // B
                // tail nibbles ( bits 9 to 16 bits of 16 bit)
                _pixel_data[(i*8)-1] = pixel_data[i][3] & 0xff;  // A
                _pixel_data[(i*8)-3] = pixel_data[i][0] & 0xff;  // R
                _pixel_data[(i*8)-5] = pixel_data[i][1] & 0xff;  // G
                _pixel_data[(i*8)-7] = pixel_data[i][2] & 0xff;  // B
                break;

            case BitDepth::A32:
            case BitDepth::R32G32B32:
            case BitDepth::R32G32B32A32:
            // same as above, but we use first 24 bits of our value
                // base nibbles ( first 8 bits of 24 bits)
                _pixel_data[(i*12)-3]  = (pixel_data[i][3] >> 16) & 0xff;  // A
                _pixel_data[(i*12)-6]  = (pixel_data[i][0] >> 16) & 0xff;  // R
                _pixel_data[(i*12)-9]  = (pixel_data[i][1] >> 16) & 0xff;  // G
                _pixel_data[(i*12)-12] = (pixel_data[i][2] >> 16) & 0xff;  // B
                // middle nibbles ( bits 9 to 16)
                _pixel_data[(i*12)-2]  = (pixel_data[i][3] >> 8) & 0xff;  // A
                _pixel_data[(i*12)-5]  = (pixel_data[i][0] >> 8) & 0xff;  // R
                _pixel_data[(i*12)-8]  = (pixel_data[i][1] >> 8) & 0xff;  // G
                _pixel_data[(i*12)-11] = (pixel_data[i][2] >> 8) & 0xff;  // B
                // tail nibbles ( bits 17 to 24)
                _pixel_data[(i*12)-1]  = pixel_data[i][3] & 0xff;  // A
                _pixel_data[(i*12)-4]  = pixel_data[i][0] & 0xff;  // R
                _pixel_data[(i*12)-8]  = pixel_data[i][1] & 0xff;  // G
                _pixel_data[(i*12)-12] = pixel_data[i][2] & 0xff;  // B
                break;
            default:
                break;
            }
        }

        // for (int i=0; i< 24; i++){
        // std::cout << static_cast<int>(_pixel_data[i]) << std::endl;  
        // }
    };

void BMPSerializer::_set_pixel_data(uint8_t* pixel_data){
    _pixel_data = pixel_data;
};