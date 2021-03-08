#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <string>
#include "point3.hpp"

#define PRECISION_TOLERANCE 0.0001
#define CENTER_OF_SPACE     0.000

template<typename T> class Point3; // foward declare to avoid circular deps
template<typename T> class Matrix4; // foward declare to avoid circular deps

/* 
	General purpose Vector class with 3 components (x,y,z) which represent their respective 
	values in 3D space. Instead of using a 4th component to differentiate a 3D vector from a 
	3D point (denoted by the use of a 1 for a point, or 0 for vector) as the classes 4th 
	component (x,y,z,w), the Point3 class shall be used instead.
*/

template<typename T>
class Vector3
{
public:
	Vector3(const T& _origin_x, const T& _origin_y, const T& _origin_z, const T& _x, const T& _y, const T& _z);
	Vector3(const T& _x,		const T& _y,		const T& _z);	
	Vector3(const Vector3& copy);
	
	// statics for generating from other objects
	Vector3<T> static fromPoints (const Point3<T>& p1, const Point3<T>& p2);
	Vector3<T> static fromCross  (const Vector3<T>& a, const Vector3<T>& b);

	// return the magnitude of the vector
	T mag() const { return sqrt(std::pow(x - ox, 2) + std::pow(y - oy, 2) + std::pow(z - oz, 2)); };

	// adjust tolerance for comparisons
	void adjustTolerance(const T& toleranceAmount) { tolerance = toleranceAmount; };

	// multiply
	T dot					(const Vector3<T>& other)				const;
	T dot					(const T& _x, const T& _y, const T& _z) const;
	Vector3<T> cross		(const Vector3<T>& other)				const;
	Vector3<T> cross		(const T& _x, const T& _y, const T& _z) const;
	Vector3<T> normalized()											const;
	
	// display rep
	std::string data() const;
	void printData()   const { std::cout << data() << std::endl; };

	T		   operator[] (const int& index) const;

	// Vector overloads								      
	bool	   operator==	(const Vector3<T>& other) const;	//  oxoyoz, xyz same on both
	bool       operator>	(const Vector3<T>& other) const;	//  gt  other vec mag
	bool       operator<	(const Vector3<T>& other) const;	//  lt  other vec mag
	bool       operator>=	(const Vector3<T>& other) const;	//  gte other vec mag
	bool       operator<=	(const Vector3<T>& other) const;	//  lte other vec mag
	Vector3<T> operator*	(const Vector3<T>& other) const;	//  cross 
	Vector3<T> operator+	(const Vector3<T>& other) const;	//  add
	Vector3<T> operator-	(const Vector3<T>& other) const;	//  sub
	void	   operator*=	(const Vector3<T>& other);			//  cross and set self
	void	   operator+=	(const Vector3<T>& other);			//  add and set self
	void	   operator-=	(const Vector3<T>& other);			//  sub and set self

	// Scalar overloads
	bool	   operator==	(const T& other) const;				//  mag eq scalar
	bool       operator>	(const T& other) const;				//  gt  scalar
	bool       operator<	(const T& other) const;				//  lt  scalar
	bool       operator>=	(const T& other) const;				//  gte scalar
	bool       operator<=	(const T& other) const;				//  lte scalar
	Vector3<T> operator*	(const T& other) const;				//  multiply by scalar 
	Vector3<T> operator/	(const T& other) const;				//  divide by scalar
	void	   operator*=	(const T& other);					//  multiply and set self
	void	   operator/=	(const T& other);					//  divide and set self

private:
	friend class Point3<T>;
	friend class Matrix4<T>;
	#ifndef PRECISION_TOLERANCE
	double tolerance = 0.0001;
	#else
	double tolerance = PRECISION_TOLERANCE;
	#endif

protected:
	// origin coordinates of vector; default 0
	#ifndef CENTER_OF_SPACE
	T ox=constants::math::center_of_space;
	T oy=constants::math::center_of_space;
	T oz=constants::math::center_of_space;
	#else
	T ox=CENTER_OF_SPACE;
	T oy=CENTER_OF_SPACE;
	T oz=CENTER_OF_SPACE;
	#endif

	// end cordinates of vector
	T x;
	T y;
	T z;
};

template<typename T>
inline Vector3<T>::Vector3(const T& _origin_x, const T& _origin_y, const T& _origin_z, const T& _x, const T& _y, const T& _z) :
	ox(_origin_x), oy(_origin_y), oz(_origin_z), x(_x), y(_y), z(_z){};

template<typename T>
inline Vector3<T>::Vector3(const T& _x, const T& _y, const T& _z) : x(_x), y(_y), z(_z) {};

template<typename T>
inline Vector3<T>::Vector3(const Vector3<T>& copy) {
	ox = copy.ox; y = copy.oy; z = copy.oz; 
	 x = copy.x;  y = copy.y;  z = copy.z;
}

template<typename T>
inline Vector3<T> Vector3<T>::fromPoints(const Point3<T>& p1, const Point3<T>& p2) {
	return Vector3<T>(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);
}

template<typename T>
inline Vector3<T> Vector3<T>::fromCross(const Vector3<T>& a, const Vector3<T>& b) {	
	return Vector3<T>(
		(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z),
		(a.x * b.y) - (a.y * b.x));
}

template<typename T>
inline Vector3<T> Vector3<T>::cross(const Vector3& other) const {
	return Vector3<T>(
		(y * other.z) - (z * other.y),
		(z * other.x) - (x * other.z),
		(x * other.y) - (y * other.x));
}

template<typename T>
inline Vector3<T> Vector3<T>::cross(const T& _x, const T& _y, const T& _z) const {
	return Vector3<T>(
		(y * _z) - (z * _y),
		(z * _x) - (x * _z),
		(x * _y) - (y * _x));
}

template<typename T>
T Vector3<T>::dot(const Vector3& other) const {
	return (x * other.x) +(y * other.y) + (z * other.z);
}

template<typename T>
inline T Vector3<T>::dot(const T& _x, const T& _y, const T& _z) const {
	return (x-ox * _x) + (y-oy * _y) + (z-oz * _z);
}

template<typename T>
inline Vector3<T> Vector3<T>::normalized() const {
	double _mag = mag();
	return Vector3<T>(x / _mag, y / _mag, z / _mag);
}

template <typename T>
Vector3<T> Vector3<T>::operator*(const Vector3& other) const {
	return Vector3<T>(
		(y * other.z) - (z * other.y),
		(z * other.x) - (x * other.z),
		(x * other.y) - (y * other.x));
}

template<typename T>
inline void Vector3<T>::operator*=(const Vector3& other) {
	*this = cross(other);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator*(const T& other) const {
	return Vector3<T>(x * other, y * other, z * other);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator/(const T& other) const {
	return Vector3<T>(x / other, y / other, z / other);
}

template<typename T>
inline bool Vector3<T>::operator==(const Vector3<T>& other) const {
/* 
	To check if our 2 vectors are equal, let's compare both of them with some level of tolerance
	due to floating point calculation inconsistencies. Use change the tolerance threshold to adjust
	to the desired accuracy. 
*/
	return(
		(ox - other.ox <= tolerance) &&
		(oy - other.oy <= tolerance) &&
		(oz - other.oz <= tolerance) &&
		(x  - other.x  <= tolerance) &&
		(y  - other.y  <= tolerance) &&
		(z  - other.z  <= tolerance));
}

template<typename T>
inline bool Vector3<T>::operator>(const Vector3& other) const {
	return (mag() > other.mag());
}

template<typename T>
inline bool Vector3<T>::operator<(const Vector3& other) const {
	return (mag() < other.mag());
}

template<typename T>
inline bool Vector3<T>::operator>=(const Vector3& other) const {
	return (mag() >= other.mag());
}

template<typename T>
inline bool Vector3<T>::operator<=(const Vector3& other) const {
	return (mag() >= other.mag());
}

template<typename T>
inline void Vector3<T>::operator*=(const T& other) {
	x *= other; z *= other; z *= other;
}

template<typename T>
inline void Vector3<T>::operator/=(const T& other) {
	x /= other; y /= other; z /= other;
}

template<typename T>
inline Vector3<T> Vector3<T>::operator+(const Vector3& other) const {
	return Vector3<T>(x + other.x, y + other.y, z + other.z);
}

template<typename T>
inline void Vector3<T>::operator+=(const Vector3& other) {
	x = x + other.x; x = x + other.x; x = x + other.z;
}

template<typename T>
inline void Vector3<T>::operator-=(const Vector3& other) {
	x = x - other.x; y = y - other.y; z = y - other.z;
}

template<typename T>
inline bool Vector3<T>::operator==(const T& other) const {
	return mag() - other <= tolerance;
}

template<typename T>
inline bool Vector3<T>::operator>(const T& other) const {
	return (mag() > other);
}

template<typename T>
inline bool Vector3<T>::operator<(const T& other) const {
	return (mag() < other);
}

template<typename T>
inline bool Vector3<T>::operator>=(const T& other) const {
	return (mag() > other || mag() - other <= tolerance);
}

template<typename T>
inline bool Vector3<T>::operator<=(const T& other) const {
	return (mag() < other || mag() - other >= tolerance);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator-(const Vector3& other) const {
	return Vector3<T>(x - other.x, y - other.y, z - other.z);
}

template <typename T>
inline T Vector3<T>::operator[](const int& index) const{
	T components[3] = {x, y, z};
	return components[index];
}

template<typename T>
inline std::string Vector3<T>::data() const {
	return std::string("OX: " + std::to_string(ox) + " OY: " + std::to_string(oy) + " OZ: " + std::to_string(oz) + 
		"\nX: " + std::to_string(x) + " Y: " + std::to_string(y) + " Z: " + std::to_string(z) + " Mag: " + std::to_string(mag()));
};

#endif // VECTOR3_H