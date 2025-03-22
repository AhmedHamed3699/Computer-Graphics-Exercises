#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

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
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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
        glfwCreateWindow(1280, 720, "Hello Triangle", nullptr, nullptr);
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

    while (!glfwWindowShouldClose(window)) // rendering loop
    {
        float time = (float)glfwGetTime();
        glClearColor(0.5 * sinf(time) + 0.5, 0.5 * sinf(time + 1) + 0.5,
                     0.5 * sinf(time + 2) + 0.5, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        GLuint vertex_array;
        glGenVertexArrays(1, &vertex_array);

        glUseProgram(program);
        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}