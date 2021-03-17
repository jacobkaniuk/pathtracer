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
    namespace image{
        enum resolutions{
            res_360,
            res_540,
            res_720,
            res_1080,
            res_4k,
            res_8k,
            res_HD = res_720,
            res_FHD = res_1080,
            res_UDH = res_4k,
        };
        enum bit_depth{
            Int8,
            Int16,
            Int32,
            Float16,
            Float32,
        };
        namespace pixel{
            namespace colors{
                // RGB
                static color::ColorRGB RED            = color::ColorRGB(1.f, 0.f, 0.f);
                static color::ColorRGB GREEN          = color::ColorRGB(0.f, 1.f, 0.f);
                static color::ColorRGB BLUE           = color::ColorRGB(0.f, 0.f, 1.f);
                static color::ColorRGB WHITE          = color::ColorRGB(1.f, 1.f, 1.f);
                static color::ColorRGB BLACK          = color::ColorRGB(0.f, 0.f, 0.f);
                static color::ColorRGB GRAY           = color::ColorRGB(0.5f, 0.5f, 0.5f);
                static color::ColorRGB GRAY_25        = color::ColorRGB(0.25f, 0.25f, 0.25f);
                static color::ColorRGB GRAY_75        = color::ColorRGB(0.75f, 0.75f, 0.75f);
                // RGBA
                static color::ColorRGBA ALPHA_RED     = color::ColorRGBA(1.f, 0.f, 0.f, 1.f);
                static color::ColorRGBA ALPHA_GREEN   = color::ColorRGBA(0.f, 1.f, 0.f, 1.f);
                static color::ColorRGBA ALPHA_BLUE    = color::ColorRGBA(0.f, 0.f, 1.f, 1.f);
                static color::ColorRGBA ALPHA_WHITE   = color::ColorRGBA(1.f, 1.f, 1.f, 1.f);
                static color::ColorRGBA ALPHA_BLACK   = color::ColorRGBA(0.f, 0.f, 0.f, 1.f);
                static color::ColorRGBA ALPHA_GRAY    = color::ColorRGBA(0.5f, 0.5f, 0.5f, 1.f);
                static color::ColorRGBA ALPHA_GRAY_25 = color::ColorRGBA(0.25f, 0.25f, 0.25f, 1.f);
                static color::ColorRGBA ALPHA_GRAY_75 = color::ColorRGBA(0.75f, 0.75f, 0.75f, 1.f);
            }
        }

    }
}


#endif // CONSTANTS_H