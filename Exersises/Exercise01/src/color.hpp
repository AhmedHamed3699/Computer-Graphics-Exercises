#pragma once

#include <glm/vec3.hpp>

// We will define colors using the RGB components in the linear sRGB space
typedef glm::vec3 Color;
// Applies gamma correction to a channel (linear space -> gamma space), then quantizes the result to 8-bits
unsigned char encode(float x);
// Converts a quantized channel to float, then applies the gamma curve (gamma space -> linear space)
float decode(unsigned char x);