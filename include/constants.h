#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <utility>
#include <unordered_map>

#include "color.h"

namespace constants{
    namespace math {
        static double precision_tolerance  = 0.00001;
        static double center_of_space      = 0.00000;
    }
    namespace layer{
        enum bit_depth{
            Int8,
            Int16,
            Int32,
            Float16,
            Float32,
        };
        namespace pixel{
            namespace colors{
                namespace RGB{
                    // RGB
                    static color::ColorRGB EMPTY    = color::ColorRGB(0.f, 0.f, 0.f);
                    static color::ColorRGB RED      = color::ColorRGB(1.f, 0.f, 0.f);
                    static color::ColorRGB GREEN    = color::ColorRGB(0.f, 1.f, 0.f);
                    static color::ColorRGB BLUE     = color::ColorRGB(0.f, 0.f, 1.f);
                    static color::ColorRGB WHITE    = color::ColorRGB(1.f, 1.f, 1.f);
                    static color::ColorRGB BLACK    = color::ColorRGB(0.f, 0.f, 0.f);
                    static color::ColorRGB GRAY     = color::ColorRGB(0.5f, 0.5f, 0.5f);
                    static color::ColorRGB GRAY_25  = color::ColorRGB(0.25f, 0.25f, 0.25f);
                    static color::ColorRGB GRAY_75  = color::ColorRGB(0.75f, 0.75f, 0.75f);
                }
                namespace RGBA{
                    // RGBA
                    static color::ColorRGBA EMPTY   = color::ColorRGBA(0.f, 0.f, 0.f, 0.f);
                    static color::ColorRGBA RED     = color::ColorRGBA(1.f, 0.f, 0.f, 1.f);
                    static color::ColorRGBA GREEN   = color::ColorRGBA(0.f, 1.f, 0.f, 1.f);
                    static color::ColorRGBA BLUE    = color::ColorRGBA(0.f, 0.f, 1.f, 1.f);
                    static color::ColorRGBA WHITE   = color::ColorRGBA(1.f, 1.f, 1.f, 1.f);
                    static color::ColorRGBA BLACK   = color::ColorRGBA(0.f, 0.f, 0.f, 1.f);
                    static color::ColorRGBA GRAY    = color::ColorRGBA(0.5f, 0.5f, 0.5f, 1.f);
                    static color::ColorRGBA GRAY_25 = color::ColorRGBA(0.25f, 0.25f, 0.25f, 1.f);
                    static color::ColorRGBA GRAY_75 = color::ColorRGBA(0.75f, 0.75f, 0.75f, 1.f);
                }
            }
        }

    }
}


#endif // CONSTANTS_H