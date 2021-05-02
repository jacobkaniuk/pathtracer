#include "catch.hpp"
#include "matrix4.hpp"

namespace test_matrix4
{
	Vector3<double> v1(15.5, 10.2, 99.144);
	Vector3<double> v2(22.23, 12.42, 44.64);
	Matrix4<double> mat1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	Matrix4<double> mat2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	Point3<double> tmpoint(1.5, 2.2, 8.92);	
} // namespace test_matrix4

using namespace test_matrix4;

TEST_CASE("MultiplyOperator") {
	// test Vector3
	Vector3<double> vec(1.5, 2.2, 8.92);
	Vector3<double> result1(32.66, 83.14, 133.62);
	Vector3<double> result = mat1 * vec;
	REQUIRE(result1 == mat1 * vec);

	// test matrix4
	Matrix4<double> result2(90, 100, 110, 120, 202, 228, 254, 280, 314, 356, 398, 440, 426, 484, 542, 600);
	REQUIRE(result2 == mat1 * mat2);

		double my_points[4][4] = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1},
	};

	Matrix4<double> m1(my_points);
	//m1.printData();
	Matrix4<int> s = Matrix4<int>::identity();
	
	// test Point3
}
