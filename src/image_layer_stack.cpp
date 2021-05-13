#include <fmt/core.h>
#include <string>
#include <iterator>
#include <chrono>
#include <thread>

#include "image_layer_stack.h"
#include "blend_ops.hpp"
#include "resolution.h"

 
image::LayerStack::LayerStack(const BitDepth& bit_depth, const display::resolution& resolution) : _bit_depth(bit_depth) {
    _output_image = new ImageBuffer(resolution, bit_depth);
    _width  = display::get_resolution_values(resolution).first;
    _height = display::get_resolution_values(resolution).second;
};
image::LayerStack::LayerStack(const BitDepth& bit_depth, const int& width, const int& height) : _bit_depth(bit_depth), _width(width), _height(height) {
    _output_image = new ImageBuffer(_width, _height, bit_depth);
    _layer_count = 0;
};
image::LayerStack::LayerStack(ImageBuffer& base_image_buffer) {
    _output_image = new ImageBuffer(base_image_buffer);
}
image::LayerStack::~LayerStack() {
    delete _output_image;
    for (auto* l : _layer_stack) {
        delete l;
        l = nullptr;
    }
}

void image::LayerStack::_rebuild_output_image(int index) {
    // Main function always called when making modifications to the layer stack. This can
    // be either adding or removing layers, modifying layer order, modifying layer opacity, etc.
    // as these are all operations which would change the final output_image
    //
    // 1. rebuild the output image by traversing the list from begin to end
    // 2. use the blendmodes as key to a map of funcptrs for each blend mode's required calculations
    // 3. before we rebuild, check the index to see where the new layer was created/inserted at, we might
    // only need to rebuild for 1 layer (ie. if addding a new layer, calculate from the output_image + new_layer through new layer blend mode)
    // 4. before we rebuild, check our cache to see if we have a calculated layer somewhere close to the
    // index passed in as a base to start from. (ie. if layer stack is 12 count, if we move layer to index 5,
    // check to see if there is a cache closest to 5 -> 4 is cached, start rebuild calculation chain from cached layer 4)   
    
    auto it = _layer_stack.begin();
    std::advance(it, index);
    Layer* target_layer = *it;
    std::cout << "Found layer to rebuild from: " << target_layer->get_name() << std::endl;
    _output_image = target_layer->get_image_buffer(); // set our output as the base layer we will work up from
    
    #ifdef PERF_LOG
        auto start = std::chrono::high_resolution_clock::now();    
    #endif

    const int max_thread_count = 128;
    std::thread blend_op_threads[max_thread_count];

    int thread_index=0;
    while(it != _layer_stack.end()){
        Layer* next_top_layer = *it;        
        for (int i=0; i< target_layer->get_image_buffer()->size()-1; i++){
            Pixel* bottom_pixel     = &_output_image->get_pixel(i);
            Pixel* top_pixel        = &next_top_layer->get_image_buffer()->get_pixel(i);
            Pixel* output_pixel     = &_output_image->get_pixel(i);

            if (blend_op_threads[thread_index].joinable()){
                blend_op_threads[thread_index] = std::thread(image::operations::run_blend_op, next_top_layer->get_blend_mode(), top_pixel, bottom_pixel, output_pixel, next_top_layer->get_opacity());
                blend_op_threads[thread_index].join();
            }            
        }
        ++it;

        if (thread_index >= max_thread_count) thread_index = 0;
        ++thread_index;
    }
    
    #ifdef PERF_LOG
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
        std::cout << "Layer calculation took: " << duration.count() << "ms"<< std::endl;
    #endif
}

void image::LayerStack::new_layer() {
    std::string layer_name = _layer_count == 0 ? "New Layer" : fmt::format("New Layer ({})", _layer_count);
    ImageBuffer* new_buffer = new ImageBuffer(*_output_image);
    image::Layer* new_layer = new image::Layer(new_buffer, layer_name);
    _layer_stack.insert(_layer_stack.end(), new_layer);
    _layer_count++;
    top_layer = new_layer;
    bottom_layer = bottom_layer == nullptr ? new_layer : bottom_layer;
}
void image::LayerStack::delete_layer(image::Layer* layer) {
    // empty stack check
    if (_layer_stack.size() <= 0) return;

    if (layer == top_layer) {
        // if there's other layers under this one
        if (top_layer != *(_layer_stack.begin())) {
            // set second last layer to be new top layer
            top_layer = *(++_layer_stack.rbegin());
            // std::cout << "Changed top layer to " << top_layer->get_name() << std::endl;
        } else
            top_layer = nullptr;
    }

    else if (layer == bottom_layer) {
        // if there's other layers on top of this one
        if (bottom_layer != *(_layer_stack.end())) {
            // set second layer to be new bottom layer
            bottom_layer = *(++_layer_stack.begin());
            // std::cout << "Changed bottom layer to " << top_layer->get_name() << std::endl;
        } else
            bottom_layer = nullptr;
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
    // check if we're moving the top or bottom layer, if so, we'll have to reassign after move
    image::Layer* new_top_layer = nullptr;
    image::Layer* new_bottom_layer = nullptr;
    if (layer == top_layer){
        // set the new top layer to the 2nd last layer
        // TODO add a check to make sure there's not only 1 or 2 layers where this iterator would break
        new_top_layer = *(++rit_end());
    }
    else if (layer == bottom_layer){
        // TODO a check again to make sure there's not only 1 or 2 layers where this iterator would break
        // set the new bottom layer to the 2nd layer
        new_bottom_layer = *(++it_begin());
    }
    
    // start from back or front of list based on index value. if higher than half, start from
    // end and work towards start. if less than half, start from start and work towards end
    auto start = layer_index > _layer_count / 2 ? _layer_stack.begin() : _layer_stack.end();
    auto end = start == _layer_stack.begin() ? _layer_stack.end() : _layer_stack.begin();
    int index = start == _layer_stack.begin() ? 0 : _layer_count;

    // pop the layer out first so we can insert at correct index
    _layer_stack.remove(layer);

    // move forwards or backwards, increment or decrement based on start and end
    for (std::list<image::Layer*>::iterator it = layer_index > _layer_count / 2 ? _layer_stack.begin() : _layer_stack.end(); it != _layer_stack.end(); start == _layer_stack.begin() ? ++it : --it) {
        if (layer_index == index) {
            // move our layer to the provided index and rebuild our output
            _layer_stack.insert(it, layer);
            _rebuild_output_image(layer_index);
            if (new_top_layer)
                top_layer = new_top_layer;
            else if (new_bottom_layer)
                bottom_layer = new_bottom_layer;
            return;
        }
        // increment or decrement index based on start and end
        start == _layer_stack.begin() ? index++ : index--;
    }
};