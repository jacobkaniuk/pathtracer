#include "catch.hpp"
#include "vector3.hpp"


namespace test_vector3{
	Vector3<double> v1(15.5, 10.2, 99.144);
	Vector3<double> v2(22.23, 12.42, 44.64);
} // namespace test_vector3

using namespace test_vector3;

TEST_CASE("Dot") {    
    double result = 4897.03716;
    REQUIRE(result == v1.dot(v2));
}

TEST_CASE("CrossFunction") {
    Vector3<double> result(-776.04048, 1512.05112, -34.236);
    REQUIRE(result == v1.cross(v2));
}

TEST_CASE("CrossOperator") {
    Vector3<double> result(-776.04048, 1512.05112, -34.236);
    REQUIRE(result == v1 * v2);
}

TEST_CASE("MultiplyScalarOperator") {
    Vector3<double> result(86.8, 57.12, 555.2064);
    REQUIRE(result == v1 * 5.6);
}

TEST_CASE("Add") {
    Vector3<double> result(37.73, 22.62, 143.784);
    REQUIRE(result == v1 + v2);
}

TEST_CASE("Subtract") {
    Vector3<double> result(-6.73, -2.22, 54.504);
    REQUIRE(result == v1 - v2);
}

TEST_CASE("Divide") {
    Vector3<double> result(5.1666666666666666, 3.4, 33.048);
    REQUIRE(result == v1 / 3);
}

TEST_CASE("Equality") {
    Vector3<double> temp = v2;
    REQUIRE(temp == v2);
}

TEST_CASE("FromPoints") {
    Point3<double> p1(22.5, 112.45, 229.167);
    Point3<double> p2(12.124, 14.35, 120.27);
    Vector3<double> pointsVec = Vector3<double>::fromPoints(p1, p2);
    Vector3<double> explicitVec = Vector3<double>(22.5, 112.45, 229.167, 12.124, 14.35, 120.27);
    REQUIRE(pointsVec == explicitVec);
}

TEST_CASE("FromCross") {
    Vector3<double> result(-776.04048, 1512.05112, -34.236);
    REQUIRE(result == Vector3<double>::fromCross(v1, v2));
}
