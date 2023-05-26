#include <utility>
#include <vips/vips8>
#include "vipdroid.h"

Image::Image(vips::VImage image, effectsType * effects) {
    this->internal = std::move(image);
    this->effects_internal = effects;
}

void
ImageMaster::addImage(int index, unsigned int *data, size_t size, int width, int height, int bands,
                       VipsBandFormat format, effectsType * effects) {
    vips::VImage image = vips::VImage::new_from_memory(data, size, width, height, bands, format);
    this->addImage(index, new Image(image, effects));
}

ResolveFunctionResult ImageMaster::resolve() {
    auto images = this->images();
    for(Image * image : images) {
        auto img = image->image();
        auto effects = image->effects();

    }
}