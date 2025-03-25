#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 vertex_color;

uniform mat4 MVP;

void main() {
    // Use the vertexID 
    gl_Position = MVP * vec4(position, 1.0);
    vertex_color = color;
}
