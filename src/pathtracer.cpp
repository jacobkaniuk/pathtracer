#include <iostream>
#include <fstream>
#include <chrono>
#include <assert.h>
#include <string>
#include <string.h>
#include <math.h>

#include "vector3.hpp"
#include "matrix4.hpp"
#include "ray.hpp"
#include "image_buffer.h"
#include "color.h"
#include "serializers.h"
#include "blend_ops.hpp"
#include "image_layer.h"
#include "image_layer_stack.h"

#include "tests/TestVector3.hpp"
#include "tests/TestMatrix4.hpp"

using v3d = Vector3<double>;
using m4d = Matrix4<double>;

void LOG(const char* message){std::cout << message << std::endl;};

// TODO fix linker issues with libgtest + libtest_main, this is getting out've hand...lol

int main()
{
   	// Vector 3 Tests
	v3d tv1 = Vector3<double>(15.5, 10.2, 99.144);
	v3d tv2 = Vector3<double>(22.23, 12.42, 44.64);
	TestVector3<double> Vector3Test(tv1, tv2);
	Vector3Test.runAllTests();	


	// Ray
	Ray3D<double> ray(tv1, tv2, 500.2);
	Point3<double> test = Point3<double>::fromVector(tv1);
	Vector3<double> vt = Vector3<double>::fromPoint(test);
	
	// Matrix4
	Matrix4<double> mat1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	Matrix4<double> mat2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	Vector3<double> tmvec(1.5, 2.2, 8.92); 
	Point3<double> tmpoint(1.5, 2.2, 8.92);
	// TestMatrix4<double> Matrix4Test(mat1, mat2, tmvec, tmpoint);
	// Matrix4Test.runAllTests();

	double my_points[4][4] = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1},
	};

	m4d m1(my_points);
	m1.printData();
	Matrix4<int> s = Matrix4<int>::identity();

	// create an empty image buffer
	ImageBuffer image_buffer(display::resolution::res_FHD, BitDepth::R8G8B8A8);
	image_buffer.fill_max();
	image_buffer.fill(constants::layer::pixel::colors::RGBA::BLUE);
	image_buffer.fill(color::Color(1.0f, 1.0f, 0.5f, 0.f));
	std::filebuf dump_file;
	dump_file.open(std::string("C:\\dev\\c++\\testing.bmp").c_str(), std::ios::out);
	std::ostream os(&dump_file);
	image_buffer.dump(dump_file, os);

	std::cout << "Value: " << bit_depth_value(BitDepth::R16G16B16) << std::endl;
	std::cout << image_buffer.width() << "x" << image_buffer.height() << std::endl;

	BMPSerializer bmp_writer("C:\\dev\\c++", image_buffer);
	
	image::LayerStack layer_stack = image::LayerStack(image_buffer);
	ImageBuffer copy = ImageBuffer(image_buffer);
	copy.fill(constants::layer::pixel::colors::RGBA::RED);
	
	for (int i=0; i<10; i++){
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

	
	// Normal/Replace Test
	Pixel p1(constants::layer::pixel::colors::RGBA::BLUE, BitDepth::R8G8B8A8);
	Pixel p2(constants::layer::pixel::colors::RGBA::RED, BitDepth::R8G8B8A8);
	Pixel output(p2);

	std::cout << "RED: " << p1[0] << " GREEN: " << p1[1] << " BLUE: " << p1[2] << std::endl;
	std::cout << "RED: " << p2[0] << " GREEN: " << p2[1] << " BLUE: " << p2[2] << std::endl << "\n\n";

	image::operations::BlendNormal(&p1, &p2, &output, 1.f);
	std::cout << "RED: " << output[0] << " GREEN: " << output[1] << " BLUE: " << output[2]  << " " << output[3] << std::endl << "\n\n";


	// Darken Test
	Pixel pd1(color::ColorRGBA(0.5f, 0.5f, 0.5f, 1.f), BitDepth::R8G8B8A8);
	Pixel pd2(color::ColorRGBA(1.f, 1.f, 1.f, 1.f), BitDepth::R8G8B8A8);

	std::cout << "REDss: " << pd1[0] << " GREEN: " << pd1[1] << " BLUE: " << pd1[2] << std::endl;
	std::cout << "REDss: " << pd2[0] << " GREEN: " << pd2[1] << " BLUE: " << pd2[2] << std::endl << "\n\n";

	image::operations::BlendDarken(&pd1, &pd2, &output, .75f);
	std::cout << "RED: " << output[0] << " GREEN: " << output[1] << " BLUE: " << output[2]  << " " << output[3] << std::endl << "\n\n";


	// Multiply Test
	Pixel pm1(color::ColorRGBA(0.5f, 0.5f, 1.f, 1.f), BitDepth::R8G8B8A8);
	Pixel pm2(color::ColorRGBA(1.f, 1.f, 1.f, 1.f), BitDepth::R8G8B8A8);

	std::cout << "REDss: " << pm1[0] << " GREEN: " << pm1[1] << " BLUE: " << pm1[2] << std::endl;
	std::cout << "REDss: " << pm2[0] << " GREEN: " << pm2[1] << " BLUE: " << pm2[2] << std::endl << "\n\n";

	image::operations::BlendDarken(&pm1, &pm2, &output, .75f);
	std::cout << "RED: " << output[0] << " GREEN: " << output[1] << " BLUE: " << output[2]  << " " << output[3] << std::endl << "\n\n";


	// image::operations::BlendNormal(&temp->get_image_buffer()->get_pixel(0,0), &p, &output, temp->get_opacity());

	for (auto it = layer_stack.it_begin(); it != layer_stack.it_end(); ++it){
		std::cout << "Layer Name: " << (**it).get_name() << std::endl;
	}

	std::string in;
	std::cin >> in;

	for (int i=0; layer_stack.size(); i++){
		LOG(std::string("Deleting Layer: " + layer_stack.top_layer->get_name()).c_str());
		layer_stack.delete_layer(layer_stack.top_layer);
	}
	
	std::cout << "Layer Count: " << layer_stack.size() << std::endl;
	if (layer_stack.top_layer) std::cout << layer_stack.top_layer->get_name() << std::endl;

	return 0;
}
