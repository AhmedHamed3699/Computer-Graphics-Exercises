#include "rasterize.hpp"

#include <stdio.h>
#include <string.h>
#include <glm/glm.hpp>

// Some helper functions that you may need
template<typename T>
void swap(T& a, T& b) { T temp = a; a = b; b = temp; }
template<typename T>
T min(T a, T b) { return a < b ? a : b; }
template<typename T>
T max(T a, T b) { return a > b ? a : b; }

void draw_point(const glm::ivec2& point, const Color& color, Image<Color>& framebuffer){
    framebuffer.set_pixel(point.x, point.y, color);
}

// Note: It is recommended that you apply bresenham's line drawing algorithm here
void draw_line(const glm::ivec2 line[2], const Color& color, Image<Color>& framebuffer) {
    //TODO: Write this function
}

// Note: It is recommended that you apply the scanline triangle rasterization algorithm here
void draw_triangle(const glm::ivec2 triangle[3], const Color& color, Image<Color>& framebuffer){
    //TODO: Write this function
}

/******************************************************************/
/******************************************************************/
/**                                                              **/
/****                                                          ****/
/******                                                      ******/
/******** Below is the function that draws the whole scene ********/
/******                                                      ******/
/****                                                          ****/
/**                                                              **/
/******************************************************************/
/******************************************************************/

// Yes, you have just arrived at the scene drawing function
bool draw_scene(const char *scene_file_path, Image<Color> &framebuffer)
{
    FILE* file = fopen(scene_file_path, "r");
    if(!file){
        printf("Failed to open file: %s\n", scene_file_path);
        return false; // Return false if we failed to open the file
    } else {
        printf("Rendering file: %s\n", scene_file_path);
    }

    // The first line in the scene file should contain the magic string "GFXEX01"
    // followed by the width and height of the image (framebuffer) to which the shapes will be rasterized 
    char magic_string[256];
    int width, height;
    fscanf(file, "%s %i %i", magic_string, &width, &height);
    if(strcmp(magic_string, "GFXEX01") != 0){
        printf("Invalid scene file format\n");
        return false;
    }

    framebuffer.allocate(width, height);

    // Since the scene files store color using the hex notation (e.g. FF0000 means red),
    // we read the hex color as an integer then decodes it in a Color (a 3d vector containing the RGB channels). 
    auto decode_rgb = [](unsigned int encoded) -> Color {
        float r = decode((encoded >> 16) & 0xFF);
        float g = decode((encoded >> 8) & 0xFF);
        float b = decode(encoded & 0xFF);
        return Color(r, g, b);
    };

    char command[256];
    while(!feof(file)){
        fscanf(file, "%s", command);
        
        if(strlen(command) == 0) continue; // Ignore empty lines

        if(strcmp(command, "clear") == 0) { // Clear the framebuffer

            unsigned int encoded_rgb;
            fscanf(file, "%x", &encoded_rgb);
            framebuffer.clear(decode_rgb(encoded_rgb));

        } else if(strcmp(command, "point") == 0) { // Draw a point

            glm::ivec2 point;
            unsigned int encoded_rgb;
            fscanf(file, "%x %i %i", 
                &encoded_rgb,
                &point.x, &point.y
            );
            draw_point(point, decode_rgb(encoded_rgb), framebuffer);
        
        } else if(strcmp(command, "line") == 0) { // Draw a line

            glm::ivec2 line[2];
            unsigned int encoded_rgb;
            fscanf(file, "%x %i %i > %i %i",
                &encoded_rgb,
                &line[0].x, &line[0].y,
                &line[1].x, &line[1].y
            );
            draw_line(line, decode_rgb(encoded_rgb), framebuffer);

        } else if(strcmp(command, "triangle") == 0) { // Draw a line

            glm::ivec2 triangle[3];
            unsigned int encoded_rgb;
            fscanf(file, "%x %i %i > %i %i > %i %i", 
                &encoded_rgb,
                &triangle[0].x, &triangle[0].y,
                &triangle[1].x, &triangle[1].y,
                &triangle[2].x, &triangle[2].y
            );
            draw_triangle(triangle, decode_rgb(encoded_rgb), framebuffer);

        } else if(command[0] == '#') { // Ignore comments

            fscanf(file, "%*[^\n]");

        }
        
    }

    return true;
}
