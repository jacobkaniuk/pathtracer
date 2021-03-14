#ifndef COLOR_H
#define COLOR_H

namespace color {
    class Color{
    protected:
        float _x;
        float _y;
        float _z;
        float _w;
    public:
        Color(const float& x, const float& y, const float& z, const float& w):
        _x(x), _y(y), _z(z), _w(w){};
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


    // color::ColorRGB RED            = color::ColorRGB(1.f, 0.f, 0.f);
    // color::ColorRGB GREEN          = color::ColorRGB(0.f, 1.f, 0.f);
    // color::ColorRGB BLUE           = color::ColorRGB(0.f, 0.f, 1.f);
    // color::ColorRGB WHITE          = color::ColorRGB(1.f, 1.f, 1.f);
    // color::ColorRGB BLACK          = color::ColorRGB(0.f, 0.f, 0.f);
    // color::ColorRGB GRAY           = color::ColorRGB(0.5f, 0.5f, 0.5f);
    // color::ColorRGB GRAY_25        = color::ColorRGB(0.25f, 0.25f, 0.25f);
    // color::ColorRGB GRAY_75        = color::ColorRGB(0.75f, 0.75f, 0.75f);
    // // RGBA
    // color::ColorRGBA ALPHA_RED     = color::ColorRGBA{1.f, 0.f, 0.f, 1.f};
    // color::ColorRGBA ALPHA_GREEN   = color::ColorRGBA{0.f, 1.f, 0.f, 1.f};
    // color::ColorRGBA ALPHA_BLUE    = color::ColorRGBA{0.f, 0.f, 1.f, 1.f};
    // color::ColorRGBA ALPHA_WHITE   = color::ColorRGBA{1.f, 1.f, 1.f, 1.f};
    // color::ColorRGBA ALPHA_BLACK   = color::ColorRGBA{0.f, 0.f, 0.f, 1.f};
    // color::ColorRGBA ALPHA_GRAY    = color::ColorRGBA{0.5f, 0.5f, 0.5f, 1.f};
    // color::ColorRGBA ALPHA_GRAY_25 = color::ColorRGBA{0.25f, 0.25f, 0.25f, 1.f};
    // color::ColorRGBA ALPHA_GRAY_75 = color::ColorRGBA{0.75f, 0.75f, 0.75f, 1.f};

#endif // COLOR_H