#pragma once
#include <string>
#include "image/image.h"

class ImageSaver {
  public:
    virtual ~ImageSaver() = default;
    // Every saver writes the whole image to path, or throws a std::runtime_error.
    virtual void save(const Image& image, const std::string& path) const = 0;
};
