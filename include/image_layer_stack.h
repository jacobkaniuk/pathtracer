#ifndef IMAGE_LAYER_STACK
#define IMAGE_LAYER_STACK

#include <stack>

#include "image_buffer.h"
#include "image_layer.h"
#include "pixel.h"

namespace image {

class LayerStack {
private:
    ImageBuffer* _output_image;
    BitDepth _bit_depth;
    std::stack<image::Layer> _stack;
    int _width;
    int _height;
    
public:
    LayerStack(const BitDepth& bit_depth, const display::resolution& resolution);
    LayerStack(const BitDepth& bit_depth, const int& width, const int& height);
    LayerStack(ImageBuffer& base_image_buffer);
    ~LayerStack();

    void new_layer();
    void delete_layer(image::Layer& layer);
    void add_layer(image::Layer& layer);
    void move_layer(image::Layer& layer, int layer_index);
};

}  // namespace image

#endif  //IMAGE_LAYER_STACK