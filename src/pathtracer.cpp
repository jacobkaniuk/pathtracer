#include <iostream>
#include <fstream>
#include <chrono>
#include <assert.h>
#include <string>
#include <string.h>
#include <math.h>
#include <functional>

#include "vector3.hpp"
#include "matrix4.hpp"
#include "ray.hpp"
#include "image_buffer.h"
#include "color.h"
#include "serializers.h"
#include "blend_ops.hpp"
#include "image_layer.h"
#include "image_layer_stack.h"

void LOG(const char* message){std::cout << message << std::endl;};

int main()
{
	// create an empty image buffer
	ImageBuffer image_buffer(display::resolution::res_FHD, BitDepth::R8G8B8A8);
	image_buffer.fill_max();
	image_buffer.fill(constants::layer::pixel::colors::RGBA::BLUE);
	image_buffer.fill(color::Color(1.0f, 1.0f, 0.5f, 0.f));
	
	std::cout << "Value: " << bit_depth_value(BitDepth::R16G16B16) << std::endl;
	std::cout << image_buffer.width() << "x" << image_buffer.height() << std::endl;

	BMPSerializer bmp_writer("C:\\dev\\c++", image_buffer);
	
	image::LayerStack layer_stack = image::LayerStack(image_buffer);
	ImageBuffer copy = ImageBuffer(image_buffer);
	copy.fill(constants::layer::pixel::colors::RGBA::RED);
	
	for (int i=0; i<25; i++){
		ImageBuffer* copy = new ImageBuffer(image_buffer);
		copy->fill(constants::layer::pixel::colors::RGBA::RED);
		std::string layer_name =  std::string("Layer ") + std::to_string(i);
		image::Layer* new_layer = new image::Layer(copy, layer_name);
		layer_stack.add_layer(new_layer);
		std::cout << "Added New Layer: " << layer_name << " " << new_layer << std::endl;
	}

	std::cout << "Done allocating layers" << std::endl;

	layer_stack.move_layer(layer_stack.top_layer, 7);

	std::cout << "Moving layers now" << std::endl;
	std::cout << "Layer Count: " << layer_stack.size() << std::endl;

	image::Layer* temp = (*++layer_stack.rit_end());

	for (auto it = layer_stack.it_begin(); it != layer_stack.it_end(); ++it){
		std::cout << "Layer Name: " << (**it).get_name() << std::endl;
	}

	std::string in;
	std::cin >> in;
	
	layer_stack.move_layer(layer_stack.top_layer, 5);
	layer_stack.move_layer(layer_stack.top_layer, 4);
	layer_stack.move_layer(layer_stack.top_layer, 3);
	layer_stack.move_layer(layer_stack.top_layer, 2);

	for (int i=0; layer_stack.size(); i++){
		LOG(std::string("Deleting Layer: " + layer_stack.top_layer->get_name()).c_str());
		layer_stack.delete_layer(layer_stack.top_layer);
	}
	
	std::cout << "Layer Count: " << layer_stack.size() << std::endl;
	if (layer_stack.top_layer) std::cout << layer_stack.top_layer->get_name() << std::endl;

	Pixel p1(constants::layer::pixel::colors::RGBA::BLUE, BitDepth::R32G32B32A32);
	Pixel p2(constants::layer::pixel::colors::RGBA::RED, BitDepth::R32G32B32A32);
	Pixel output(p2);
	
	image::operations::run_blend_op(image::BlendMode::Normal, &p1, &p2, &output, 1.f);

	return 0;
}
