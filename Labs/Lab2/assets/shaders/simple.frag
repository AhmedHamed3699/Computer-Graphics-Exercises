#version 330 core

in vec4 vertex_color;
out vec4 frag_color;

uniform float time;

void main() {
    vec4 flicker = vec4(sin(10 * time), sin(10 * time + 1.0), sin(10 * time + 2.0), 1.0);
    flicker = flicker * 0.5 + 0.5;
    frag_color = vertex_color * flicker;
}
