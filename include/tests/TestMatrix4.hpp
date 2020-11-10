#include <assert.h>
#include "../matrix4.hpp"

template<typename T>
class TestMatrix4 {
public:
	TestMatrix4(const Matrix4<T>& _matA, const Matrix4<T>& _matB, Vector3<T> _vec, Point3<T> _point):
		mat1(_matA), mat2(_matB), vec(_vec), point(_point){};
	void runAllTests();
	void testMult();
	void testAdd();
	void testSub();
private:
	Matrix4<T> mat1;
	Matrix4<T> mat2;
	Vector3<T> vec;
	Point3<T> point;

};

template<typename T>
inline void TestMatrix4<T>::runAllTests() {
	testMult();
	//testAdd();
	//testSub();
}

template<typename T>
inline void TestMatrix4<T>::testMult() {
	// test Vector3
	Vector3<T> vec(1.5, 2.2, 8.92);
	Vector3<T> result1(32.66, 83.14, 133.62);
	assert(result1 == mat1 * vec);

	// test matrix4
	Matrix4<T> result2(90, 100, 110, 120, 202, 228, 254, 280, 314, 356, 398, 440, 426, 484, 542, 600);
	assert(result2 == mat1 * mat2);
	
	// test Point3
}
