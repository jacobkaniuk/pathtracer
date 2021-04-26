#ifndef IMAGE_LAYER_H
#define IMAGE_LAYER_H

#include "image_buffer.h"
#include "transform.h"

namespace image {

enum BlendMode {
    // normal
    Normal,
    Dissolve,
    // darker
    Darken,
    Multiply,
    ColorBurn,
    LinearBurn,
    DarkerColor,
    // lighter
    Lighten,
    Screen,
    ColorDodge,
    LinearDodge,
    LighterColor,
    // overlays
    Overlay,
    SoftLight,
    HardLight,
    VividLight,
    LinearLight,
    PinLight,
    HardMix,
    // functional
    Difference,
    Exclusion,
    Subtract,
    Divide,
    // color
    Hue,
    Saturation,
    Color,
    Luminosity
};

class Layer {
   private:
    ImageBuffer* _layer_image_buffer;
    std::string _layer_name;
    float _opacity;
    BlendMode _blend_mode;
    bool _visibility;
    Transform2D _transform;

   public:
    Layer(ImageBuffer* image_buffer = nullptr, const std::string& layer_name = "Layer");
    Layer(const Layer& copy);
    Layer(Layer&& rval_copy);
    ~Layer();

    void set_name(std::string& layer_name);
    void set_blend_mode(const BlendMode& blend_mode);
    void set_visibility(const bool& visible);
    void set_transform(const Transform2D& transform);
    void set_opacity(const float& opacity);
    void clear_layer();

    const std::string& get_name() const;
    ImageBuffer* get_image_buffer() const;
    const BlendMode& get_blend_mode() const;
    const bool& is_visible() const;
    const Transform2D& get_transform() const;
    const float& get_opacity() const;
};

}  // namespace image

#endif  // IMAGE_LAYER_H