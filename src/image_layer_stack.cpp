#include <fmt/core.h>

#include "image_layer_stack.h"
#include "resolution.h"


image::LayerStack::LayerStack(const BitDepth& bit_depth, const display::resolution& resolution): _bit_depth(bit_depth) {
    _width = display::get_resolution_values(resolution).first;
    _height = display::get_resolution_values(resolution).second;
};
image::LayerStack::LayerStack(const BitDepth& bit_depth, const int& width, const int& height): _bit_depth(bit_depth), _width(width), _height(height) {
    _output_image = new ImageBuffer(_width, _height);
    _layer_count = 0;
};
image::LayerStack::LayerStack(ImageBuffer& base_image_buffer){
    _output_image = new ImageBuffer(base_image_buffer);   
}   
image::LayerStack::~LayerStack() {
    delete _output_image;
    for (auto* l : _layer_stack){
        delete l;
        l = nullptr;
    }
}

void image::LayerStack::_rebuild_output_image(int index){
    // Main function always called when making modifications to the layer stack. This can 
    // be either adding or removing layers, modifying layer order, modifying layer opacity, etc.
    // as these are all operations which would change the final output_image 
    //
    // TODO
    // 1. rebuild the output image by traversing the list from begin to end
    // 2. use the blendmodes as key to a map of funcptrs for each blend mode's required calculations
    // 3. before we rebuild, check the index to see where the new layer was created/inserted at, we might
    // only need to rebuild for 1 layer (ie. if addding a new layer, calculate from the output_image + new_layer through new layer blend mode)
    // 4. before we rebuild, check our cache to see if we have a calculated layer somewhere close to the 
    // index passed in as a base to start from. (ie. if layer stack is 12 count, if we move layer to index 5, 
    // check to see if there is a cache closest to 5 -> 4 is cached, start rebuild calculation chain from cached layer 4)
}

void image::LayerStack::new_layer(){
    std::string layer_name =  _layer_count == 0 ? "New Layer" : fmt::format("New Layer ({})", _layer_count);
    ImageBuffer* new_buffer = new ImageBuffer(*_output_image);
    image::Layer* new_layer = new image::Layer(new_buffer, layer_name);
    _layer_stack.emplace_back(new_layer);
    _layer_count++;
    top_layer = new_layer;
    bottom_layer = bottom_layer == nullptr ? new_layer : bottom_layer;
}
void image::LayerStack::delete_layer(image::Layer* layer) {
    if (layer == top_layer){
        // if there's other layers under this one
        if (top_layer != *(_layer_stack.begin())){        
            // set second last layer to be new top layer
            top_layer = *(++_layer_stack.rbegin());
            // std::cout << "Changed top layer to " << top_layer->get_name() << std::endl;
        }
        else top_layer = nullptr;
    }

    else if (layer == bottom_layer){
        if (bottom_layer != *(_layer_stack.end())){
            // set second layer to be new bottom layer
            bottom_layer = *(++_layer_stack.begin());
            // std::cout << "Changed bottom layer to " << top_layer->get_name() << std::endl;
        }
        else bottom_layer = nullptr;
    }

    _layer_stack.remove(layer);
    delete layer;
    layer = nullptr;
};
void image::LayerStack::add_layer(image::Layer* layer) {
    _layer_stack.insert(_layer_stack.end(), layer);
    top_layer = layer;
};
void image::LayerStack::move_layer(image::Layer* layer, const int& layer_index) {    
    // start from back or front of list based on index value. if higher than half, start from
    // end and work towards start. if less than half, start from start and work towards end
    auto start  = layer_index > _layer_count/2 ? _layer_stack.begin() : _layer_stack.end();
    auto end    = start == _layer_stack.begin() ? _layer_stack.end()  : _layer_stack.begin();
    int index   = start == _layer_stack.begin() ? 0 : _layer_count;
    // move forwards or backwards, increment or decrement based on start and end
    for (std::list<image::Layer*>::iterator it = layer_index > _layer_count/2 ? _layer_stack.begin() : _layer_stack.end(); it != _layer_stack.end(); start == _layer_stack.begin() ? ++it : --it){
        if (layer_index == index){
            // move our layer to the provided index and rebuild our output
            _layer_stack.insert(it, layer);
            _rebuild_output_image(layer_index);
            return;
        }
        // increment or decrement index based on start and end
        start == _layer_stack.begin() ? index++ : index--;
    }
};