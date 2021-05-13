#include <cmath>
#include <iostream>

#include "blend_ops.hpp"
#include "pixel.h"

namespace image
{
    namespace operations
    {
        
        void run_blend_op(const image::BlendMode& blend_mode, Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {
            switch(blend_mode){
                case image::BlendMode::Normal: {
                    image::operations::BlendNormal(top_pixel, bottom_pixel, output_pixel, opacity);
                    break;
                }
                // case Dissolve:
                //     return &BlendDissolve;
                //     break;
                case image::BlendMode::Darken: {
                    image::operations::BlendDarken(top_pixel, bottom_pixel, output_pixel, opacity);
                    break;
                }
                case image::BlendMode::Multiply:
                    image::operations::BlendMultiply(top_pixel, bottom_pixel, output_pixel, opacity);
                    break;
                    
                // case ColorBurn:
                //     return &BlendColorBurn;
                //     break;
                // case LinearBurn:
                //     return &BlendLinearBurn;
                //     break;
                // case DarkerColor:
                //     return &BlendDarkerColor;
                //     break;
                // case Lighten:
                //     return &BlendLighten;
                //     break;
                // case Screen:
                //     return &BlendScreen;
                //     break;
                // case ColorDodge:
                //     return &BlendColorDodge;
                //     break;
                // case LinearDodge:
                //     return &BlendLinearDodge;
                //     break;
                // case LighterColor:
                //     return &BlendLighterColor;
                //     break;
                // case Overlay:
                //     return &BlendOverlay;
                //     break;
                // case SoftLight:
                //     return &BlendSoftLight;
                //     break;
                // case HardLight:
                //     return &BlendHardLight;
                //     break;
                // case VividLight:
                //     return &BlendVividLight;
                //     break;
                // case LinearLight:
                //     return &BlendLinearLight;
                //     break;
                // case PinLight:
                //     return &BlendPinLight;
                //     break;
                // case HardMix:
                //     return &BlendHardMix;
                //     break;
                // case Difference:
                //     return &BlendDifference;
                //     break;
                // case Exclusion:
                //     return &BlendExclusion;
                //     break;
                // case Subtract:
                //     return &BlendSubtract;
                //     break;
                // case Divide:
                //     return &BlendDivide;
                //     break;
                // case Hue:
                //     return &BlendHue;
                //     break;
                // case Saturation:
                //     return &BlendSaturation;
                //     break;
                // case Color:
                //     return &BlendColor;
                //     break;
                // case Luminosity:
                //     return &BlendLuminosity;
                //     break;
                }
            };
        }   // namespace operations
    }   // namespace image
