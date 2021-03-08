#ifndef MATRIX4_H
#define MATRIX4_H
#include <assert.h>
#include <array>
#include <iterator>
#include <iostream>
#include "vector3.hpp"
#include "point3.hpp"
#include "constants.h"

#define PRECISION_TOLERANCE 0.0001

template<typename T>
class Matrix4 {
public:
	// construct from 4x4 array, or 16 elements
	Matrix4();
	Matrix4(T(&_elements)[4][4]);
	Matrix4(const T& ax, const T& ay, const T& az, const T& aw,
		const T& bx, const T& by, const T& bz, const T& bw,
		const T& cx, const T& cy, const T& cz, const T& cw,
		const T& dx, const T& dy, const T& dz, const T& dw) {};
	Matrix4(const Matrix4<T>& copy);
	// statics for generation
	static	Matrix4<T> invserse(const Matrix4<T>& mat, const T n = nullptr);
	static	Matrix4<T> identity();

	// 
	Matrix4<T> invserse(const Matrix4<T>& mat) const;

	void printData() const;

	~Matrix4() {};

	// operators
	bool operator==(const Matrix4<T>& other);
	Vector3<T> operator*(const Vector3<T>& vector);
	Matrix4<T> operator*(const T& scalar);
	Matrix4<T> operator*(const Matrix4<T>& other);
	Point3 <T> operator*(const Point3<T>& point);

private:
	// Default as identity
	T elements[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
	#ifndef PRECISION_TOLERANCE
	double tolerance = constants::math::precision_tolerance;
	#else
	double tolerance = PRECISION_TOLERANCE;
	#endif
};


template<typename T>
inline Matrix4<T>::Matrix4() {
}

template<typename T>
inline Matrix4<T>::Matrix4(T (&_elements)[4][4]) {
	//std::copy(std::begin(_elements), std::end(_elements), std::begin(elements));

	/*for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			elements[i][j] = _elements[i][j];
		}
	}*/
}

template<typename T>
inline void Matrix4<T>::printData() const {
	std::string rep =
		std::to_string(elements[0][0]) + " " + std::to_string(elements[0][1]) + " " + std::to_string(elements[0][2]) + " " + std::to_string(elements[0][3]) + "\n" +
		std::to_string(elements[1][0]) + " " + std::to_string(elements[1][1]) + " " + std::to_string(elements[1][2]) + " " + std::to_string(elements[1][3]) + "\n" +
		std::to_string(elements[2][0]) + " " + std::to_string(elements[2][1]) + " " + std::to_string(elements[2][2]) + " " + std::to_string(elements[2][3]) + "\n" +
		std::to_string(elements[3][0]) + " " + std::to_string(elements[3][1]) + " " + std::to_string(elements[3][2]) + " " + std::to_string(elements[3][3]) + "\n";
	std::cout << rep;
}

template<typename T>
inline bool Matrix4<T>::operator==(const Matrix4<T>& other) {
	return (

		(elements[0][0] - other.elements[0][0] <= tolerance) &&
		(elements[0][1] - other.elements[0][1] <= tolerance) &&
		(elements[0][2] - other.elements[0][2] <= tolerance) &&
		(elements[0][3] - other.elements[0][3] <= tolerance) &&
		
		(elements[1][0] - other.elements[1][0] <= tolerance) &&
		(elements[1][1] - other.elements[1][1] <= tolerance) &&
		(elements[1][2] - other.elements[1][2] <= tolerance) &&
		(elements[1][3] - other.elements[1][3] <= tolerance) &&

		(elements[2][0] - other.elements[2][0] <= tolerance) &&
		(elements[2][1] - other.elements[2][1] <= tolerance) &&
		(elements[2][2] - other.elements[2][2] <= tolerance) &&
		(elements[2][3] - other.elements[2][3] <= tolerance) &&

		(elements[3][0] - other.elements[3][0] <= tolerance) &&
		(elements[3][1] - other.elements[3][1] <= tolerance) &&
		(elements[3][2] - other.elements[3][2] <= tolerance) &&
		(elements[3][3] - other.elements[3][3] <= tolerance));
}

template<typename T>
inline Vector3<T> Matrix4<T>::operator*(const Vector3<T>& vector) {
	return Vector3<T>(
		(vector.x - vector.ox * elements[0][0]) + (vector.x - vector.ox * elements[0][1]) + 
		(vector.x - vector.ox * elements[0][2]) + (vector.x - vector.ox * elements[0][3]),
		(vector.y - vector.oy * elements[1][0]) + (vector.x - vector.ox * elements[1][1]) +
		(vector.y - vector.oy * elements[1][2]) + (vector.x - vector.ox * elements[1][3]),
		(vector.z - vector.oz * elements[2][0]) + (vector.x - vector.ox * elements[2][1]) +
		(vector.z - vector.oz * elements[2][2]) + (vector.x - vector.ox * elements[2][3])
		// omit W component since we separated W component to signify Point3 class
		);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator*(const T& scalar) {
	return Matrix4<T>(
		elements[0][0] * scalar, elements[0][1] * scalar, elements[0][2] * scalar, elements[0][3],
		elements[1][0] * scalar, elements[1][1] * scalar, elements[1][2] * scalar, elements[1][3],
		elements[2][0] * scalar, elements[2][1] * scalar, elements[2][2] * scalar, elements[2][3],
		elements[3][0] * scalar, elements[3][1] * scalar, elements[3][2] * scalar, elements[3][3]
		);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::operator*(const Matrix4<T>& other) {
	return Matrix4<T>(
		elements[0][0] * other.elements[0][0], elements[0][1] * other.elements[0][1], elements[0][2] * other.elements[0][2], elements[0][3] * other.elements[0][3],
		elements[1][0] * other.elements[1][0], elements[1][1] * other.elements[1][1], elements[1][2] * other.elements[1][2], elements[1][3] * other.elements[1][3],
		elements[2][0] * other.elements[2][0], elements[2][1] * other.elements[2][1], elements[2][2] * other.elements[2][2], elements[2][3] * other.elements[2][3],
		elements[3][0] * other.elements[3][0], elements[3][1] * other.elements[3][1], elements[3][2] * other.elements[3][2], elements[3][3] * other.elements[3][3]
		);
}

template<typename T>
inline Point3<T> Matrix4<T>::operator*(const Point3<T>& point) {
	return Point3<T>();
}

template<typename T>
inline Matrix4<T>::Matrix4(const Matrix4<T>& copy) {
	memcpy(elements, copy.elements, sizeof(T) * 16);
}

template<typename T>
inline Matrix4<T> Matrix4<T>::identity() {
	return Matrix4<T>(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
}


#endif // MATRIX4_H