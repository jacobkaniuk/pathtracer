#include <cmath>

#include "blend_ops.hpp"
#include "pixel.h"

namespace image
{
    namespace operations
    {
        decltype(auto) get_blend_mode_operation(const image::BlendMode& blendmode) {
            switch (blendmode)
            {
                case Normal:
                    return &BlendNormal;
                    break;
                case Dissolve:
                    return &BlendDissolve;
                    break;
                case Darken:
                    return &BlendDarken;
                    break;
                case Multiply:
                    return &BlendMultiply;
                    break;
                case ColorBurn:
                    return &BlendColorBurn;
                    break;
                case LinearBurn:
                    return &BlendLinearBurn;
                    break;
                case DarkerColor:
                    return &BlendDarkerColor;
                    break;
                case Lighten:
                    return &BlendLighten;
                    break;
                case Screen:
                    return &BlendScreen;
                    break;
                case ColorDodge:
                    return &BlendColorDodge;
                    break;
                case LinearDodge:
                    return &BlendLinearDodge;
                    break;
                case LighterColor:
                    return &BlendLighterColor;
                    break;
                case Overlay:
                    return &BlendOverlay;
                    break;
                case SoftLight:
                    return &BlendSoftLight;
                    break;
                case HardLight:
                    return &BlendHardLight;
                    break;
                case VividLight:
                    return &BlendVividLight;
                    break;
                case LinearLight:
                    return &BlendLinearLight;
                    break;
                case PinLight:
                    return &BlendPinLight;
                    break;
                case HardMix:
                    return &BlendHardMix;
                    break;
                case Difference:
                    return &BlendDifference;
                    break;
                case Exclusion:
                    return &BlendExclusion;
                    break;
                case Subtract:
                    return &BlendSubtract;
                    break;
                case Divide:
                    return &BlendDivide;
                    break;
                case Hue:
                    return &BlendHue;
                    break;
                case Saturation:
                    return &BlendSaturation;
                    break;
                case Color:
                    return &BlendColor;
                    break;
                case Luminosity:
                    return &BlendLuminosity;
                    break;
            }
        };        
    } // namespace operations
    
    
} // namespace image