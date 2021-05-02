#include "catch.hpp"
#include "ray.hpp"

namespace ray
{
    Vector3<double> v1(15.5, 10.2, 99.144);
    Vector3<double> v2(22.23, 12.42, 44.64);
    Ray3D<double> ray(tv1, tv2, 500.2);
    Point3<double> test = Point3<double>::fromVector(tv1);
    Vector3<double> vt = Vector3<double>::fromPoint(test);    
} // namespace ray

using namespace ray;
