#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

struct Color {
    uint8_t r, g, b, a;
};
struct Vertex {
    glm::vec3 position;
    Color color;
    glm::vec2 texture;
};

GLuint loadShader(const string &path, GLenum shaderType) {
    ifstream file(path);
    string sourceCode =
        string(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
    const char *sourceCodeCStr = sourceCode.c_str();
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &sourceCodeCStr, nullptr);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char *logInfo = new char[length];
        glGetShaderInfoLog(shader, length, nullptr, logInfo);
        cerr << "ERROR IN " << path << endl;
        cerr << logInfo << endl;
        glDeleteShader(shader);
        delete[] logInfo;
        return 0;
    }
    return shader;
}

int main() {
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW!";
        exit(1);
    }

    // opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Make window size fixed (User can't resize it)
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    // Set Number of sample used in MSAA (0 = Disabled)
    glfwWindowHint(GLFW_SAMPLES, 0);

    // Enable Double Buffering
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    // Set the bit-depths of the frame buffer
    glfwWindowHint(GLFW_RED_BITS, 8);
    glfwWindowHint(GLFW_GREEN_BITS, 8);
    glfwWindowHint(GLFW_BLUE_BITS, 8);
    glfwWindowHint(GLFW_ALPHA_BITS, 8);

    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);

    GLFWwindow *window =
        glfwCreateWindow(750, 750, "Hello Triangle", nullptr, nullptr);
    if (!window) {
        cerr << "Failed to create window!";
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        cerr << "Failed to load OpenGL!";
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(1);
    }

    GLuint program = glCreateProgram();

    GLuint VertShader =
        loadShader("assets/shaders/simple.vert", GL_VERTEX_SHADER);
    glAttachShader(program, VertShader);
    glDeleteShader(VertShader);

    GLuint FragShader =
        loadShader("assets/shaders/simple.frag", GL_FRAGMENT_SHADER);
    glAttachShader(program, FragShader);
    glDeleteShader(FragShader);

    glLinkProgram(program);

    GLuint mvp_loc = glGetUniformLocation(program, "MVP");
    GLuint tex_loc = glGetUniformLocation(program, "tex");

    const Vertex vertices[4] = {
        {{-0.5, 0.5, 0.0}, {255, 0, 0, 255}, {0.0, 1.0}},
        {{0.5, -0.5, 0.0}, {0, 255, 0, 255}, {1.0, 0.0}},
        {{-0.5, -0.5, 0.0}, {0, 0, 255, 255}, {0.0, 0.0}},
        {{0.5, 0.5, 0.0}, {0, 255, 255, 255}, {1.0, 1.0}}};

    const uint16_t elements[6] = {0, 1, 2, 0, 1, 3};

    const Color W = {255, 255, 255, 255};
    const Color B = {0, 0, 0, 255};
    const Color Y = {255, 255, 0, 255};

    const Color image[] = {
        W, W, Y, Y, Y, Y, W, W, W, Y, Y, B, B, Y, Y, W, Y, Y, B, Y, Y, B,
        Y, Y, Y, Y, Y, Y, Y, Y, Y, Y, Y, Y, B, Y, Y, B, Y, Y, Y, Y, B, Y,
        Y, B, Y, Y, W, Y, Y, Y, Y, Y, Y, W, W, W, Y, Y, Y, Y, W, W,
    };

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 image);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    GLuint element_buffer;
    glGenBuffers(1, &element_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint16_t), elements,
                 GL_STATIC_DRAW);

    GLuint position_loc = 0; // glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(position_loc);
    glVertexAttribPointer(position_loc, 3, GL_FLOAT, false, sizeof(Vertex), 0);

    GLuint color_loc = 1;
    glEnableVertexAttribArray(color_loc);
    glVertexAttribPointer(color_loc, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex),
                          (void *)offsetof(Vertex, color));

    GLuint tex_coord_loc = 2;
    glEnableVertexAttribArray(tex_coord_loc);
    glVertexAttribPointer(tex_coord_loc, 2, GL_FLOAT, false, sizeof(Vertex),
                          (void *)offsetof(Vertex, texture));

    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0f);

    while (!glfwWindowShouldClose(window)) // rendering loop
    {
        int width, hight;
        glfwGetFramebufferSize(window, &width, &hight);
        glViewport(0, 0, width, hight);

        float time = (float)glfwGetTime();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vertex_array);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(tex_loc, 0);

        glm::mat4 P = glm::perspective(glm::pi<float>() * 0.5f,
                                       (float)width / hight, 0.01f, 1000.0f);
        glm::mat4 V =
            glm::lookAt(glm::vec3(2.0 * cosf(time), 1.0, 2.0 * sinf(time)),
                        glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

        for (int i = -2; i <= 2; i++) {
            glm::mat4 M =
                glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, (float)i));
            glm::mat4 MVP = P * V * M;

            glUniformMatrix4fv(mvp_loc, 1, false, &MVP[0][0]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}