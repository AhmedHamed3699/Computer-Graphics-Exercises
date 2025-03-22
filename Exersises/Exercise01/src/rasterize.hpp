#pragma once

#include <glm/vec2.hpp>
#include "color.hpp"
#include "image.hpp"

// Draw a point with the given color to the framebuffer
void draw_point(const glm::ivec2& point, const Color& color, Image<Color>& framebuffer);
// Draw a line with the given color to the framebuffer
void draw_line(const glm::ivec2 line[2], const Color& color, Image<Color>& framebuffer);
// Draw a triangle with the given color to the framebuffer
void draw_triangle(const glm::ivec2 triangle[3], const Color& color, Image<Color>& framebuffer);

// Draw a scene that can consist of points, lines and triangles to the framebuffer
bool draw_scene(const char* scene_file_path, Image<Color>& framebuffer);