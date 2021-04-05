#ifndef IMAGE_LAYER_H
#define IMAGE_LAYER_H

#include "image_buffer.h"
#include "transform.h"

enum BlendMode {
    Normal,
    Dissolve,
    Multiply,
    Screen,
    Overlay,
    HardLight,
    SoftLight,
    Dodge,
    Burn,
    Divide,
    Add,
    Subtract,
    Difference,
    Darken,
    Lighten,
    Hue,
    Saturation,
    Color,
    Luminosity
};

class ImageLayer {
   private:
    ImageBuffer* _layer_image_buffer;
    float _opacity;
    BlendMode _blend_mode;
    bool _visibility;
    Transform2D _transform;

   public:
    ImageLayer(ImageBuffer* image_buffer=nullptr);
    ImageLayer();
    ~ImageLayer();
    void set_blend_mode(const BlendMode& blend_mode);
    void set_visibility(const bool& visible);
    void set_transform(const Transform2D& transform);
    void set_opacity(const float& opacity);
    void clear_layer();
    
    const ImageBuffer* get_image_buffer() const;
    const BlendMode& get_blend_mode() const;
    const bool& is_visible() const;
    const Transform2D& get_transform() const;
    const float& get_opacity() const;

};

#endif  // IMAGE_LAYER_H