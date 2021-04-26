#ifndef BLEND_OPS_H
#define BLEND_OPS_H

#include <algorithm>

#include "image_layer.h"

namespace image 
{
    namespace operations
    {
        inline void BlendNormal(Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity){
            // formula is 1-opacity(a) + opacity(b)
            output_pixel->set_value(
                (1.0f - opacity) * (*top_pixel)[0] + (opacity * (*bottom_pixel)[0]),
                (1.0f - opacity) * (*top_pixel)[1] + (opacity * (*bottom_pixel)[1]),
                (1.0f - opacity) * (*top_pixel)[2] + (opacity * (*bottom_pixel)[2]),
                output_pixel->max_value()
            );
        }

        inline void BlendDissolve(Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendDarken(Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {
            // formula is min(a,b) + (max(a,b) - min(a,b) * (1-opacity))
            auto min_x = std::min((*top_pixel)[0], (*bottom_pixel)[0]);
            auto max_x = min_x == (*top_pixel)[0] ? (*bottom_pixel)[0] : (*top_pixel)[0];
            auto min_y = std::min((*top_pixel)[1], (*bottom_pixel)[1]);
            auto max_y = min_y == (*top_pixel)[1] ? (*bottom_pixel)[1] : (*top_pixel)[1];
            auto min_z = std::min((*top_pixel)[2], (*bottom_pixel)[2]);
            auto max_z = min_z == (*top_pixel)[2] ? (*bottom_pixel)[2] : (*top_pixel)[2];

            output_pixel->set_value(
                min_x + ((max_x - min_x) * (1 - opacity)),
                min_y + ((max_y - min_y) * (1 - opacity)),
                min_z + ((max_z - min_z) * (1 - opacity)),
                (*output_pixel)[3]
            );
        };

        inline void BlendMultiply(Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {
            auto max_val = bottom_pixel->max_value();
            auto new_x = (*top_pixel)[0] * (float)(*bottom_pixel)[0]/max_val;
            auto new_y = (*top_pixel)[1] * (float)(*bottom_pixel)[1]/max_val;
            auto new_z = (*top_pixel)[2] * (float)(*bottom_pixel)[2]/max_val;
            
            output_pixel->set_value(
                (1.0f - opacity) * new_x + (opacity * (*bottom_pixel)[0]),
                (1.0f - opacity) * new_y + (opacity * (*bottom_pixel)[1]),
                (1.0f - opacity) * new_z + (opacity * (*bottom_pixel)[2]),
                (*output_pixel)[3]
            );
        };
        inline void BlendColorBurn      (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {
            
        };
        inline void BlendLinearBurn     (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendDarkerColor    (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendLighten        (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendScreen         (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendColorDodge     (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendLinearDodge    (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendLighterColor   (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendOverlay        (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendSoftLight      (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendHardLight      (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendVividLight     (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendLinearLight    (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendPinLight       (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendHardMix        (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendDifference     (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendExclusion      (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendSubtract       (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendDivide         (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendHue            (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendSaturation     (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendColor          (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};
        inline void BlendLuminosity     (Pixel* top_pixel, Pixel* bottom_pixel, Pixel* output_pixel, float opacity) {};

        decltype(auto) get_blend_mode_operation(const image::BlendMode& blendmode);
    }
}   

#endif // BLEND_OPS_H
