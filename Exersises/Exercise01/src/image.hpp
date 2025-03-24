#pragma once
#include <stdlib.h>
#include <cmath>

// Image<T> is a template class holding an image (2D array) where each pixel is of type T
template<typename T>
class Image {
public:
    
    Image() = default;
    // To avoid any problems that copying may cause, we delete the copy constructor and assignment operator
    Image(const Image<T>&) = delete;
    Image<T>& operator=(const Image<T>&) = delete;
    // This constructon allocate an image of size: width x height
    Image(int width, int height) { allocate(width, height); }
    ~Image(){ if(pixels) delete[] pixels; }

    // Allocates an image of size: width x height
    void allocate(int width, int height) {
        this->width = width;
        this->height = height;
        if(pixels) delete[] pixels; // Delete the pixel array if it was already allocated
        pixels = new T[width * height];
    }

    int get_width() const { return width; }
    int get_height() const { return height; }

    // Gets a pixel to the raw pixel array in case we want to read/write many pixels without the overhead of get/set_pixel
    const T* get_pixels() const { return pixels; }
    T* get_pixels() { return pixels; }

    // Gets the pixel at (x,y)
    // If (x,y) is out of the image bound, the zero value of T will be returned. 
    T get_pixel(int x, int y) const {
        if(0 <= x && x < width && 0 <= y && y < height)
            return pixels[x + y * width];
        else
            return T(0); 
    }

    // Sets the pixel at (x,y)
    // If (x,y) is out of the image bound, nothing will be modified.
    void set_pixel(int x, int y, const T& color) {
        if(0 <= x && x < width && 0 <= y && y < height) 
            pixels[x + y * width] = color;
    }

    // Clears all of the pixels with the given color
    void clear(const T& clear_color) {
        for(int idx = width * height - 1; idx >= 0; --idx)
            pixels[idx] = clear_color;
    }

    // Saves/loads the image to/from a file
    void save(const char* file_path);
    bool load(const char* file_path);

private:
    int width = 0;
    int height = 0;
    T* pixels = nullptr;
};