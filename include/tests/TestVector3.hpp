#include <assert.h>
#include "../vector3.hpp"

template<typename T>
class TestVector3 {
public:
	TestVector3(Vector3<T>& _v1, Vector3<T>& _v2) : v1(_v1), v2(_v2) {};
	~TestVector3();
	void runAllTests();
	void testDot();
	void testCross();
	void testMult();
	void testAdd();
	void testSub();
	void testDiv();
	void testEquals();
	void testFromPoints();
	void testFromCross();
private:
	Vector3<T> v1;
	Vector3<T> v2;
};

template<typename T>
inline TestVector3<T>::~TestVector3()
{
}

template<typename T>
inline void TestVector3<T>::runAllTests(){
	testDot();
	testCross();
	testMult();
	testAdd();
	testSub();
	testDiv();
	testEquals();
	testFromPoints();
	testFromCross();
}

template<typename T>
inline void TestVector3<T>::testDot() {
	T result = 4897.03716;
	assert(result == v1.dot(v2));
}

template<typename T>
inline void TestVector3<T>::testCross() {
	Vector3<T> result(-776.04048, 1512.05112, -34.236);
	assert(result == v1.cross(v2)); 	// function call
	assert(result == v1 * v2);		// operator call
}

template<typename T>
inline void TestVector3<T>::testMult() {
	Vector3<T>result(86.8, 57.12, 555.2064);  
	Vector3<T>calc(v1*5.6); 		// v3d from multiply by scalar
	assert(result == v1 * 5.6);
}

template<typename T>
inline void TestVector3<T>::testAdd() {
	Vector3<T> result(37.73, 22.62, 143.784);
	assert(result == v1 + v2);
}

template<typename T>
inline void TestVector3<T>::testSub() {
	Vector3<T> result(-6.73, -2.22, 54.504);
	assert(result == v1 - v2);
}

template<typename T>
inline void TestVector3<T>::testDiv() {	
	Vector3<T>result(5.1666666666666666, 3.4, 33.048);
	assert(result == v1 / 3);
}

template<typename T>
inline void TestVector3<T>::testEquals() {
	Vector3<T> temp = v2;
	assert(temp == v2);
}

template<typename T>
inline void TestVector3<T>::testFromPoints() {
	Point3<T> p1(22.5, 112.45, 229.167);
	Point3<T> p2(12.124, 14.35, 120.27);
	Vector3<T> pointsVec = Vector3<T>::fromPoints(p1, p2);
	Vector3<T> explicitVec = Vector3<T>(22.5, 112.45, 229.167, 12.124, 14.35, 120.27);
	assert(pointsVec == explicitVec);
}

template<typename T>
inline void TestVector3<T>::testFromCross() {
	Vector3<T> result(-776.04048, 1512.05112, -34.236);
	assert(result == Vector3<T>::fromCross(v1, v2));
}
