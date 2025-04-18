#version 330 core

in Varyings {
    vec4 color;
    vec2 tex_coord;
} fs_in;
out vec4 frag_color;

uniform sampler2D tex;

void main() {
    frag_color = texture(tex, fs_in.tex_coord);
}
