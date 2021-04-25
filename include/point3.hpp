#ifndef POINT3_H
#define POINT3_H

#include "vector3.hpp"
#include "ray.hpp"
#include <cmath>
#include <array>

template<typename T> class Vector3; // foward declare to avoid circular deps

template<typename T>
class Point3
{
public:
	Point3(const T& _x, const T& _y, const T& _z) : x(_x), y(_y), z(_z) {};
	Point3(const Point3<T>& copy);
	Point3<T> static fromVector(const Vector3<T>& vector) { return Point3<T>(vector.x, vector.y, vector.z); };
	
	T distanceTo(const Point3<T>& other) const;
	T* asVector4() const;

	std::string data()	const;
	void printData()	const { std::cout << data() << std::endl; };
	
private:
	friend class Vector3<T>;
	friend class Ray3D<T>;
protected:
	T x;
	T y;
	T z;
	T w = 1;
};

template<typename T>
inline std::string Point3<T>::data() const {
	return std::string("X: " + std::to_string(x) + " Y: " + std::to_string(y) + " Z: " + std::to_string(z));
}

template<typename T>
inline Point3<T>::Point3(const Point3<T>& copy) {
	x = copy.x; y = copy.y; z = copy.z; w = copy.w;
}

template<typename T>
inline T Point3<T>::distanceTo(const Point3<T>& other) const {
	return sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2) + std::pow(z - other.z, 2));
}

template<typename T>
inline T* Point3<T>::asVector4() const {
	T* stuff = new T[4];
	stuff[0] = x; stuff[1] = y; stuff[2] = z; stuff[3] = w;
	return stuff;
}

#endif // POINT3_H
