#include <iostream>
#include <stdexcept>
#include <core.h>
#include <cmath>
#include <random>
using namespace std;


void ErrorCallback(const int code,const char* const error){
    throw runtime_error(error);
}

const auto N = 100000;
const auto STRIDE = 5 * sizeof(GLfloat);

int main() {
    glfwSetErrorCallback(ErrorCallback);
    try {
        if (glfwInit() == GLFW_FALSE)
            throw runtime_error("Failed to initialize GLFW!");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
        glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
        glfwWindowHint(GLFW_SAMPLES, 4);

        GLFWwindow* const window = glfwCreateWindow(640, 640,"second_step",nullptr,nullptr);
        if (window == nullptr)
            throw runtime_error("Failed to create window!");
        glfwSetKeyCallback(window,KeyCallback);

        glfwMakeContextCurrent(window);
        {
            auto error = glewInit();
            if (error != GLEW_OK){
                auto message = reinterpret_cast<const char*>(glewGetErrorString(error));
                throw runtime_error(string("Failed to initialize GLEW:") + message);
            }
        }
        {
            int width,height;
            glfwGetFramebufferSize(window,&width,&height);
            glViewport(0,0,width,height);
        }
        glEnable(GL_PROGRAM_POINT_SIZE);
        //////////////////////////////////////////////////////////////////////////////////////////////////
        ShaderProgram program(
                {
                        {"shaders/vertex.glsl",   GL_VERTEX_SHADER},
                        {"shaders/fragment.glsl", GL_FRAGMENT_SHADER}
                });
        glUseProgram(program.id);

        const auto t_location = glGetUniformLocation(program.id, "t");
        if(t_location == -1){
            throw runtime_error("Failed to locate uniform varibale(s)!");
        }


        GLfloat data[STRIDE * N]={0};

        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<float> dis(-1.0, 1.0);// [-1;+1]

        for(size_t i=0; i < STRIDE * N; i+=5){
            data[i] = dis(gen);
        }
        for(size_t i=1; i < STRIDE * N; i+=5){
            data[i] = dis(gen);
        }
        for(size_t i=2; i < STRIDE * N; i+=5){
            data[i] = fabs(dis(gen));
        }
        for(size_t i=3; i < STRIDE * N; i+=5){
            data[i] = fabs(dis(gen));
        }
        for(size_t i=4; i < STRIDE * N; i+=5){
            data[i] = fabs(dis(gen));
        }
        GLuint vbo;
        {
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
        }

        GLuint vao;
        {
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
            const auto v_location = glGetAttribLocation(program.id, "v");
            const auto rgb_location = glGetAttribLocation(program.id, "rgb");
            if (v_location == -1 || rgb_location == -1) {
                throw runtime_error("Failed to locate variable(s)!");
            }
            glVertexAttribPointer(v_location, 2, GL_FLOAT, GL_FALSE, STRIDE, nullptr);
            glVertexAttribPointer(rgb_location, 3, GL_FLOAT, GL_FALSE, STRIDE,
                                  reinterpret_cast<void *>(sizeof(GLfloat) * 2));
            glEnableVertexAttribArray(v_location);
            glEnableVertexAttribArray(rgb_location);
        }
        glClearColor(1,1,1,1);

//////////////////////////////////////////////////////////////////////////////////////////////////
        while(!glfwWindowShouldClose(window)){
            glClear(GL_COLOR_BUFFER_BIT);

            glUniform1f(t_location, static_cast<GLfloat>(glfwGetTime()));
            glDrawArrays(GL_POINTS, 0, N);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    catch (const exception& e) {
        glfwTerminate();
        cout << e.what() << endl;
        return EXIT_FAILURE;
    }
}
