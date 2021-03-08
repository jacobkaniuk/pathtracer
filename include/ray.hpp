#ifndef RAY_H
#define RAY_H

#include "vector3.hpp"
#include "point3.hpp"


template<typename T> class Point3; // foward declare to avoid circular deps
template<typename T> class Vector3; // foward declare to avoid circular deps

template<typename T>
class Ray3D {
public:
    Ray3D(const Vector3<T>& _origin, const Vector3<T>& _direction, const T& _length);
    Ray3D(const Point3<T>&  _origin, const Vector3<T>& _direction, const T& _length);

protected:
    Vector3<T> origin, direction;
    T length;
};

template<typename T>
inline Ray3D<T>::Ray3D(const Vector3<T>& _origin, const Vector3<T>& _direction, const T& _length):
    origin(_origin), direction(_direction), length(_length){};

#endif