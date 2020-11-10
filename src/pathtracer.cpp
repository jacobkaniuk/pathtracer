#include <iostream>
#include <chrono>
#include <assert.h>
#include "../include/vector3.hpp"
#include "../include/matrix4.hpp"
#include "../include/tests/TestVector3.hpp"
#include "../include/tests/TestMatrix4.hpp"

using v3d = Vector3<double>;
using m4d = Matrix4<double>;

int main()
{
	// Vector 3 Tests
	v3d tv1 = Vector3<double>(15.5, 10.2, 99.144);
	v3d tv2 = Vector3<double>(22.23, 12.42, 44.64);
	TestVector3<double> Vector3Test(tv1, tv2);
	Vector3Test.runAllTests();

	// Matrix4
	Matrix4<double> mat1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	Matrix4<double> mat2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	Vector3<double> tmvec(1.5, 2.2, 8.92); 
	Point3<double> tmpoint(1.5, 2.2, 8.92);
	TestMatrix4<double> Matrix4Test(mat1, mat2, tmvec, tmpoint);
	Matrix4Test.runAllTests();

	double my_points[4][4] = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1},
	};
	m4d m1(my_points);
	m1.printData();
	Matrix4<int> s = Matrix4<int>::identity();
	return 0;
}
