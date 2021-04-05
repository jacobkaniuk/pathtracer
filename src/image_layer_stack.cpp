#include "image_layer_stack.h"
#include "resolution.h"

image::LayerStack::LayerStack(const BitDepth& bit_depth, const display::resolution& resolution): _bit_depth(bit_depth) {
    _width = display::get_resolution_values(resolution).first;
    _height = display::get_resolution_values(resolution).second;
};
image::LayerStack::LayerStack(const BitDepth& bit_depth, const int& width, const int& height): _bit_depth(bit_depth), _width(width), _height(height) {
    _output_image = new ImageBuffer(_width, _height);
};
image::LayerStack::LayerStack(ImageBuffer& base_image_buffer){
    _output_image = new ImageBuffer(base_image_buffer);   
}   
image::LayerStack::~LayerStack() {
    delete _output_image;
}
void image::LayerStack::new_layer(){
    _stack.emplace(image::Layer());
}
void image::LayerStack::delete_layer(image::Layer& layer) {

};
void image::LayerStack::add_layer(image::Layer& layer) {
    _stack.push(std::move(layer));
};
void image::LayerStack::move_layer(image::Layer& layer, int layer_index) {    
    std::stack<Layer> temp;
    if (_stack.size() >= 1){
        // split the stack so we can inject our new layer at index
        for (int i = _stack.size(); i<layer_index; --i){
            temp.push(std::move(_stack.top()));
            _stack.pop();
        }
        // inject at index
        _stack.push(std::move(layer));
        // push removed layers back on
        for (int j = 0; j<temp.size()-1; ++j){
            _stack.push(std::move(temp.top()));
            temp.pop();
        }
    }
};