#include <core.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

// Вспомогательный метод для компиляции одного шейдера.
// Принимает путь к файлу с исходным кодом шейдера и тип создаваемого шейдера.
// Возвращает идентификатор созданного шейдера.
// Генерирует исключение в случае какой-либо ошибки.
static GLuint CompileShader(const string& path, const GLenum shaderType) {
    // Шаг 1. Открыть файл, считать все его строки, закрыть файл.
    string code;
    {
        ifstream file(path); //possible exception
        if(file.fail()){
            throw runtime_error("Can't open file from this path");
        }
        stringstream temp;
        temp << file.rdbuf();
        code = temp.str();
    }
    // Шаг 2. Создать объект шейдера.
    auto shader = glCreateShader(shaderType);
    if(shader == 0){
        throw runtime_error("Failed to create a shader");
    }
    // Шаг 3. Привязать к созданному шейдеру считанные из файла строки исходного кода.
    const auto str = code.c_str();
    glShaderSource(shader, 1, &str, nullptr);
    // Шаг 4. Скомпилировать шейдер.
    glCompileShader(shader);
    // Шаг 5. Убедиться в успешности компиляции.
    GLint compile = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile);
    // Шаг 6. В случае успеха вернуть идентификатор скомпилированного шейдера.
    if(compile == GL_TRUE){
        return shader;
    }
    else{
        GLint log_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        vector<GLchar> log(log_length);
        glGetShaderInfoLog(shader, log_length, nullptr, log.data());
        glDeleteShader(shader);
        throw runtime_error(log.data());
    }
}


// Конструктор.
// Принимает произвольный набор пар вида ("Путь к файлу с исходным кодом шейдера", "Тип шейдера").
// Компилирует все указанные шейдеры и линкует их в шейдерную программу.
// Генерирует исключение в случае какой-либо ошибки.
ShaderProgram::ShaderProgram(initializer_list<pair<string, GLenum>> shaders) : id(glCreateProgram()) {
    // Шаг 1. Создать объект программы.
    // Шаг 2. Пройтись по всем парам и для каждой пары вызвать CompileShader и присоединить скомпилированный шейдер к программе.
    vector<GLuint> compiled_shaders(shaders.size());
    for(auto &n : shaders) {
        auto shader=CompileShader(n.first,n.second);
        compiled_shaders.push_back(shader);
        glAttachShader(id, shader);
    }
    // Шаг 3. Слинковать программу.
    glLinkProgram(id);
    auto linked = GLFW_FALSE;
    glGetProgramiv(id, GL_LINK_STATUS, &linked);
    if(!linked){
        GLint logLength = 0;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);
        vector<GLchar> log(logLength);
        glGetProgramInfoLog(id, logLength, nullptr, log.data());
        for (auto shader : compiled_shaders)
            glDeleteShader(shader);
        throw runtime_error(log.data());
    }
    for (auto shader : compiled_shaders)
        glDeleteShader(shader);

}

// Деструктор.
// Удаляет объект шейдерной программы.
ShaderProgram::~ShaderProgram() {
   glDeleteShader(id);
}

CircleProgram::CircleProgram() : ShaderProgram ({
                                         {"/home/alzeen/CLionProjects/OpenGL-master/app-task4-surprise-your-teacher/shaders/circle_vertex.glsl",   GL_VERTEX_SHADER},
                                         {"/home/alzeen/CLionProjects/OpenGL-master/app-task4-surprise-your-teacher/shaders/circle_fragment.glsl", GL_FRAGMENT_SHADER}
                                 }) {
    _segments = glGetUniformLocation(id, "segments");
    _center = glGetUniformLocation(id, "center");
    _radius = glGetUniformLocation(id, "radius");
    _color = glGetUniformLocation(id, "color");

    GLfloat dummy = 0;
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat), &dummy, GL_STATIC_DRAW);

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    const auto dummyLocation = glGetAttribLocation(id, "dummy");
    glVertexAttribPointer(dummyLocation, 1, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(dummyLocation);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void CircleProgram::Draw(const GLfloat x_center, const GLfloat y_center, const GLfloat radius, const GLfloat *const color) {

    const GLint segments = 30;

    glUseProgram(id);
    glBindVertexArray(_vao);
    glUniform1i(_segments, segments);
    glUniform2f(_center, x_center, y_center);
    glUniform1f(_radius, radius);
    glUniform4fv(_color, 1, color);

    glDrawArrays(GL_LINE_LOOP, 0 , segments);

    glBindVertexArray(0);
    glUseProgram(0);
}
CircleProgram::~CircleProgram()  {
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
}




