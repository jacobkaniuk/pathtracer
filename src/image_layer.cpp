#include "image_layer.h"

#include <memory>

using image::BlendMode;
using image::Layer;

Layer::Layer(ImageBuffer* image_buffer, const std::string& layer_name) : _layer_name(layer_name) {
    if (image_buffer) {
        _layer_image_buffer = image_buffer;
        return;
    }
    _layer_image_buffer = new ImageBuffer();
}
Layer::Layer(const Layer& copy) : _layer_image_buffer(copy._layer_image_buffer),
                                  _layer_name(copy._layer_name),
                                  _opacity(copy._opacity),
                                  _blend_mode(copy._blend_mode),
                                  _visibility(copy._visibility),
                                  _transform(copy._transform){};

Layer::Layer(Layer&& rval_copy) : _layer_image_buffer(rval_copy._layer_image_buffer),
                                  _layer_name(rval_copy._layer_name),
                                  _opacity(rval_copy._opacity),
                                  _blend_mode(rval_copy._blend_mode),
                                  _visibility(rval_copy._visibility),
                                  _transform(rval_copy._transform){};
Layer::~Layer() {
    delete _layer_image_buffer;
    _layer_image_buffer = nullptr;
}
void Layer::set_blend_mode(const BlendMode& blend_mode) {
    _blend_mode = blend_mode;
};
void Layer::set_visibility(const bool& visible) {
    _visibility = visible;
};
void Layer::set_transform(const Transform2D& transform) {
    _transform = transform;
};
void Layer::set_opacity(const float& opacity) {
    _opacity = opacity;
};
void Layer::clear_layer() {
    _layer_image_buffer->clear();
};
const std::string& Layer::get_name() const {
    return _layer_name;
};
ImageBuffer* Layer::get_image_buffer() const {
    return _layer_image_buffer;
};
const BlendMode& Layer::get_blend_mode() const {
    return _blend_mode;
};
const bool& Layer::is_visible() const {
    return _visibility;
};
const Transform2D& Layer::get_transform() const {
    return _transform;
};
const float& Layer::get_opacity() const {
    return _opacity;
};