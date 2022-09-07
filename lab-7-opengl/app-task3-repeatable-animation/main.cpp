#include <iostream>
#include <stdexcept>
#include <core.h>
#include <vector>

using namespace std;


void ErrorCallback(const int code,const char* const error){
    throw runtime_error(error);
}

const auto STRIDE = 8 * sizeof(GLfloat);
/*          layout std140:
|------------------------>| - stride = 8 * sizeof(GLfloat)
|t0|..|v.x|v.y|r |g |b |a |
|fl|  |  vec2 |    vec4   |
                shift:
nullptr
|---->| - 2 * sizeof(GLfloat)
|------------>| - 4 * sizeof(GLfloat)*/
const auto N = 100;

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

        GLFWwindow* const window = glfwCreateWindow(640, 640,"third_step",nullptr,nullptr);
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
        ShaderProgram program({
                        {"shaders/vertex.glsl",   GL_VERTEX_SHADER},
                        {"shaders/fragment.glsl", GL_FRAGMENT_SHADER}
                });
        ShaderProgram change_program( {{"shaders/change.glsl",   GL_COMPUTE_SHADER}});
        ShaderProgram initialize_program({{"shaders/init.glsl", GL_COMPUTE_SHADER}});


        const auto initialize_time_location = glGetUniformLocation(initialize_program.id, "t");

        const auto change_time_location = glGetUniformLocation(change_program.id, "t");

        const auto program_time_location = glGetUniformLocation(program.id, "t");
        if(initialize_time_location == -1 || change_time_location == -1 || program_time_location == -1){
            throw runtime_error("Failed to locate uniform variable(s)!");
        }

        GLuint vbo;
        {
            glGenBuffers(1, &vbo);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            vector<GLbyte> data(N * STRIDE);
            glBufferData(GL_ARRAY_BUFFER, N * STRIDE, data.data(), GL_DYNAMIC_COPY);
        }

        glUseProgram(initialize_program.id);
        glUniform1f(initialize_time_location, static_cast<GLfloat>(glfwGetTime()));
        glDispatchCompute(N, 1, 1);
        glUseProgram(0);
        glDeleteProgram(initialize_program.id);



        GLuint vao;
        {
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            const auto t0_location = glGetAttribLocation(program.id, "t0");
            const auto v_location = glGetAttribLocation(program.id, "v");
            const auto rgb_location = glGetAttribLocation(program.id, "rgba");
            if (t0_location == -1 || rgb_location == -1 || v_location == -1)
                throw runtime_error("Failed to locate attribute(s)!");

            glVertexAttribPointer(t0_location, 1, GL_FLOAT, GL_FALSE, STRIDE,
                                  reinterpret_cast<GLvoid *>(0 * sizeof(GLfloat)));
            glVertexAttribPointer(v_location, 2, GL_FLOAT, GL_FALSE, STRIDE,
                                  reinterpret_cast<GLvoid *>(2 * sizeof(GLfloat)));
            glVertexAttribPointer(rgb_location, 4, GL_FLOAT, GL_FALSE, STRIDE,
                                  reinterpret_cast<GLvoid *>(4 * sizeof(GLfloat)));


            glEnableVertexAttribArray(t0_location);
            glEnableVertexAttribArray(v_location);
            glEnableVertexAttribArray(rgb_location);

        }
        glClearColor(1, 1, 1, 1);
        glUseProgram(program.id);
        glUseProgram(0);
//////////////////////////////////////////////////////////////////////////////////////////////////
        while(!glfwWindowShouldClose(window)){
                glClear(GL_COLOR_BUFFER_BIT);
                const auto time = static_cast<GLfloat>(glfwGetTime());

                glUseProgram(change_program.id);
                glUniform1f(change_time_location, time);
                glDispatchCompute(N, 1, 1);
                glUseProgram(0);

                glMemoryBarrier(GL_ALL_BARRIER_BITS);

                glUseProgram(program.id);
                glUniform1f(program_time_location, time);
                glDrawArrays(GL_POINTS, 0, N);
                glUseProgram(0);

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