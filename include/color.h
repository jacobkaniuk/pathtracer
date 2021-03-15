#ifndef COLOR_H
#define COLOR_H

namespace color {
    class Color{
    protected:
        friend class Pixel;
        float _x;
        float _y;
        float _z;
        float _w;
    public:
        Color(const Color& copy){_x = copy._x; _y = copy._y; _z = copy._z; _w = copy._w;}
        Color(const float& x, const float& y, const float& z, const float& w):
        _x(x), _y(y), _z(z), _w(w){};
        float x() const {return _x;};
        float y() const {return _y;};
        float z() const {return _z;};
        float w() const {return _w;};
    };

    class ColorRGB: public Color {
        public:
            ColorRGB(const float& _r, const float& _g, const float& _b): Color(_r, _g, _b, 0.f) { };
            // 0 - 1 normalized definition for easily changing between bit depth formats
            float r(){return _x;};
            float g(){return _y;};
            float b(){return _z;};
    };

    struct ColorRGBA: public Color{
        public:
            ColorRGBA(const float& _r, const float& _g, const float& _b, const float& _a): Color(_r, _g, _b, _a) { };
            // 0 - 1 normalized definition for easily changing between bit depth formats
            float r(){return _x;};
            float g(){return _y;};
            float b(){return _z;};
            float a(){return _w;};
    };
    class ColorCMYK: public Color {
        public:
            ColorCMYK(const float& _c, const float& _m, const float& _y, const float& _k): Color(_c, _m, _y, _k) { };
            // 0 - 1 normalized definition for easily changing between bit depth formats
            float c(){return _x;};
            float m(){return _y;};
            float y(){return _z;};
            float k(){return _w;};
    };
}

#endif // COLOR_H