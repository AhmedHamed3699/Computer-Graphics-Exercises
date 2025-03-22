#include "image.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "color.hpp"

template<>
void Image<Color>::save(const char *file_path)
{
    if(pixels == nullptr) return;
    int area = width * height;
    stbi_uc* buffer = new stbi_uc[area * 3];
    int byte_idx = 0;
    for(int index = 0; index < area; index++){
        Color& color = pixels[index];
        // Before saving the image, we apply gamma correction and quantize the channels into 8-bits. 
        buffer[byte_idx++] = encode(color.r);
        buffer[byte_idx++] = encode(color.g);
        buffer[byte_idx++] = encode(color.b);
    }
    // Since images assume that the first row is at the top, we flip the image while saving so that the first row is at the bottom  
    stbi_flip_vertically_on_write(true);
    stbi_write_png(file_path, width, height, 3, buffer, width*3);
    delete[] buffer;
}


template<>
bool Image<Color>::load(const char *file_path)
{
    int width, height, channels;
    // Since images assume that the first row is at the top, we flip the image while loading so that the first row is at the bottom
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* buffer = stbi_load(file_path, &width, &height, &channels, 3);
    if(!buffer) return false; // The file was not loaded successfully
    allocate(width, height);
    int area = width * height;
    int byte_idx = 0;
    for(int index = 0; index < area; index++){
        Color& color = pixels[index];
        // After loading the image, we dequantize the channels and apply the gamma curve. 
        color.r = decode(buffer[byte_idx++]);
        color.g = decode(buffer[byte_idx++]);
        color.b = decode(buffer[byte_idx++]);
    }
    STBI_FREE(buffer);
    return true;
}