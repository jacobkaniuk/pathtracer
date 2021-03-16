#include <iostream>
#include <fstream>
#include <chrono>
#include <assert.h>
#include <string>
#include <string.h>

#include "vector3.hpp"
#include "matrix4.hpp"
#include "ray.hpp"
#include "image_buffer.h"
#include "color.h"
#include "serializers.h"

#include "tests/TestVector3.hpp"
#include "tests/TestMatrix4.hpp"


using v3d = Vector3<double>;
using m4d = Matrix4<double>;

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
	ImageBuffer image_buffer(10, 10, BitDepth::NEG_R32G32B32);
	image_buffer.fill(constants::image::pixel::colors::BLUE);
	//image_buffer->fill_max();
	std::filebuf dump_file;
	dump_file.open(std::string("C:\\dev\\c++\\testing.bmp").c_str(), std::ios::out);
	std::ostream os(&dump_file);
	image_buffer.dump(dump_file, os);

	std::cout << "Value: " << bit_depth_value(BitDepth::R16G16B16) << std::endl;

	return 0;
}
