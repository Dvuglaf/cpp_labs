#pragma once

#include <initializer_list> // initializer_list
#include <string>           // string
#include <utility>          // pair

#include <GL/glew.h>        // Библиотеки GLEW и OpenGL
#include <GLFW/glfw3.h>     // Библиотека GLFW
// Обработчик событий клавиатуры.
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// Вспомогательный класс для компиляции и линковки шейдерной программы.
struct ShaderProgram {
    // Идентификатор созданной шейдерной программы.
    const GLenum id;

    // Конструктор.
    // Принимает произвольный набор пар вида ("Путь к файлу с исходным кодом шейдера", "Тип шейдера").
    // Компилирует все указанные шейдеры и линкует их в шейдерную программу.
    // Генерирует исключение в случае какой-либо ошибки.
    //ShaderProgram() {;}
    ShaderProgram(std::initializer_list<std::pair<std::string, GLenum>> );

    // Запрещаем операцию копирования.
    ShaderProgram(const ShaderProgram&) = delete;

    // Запрещаем операцию присваивания копированием.
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    // Деструктор.
    // Удаляет объект шейдерной программы.
    virtual ~ShaderProgram();
};


class CircleProgram: public ShaderProgram{
    GLint _segments;
    GLint _center;
    GLint _radius;
    GLint _color;
    GLuint _vbo;
    GLuint _vao;
public:

    CircleProgram() ;

    CircleProgram(const CircleProgram&) = delete;
    CircleProgram& operator=(const CircleProgram&) = delete;

    void Draw(GLfloat , GLfloat , GLfloat ,const  GLfloat * );

    ~CircleProgram() override ;

};






