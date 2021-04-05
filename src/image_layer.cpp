#include <memory>

#include "image_layer.h"

ImageLayer::ImageLayer(ImageBuffer* image_buffer) {
    if (image_buffer){
        _layer_image_buffer = image_buffer;
        return;
    }
    _layer_image_buffer = new ImageBuffer();
}
ImageLayer::~ImageLayer() {
    delete _layer_image_buffer;
}
void ImageLayer::set_blend_mode(const BlendMode& blend_mode){
    _blend_mode = blend_mode;
};
void ImageLayer::set_visibility(const bool& visible){
    _visibility = visible;
};
void ImageLayer::set_transform(const Transform2D& transform){
    _transform = transform;
};
void ImageLayer::set_opacity(const float& opacity){
    _opacity = opacity;
};
void ImageLayer::clear_layer(){
    _layer_image_buffer->clear();
};
const ImageBuffer* ImageLayer::get_image_buffer() const {
    return _layer_image_buffer;
};
const BlendMode& ImageLayer::get_blend_mode() const {
    return _blend_mode;
};
const bool& ImageLayer::is_visible() const {
    return _visibility;
};
const Transform2D& ImageLayer::get_transform() const {
    return _transform;
};
const float& ImageLayer::get_opacity() const {
    return _opacity;
};