#include "transform.h"

#define PI 3.14159265359

Transform2D::Transform2D() {
    _translate_x = 0.f;
    _translate_y = 0.f;
    _rotate = 0.f;
    _scale_x = 1.f;
    _scale_y = 1.f;
};

Transform2D::Transform2D(const Transform2D& copy) {
    _translate_x = copy._translate_x;
    _translate_y = copy._translate_y;
    _rotate = copy._rotate;
    _scale_x = copy._scale_x;
    _scale_y = copy._scale_y;
};

void Transform2D::set_scale(const float& x, const float& y) {
    _scale_x = x;
    _scale_y = y;
};

void Transform2D::set_position(const float& x, const float& y) {
    _translate_x = x;
    _translate_y = y;
};

void Transform2D::set_rotation(const float& angle) {
    _rotate = angle;
};

std::pair<float, float> Transform2D::get_translate() const {
    return std::pair<float, float>(_translate_x, _translate_y);
};

std::pair<float, float> Transform2D::get_scale() const {
    return std::pair<float, float>(_scale_x, _scale_y);
};

float Transform2D::get_rotation() const {
    return _rotate;
};

float Transform2D::rotation_as_radians() const {
    return static_cast<float>((_rotate * PI) / 180);
};
