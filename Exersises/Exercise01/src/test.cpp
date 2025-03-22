#include <stdio.h>

#include "color.hpp"
#include "image.hpp"
#include "rasterize.hpp"

// The threshold beyond which we will consider two values to be unequal
#define THRESHOLD 0.0f
// Compare two images pixel-by-pixel.
// If both images match, the function will return true and img_diff will be black
// If there is a mismatch, the function will return false, and img_diff will mark the pixels (and channels) where the mismatch occured
bool compare(const Image<Color>& img_result, const Image<Color>& img_expected, Image<Color>& img_diff) {
    int width = img_result.get_width(), height = img_result.get_height();
    if(width != img_expected.get_width() || height != img_expected.get_height()) {
        fprintf(stderr, "Image dimension mismatch, expected %ix%i, found %ix%i\n", img_expected.get_width(), img_expected.get_height(), width, height);
        return false;
    }

    img_diff.allocate(width, height);
    const Color* buff_result = img_result.get_pixels();
    const Color* buff_expected = img_expected.get_pixels();
    Color* buff_diff = img_diff.get_pixels();

    bool match = true;

    for(int idx = 0, area = width*height; idx < area; ++idx){
        Color result = buff_result[idx];
        Color expected = buff_expected[idx];
        Color error = { 
            abs(result.r - expected.r),
            abs(result.g - expected.g),
            abs(result.b - expected.b)
        };
        bool match_r = error.r <= THRESHOLD;
        bool match_g = error.g <= THRESHOLD;
        bool match_b = error.b <= THRESHOLD;
        match = match && match_r && match_g && match_b;
        // If the error is small, it will be hard to see, so we add 0.5 to mismatched channel and use the remaining range to store the error.
        buff_diff[idx] = 0.5f * error + 0.5f * Color(!match_r, !match_g, !match_b);
    }

    return match;
}

int main(int argc, char** argv) {
    if(argc < 3) exit(1);

    char* tests_root_path = argv[1];
    char* test_name = argv[2];

    char scene_file_path[256], output_file_path[256], expected_file_path[256], error_file_path[256];
    sprintf(scene_file_path, "%s/scenes/%s.txt", tests_root_path, test_name);
    sprintf(output_file_path, "%s/results/%s.png", tests_root_path, test_name);
    sprintf(expected_file_path, "%s/expected/%s.png", tests_root_path, test_name);
    sprintf(error_file_path, "%s/errors/%s.png", tests_root_path, test_name);

    Image<Color> result;
    if(!draw_scene(scene_file_path, result)){
        fprintf(stderr, "Failed to draw the scene\n");
        exit(1);
    }
    result.save(output_file_path);

    Image<Color> expected;
    if(!expected.load(expected_file_path)){
        fprintf(stderr, "Expected result is not found\n");
        exit(1);
    }

    Image<Color> error;
    bool match = compare(result, expected, error);
    error.save(error_file_path);
    return match ? 0 : 1;
}