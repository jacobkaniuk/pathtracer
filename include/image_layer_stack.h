#ifndef IMAGE_LAYER_STACK
#define IMAGE_LAYER_STACK

#include <list>

#include "image_buffer.h"
#include "image_layer.h"
#include "pixel.h"

namespace image {

class LayerStackCache {
    /* Cache container which will store previously computed layer
     data at different stages in the layer stack. This ensures we don't 
     recalculate the image buffer at different stages in the layer stack pointlessly
    */
public:
    LayerStackCache();
    ~LayerStackCache();
};


class LayerStack {
private:
    void _rebuild_output_image(int index);

    ImageBuffer* _output_image;
    BitDepth _bit_depth;
    std::list<image::Layer*> _layer_stack;
    int _width;
    int _height;
    int _layer_count;
    
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