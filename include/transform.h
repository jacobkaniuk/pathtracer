#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <utility>

class Transform2D {
   private:
    float _translate_x, _translate_y;
    float _rotate;
    float _scale_x, _scale_y;

   public:
    Transform2D();
    Transform2D(const Transform2D& copy);
    void set_scale(const float& x, const float& y);
    void set_position(const float& x, const float& y);
    void set_rotation(const float& angle);

    std::pair<float, float> get_translate() const;
    std::pair<float, float> get_scale() const;
    float get_rotation() const;
    float rotation_as_radians() const;
};

#endif  // TRANSFORM_H