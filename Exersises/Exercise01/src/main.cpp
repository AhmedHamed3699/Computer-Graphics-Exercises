#include <stdio.h>

#include "color.hpp"
#include "image.hpp"
#include "rasterize.hpp"

int main(int argc, char** argv){
    if(argc < 3) {
        printf("You must define the path to scene file and the path to which the image will be saved.\n");
        exit(1);
    }

    const char* scene_file_path = argv[1];
    const char* output_file_path = argv[2];

    Image<Color> framebuffer;

    if(!draw_scene(scene_file_path, framebuffer)){
        exit(1);
    }

    printf("Saving image to file: %s\n", output_file_path);
    framebuffer.save(output_file_path);

    return 0;
}
