#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 vertex_color;

uniform float time;

void main() {
    // Use the vertexID 
    gl_Position = vec4(position + vec3(sin(2 * time), 0.0, 0.0), 1.0);
    vertex_color = color;
}
