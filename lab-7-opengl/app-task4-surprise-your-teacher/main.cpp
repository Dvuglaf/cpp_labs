#include <iostream>
#include <stdexcept>
#include <core.h>

using namespace std;

bool press = false;
bool x_hod = true;

const auto STRIDE = 2 * sizeof(GLfloat);

char matrix [3][3] = {
        {'-', '-', '-'},
        {'-', '-', '-'},
        {'-', '-', '-'}
};

size_t GetCountSteps() noexcept{
    size_t return_value = 0;
    for(auto & i : matrix)
        for(char j : i) {
            if(j != '-')
                ++return_value;
        }
    return return_value;
}

size_t GetCountO() noexcept{
    size_t return_value = 0;
    for(auto & i : matrix)
        for(char j : i) {
            if(j == 'o')
                ++return_value;
        }
    return return_value;
}
size_t GetCountX() noexcept{
    return GetCountSteps() - GetCountO();
}

//return: 'x' - Win X;
//        'o' - Win O;
//        '-' - the game is not over yet OR draw
char WinOrNot() noexcept{
    if (matrix[0][0] == matrix[0][1] && matrix[0][1] == matrix[0][2] && matrix[0][0] != '-'){
        cout << "FIRST row, Horizontal win - " << (matrix[0][0] == 'x' ? 'X' : 'O');
        return matrix[0][0];
    }
    else if(matrix[1][0] == matrix[1][1] && matrix[1][1] == matrix[1][2] && matrix[1][0] != '-'){
        cout << "SECOND row, Horizontal win - " << (matrix[1][0] == 'x' ? 'X' : 'O');
        return matrix[1][0];
    }
    else if(matrix[2][0] == matrix[2][1] && matrix[2][1] == matrix[2][2] && matrix[2][0] != '-'){
        cout << "THIRD row, Horizontal win - " << (matrix[2][0] == 'x' ? 'X' : 'O');
        return matrix[2][0];
    }
    else if(matrix[0][0] == matrix[1][0] && matrix[1][0] == matrix[2][0] && matrix[0][0] != '-'){
        cout << "FIRST column, Vertical win - " << (matrix[0][0] == 'x' ? 'X' : 'O');
        return matrix[0][0];
    }
    else if(matrix[0][1] == matrix[1][1] && matrix[1][1] == matrix[2][1] && matrix[0][1] != '-'){
        cout << "SECOND column, Vertical win - " << (matrix[0][1] == 'x' ? 'X' : 'O');
        return matrix[0][1];
    }
    else if(matrix[0][2] == matrix[1][2] && matrix[1][2] == matrix[2][2] && matrix[0][2] != '-'){
        cout << "THIRD column, Vertical win - " << (matrix[0][2] == 'x' ? 'X' : 'O');
        return matrix[0][2];
    }
    else if(matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2] && matrix[0][0] != '-'){
        cout << "MAIN diagonal win - " << (matrix[0][0] == 'x' ? 'X' : 'O');
        return matrix[0][0];
    }
    else if(matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0] && matrix[0][2] != '-'){
        cout << "COUNTER diagonal win - " << (matrix[0][2] == 'x' ? 'X' : 'O');
        return matrix[0][2];
    }
    else
        return '-';
}



void ErrorCallback(const int code,const char* const error){
    throw runtime_error(error);
}

//tracks cursor coordinates in [-1; 1]
double X, Y;

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) noexcept {
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        press = true;
    }
}

//calculating coordinates of figure's center
//return true if place is clear
bool MouseButtonIsPressed(char symbol, GLfloat &figure_center_x, GLfloat &figure_center_y) noexcept{

    figure_center_x = 0;
    figure_center_y = 0;

    if (X > 0.333) {
        if (Y > 0.333) {
            if(matrix[0][2] == '-')
                matrix[0][2] = symbol;
            else
                return false;
            figure_center_y = 0.667;
        }
        else if(Y < -0.333){
            if(matrix[2][2] == '-')
                matrix[2][2] = symbol;
            else
                return false;
            figure_center_y = -0.667;
        }
        else{
            if(matrix[1][2] == '-')
                matrix[1][2] = symbol;
            else
                return false;
        }
        figure_center_x = 0.667;

    }
    else if (X < -0.333) {
        if (Y > 0.333) {
            if(matrix[0][0] == '-')
                matrix[0][0] = symbol;
            else
                return false;
            figure_center_y = 0.667;
        }
        else if(Y < -0.333){
            if(matrix[2][0] == '-')
                matrix[2][0] = symbol;
            else
                return false;
            figure_center_y = -0.667;
        }
        else{
            if(matrix[1][0] == '-')
                matrix[1][0] = symbol;
            else
                return false;
        }
        figure_center_x = -0.667;
    }
    else{
        if (Y > 0.333) {
            if(matrix[0][1] == '-')
                matrix[0][1] = symbol;
            else
                return false;
            figure_center_y = 0.667;

        }
        else if(Y < -0.333){
            if(matrix[2][1] == '-')
                matrix[2][1] = symbol;
            else
                return false;
            figure_center_y = -0.667;

        }
        else{
            if(matrix[1][1] == '-')
                matrix[1][1] = symbol;
            else
                return false;;
        }

    }
    return true;
}


void CursorPositionCallback(GLFWwindow* const  window, double xpos, double ypos) noexcept{
    glfwGetCursorPos(window, &X, &Y);
    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(window, &width, &height);

    //cast from range [0; wight/height] to [-1; 1]
    X -= width / 2;
    X = 2 * X / width;
    Y -= height / 2;
    Y = - 2* Y / height;
}



int main() {
    glfwSetErrorCallback(ErrorCallback);
    try {
        if (glfwInit() == GLFW_FALSE)
            throw runtime_error("Failed to initialize GLFW!");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_SAMPLES, 4);

        GLFWwindow *const window = glfwCreateWindow(640, 640, "tic_tac_toe", nullptr, nullptr);
        if (window == nullptr)
            throw runtime_error("Failed to create window!");
        glfwMakeContextCurrent(window);
        glfwSetCursorPosCallback(window, CursorPositionCallback);
        glfwSetMouseButtonCallback(window, MouseButtonCallback);
        {
            auto error = glewInit();
            if (error != GLEW_OK) {
                auto message = reinterpret_cast<const char *>(glewGetErrorString(error));
                throw runtime_error(string("Failed to initialize GLEW:") + message);
            }
        }
        {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        ShaderProgram render_program(
                {
                        {"shaders/vertex.glsl",   GL_VERTEX_SHADER},
                        {"shaders/fragment.glsl", GL_FRAGMENT_SHADER}
                });
        CircleProgram circle_program;
        //first 16 numbers is a board coordinates
        //next is a vertexes coordinates for drawing X
        GLfloat data [56] = {-1, 0.333, 1, 0.333, -1, -0.333, 1, -0.333, -0.333, 1, -0.333, -1, 0.333, 1, 0.333, -1};
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
            const auto x_location = glGetAttribLocation(render_program.id, "x");
            const auto y_location = glGetAttribLocation(render_program.id, "y");
            if (x_location == -1 || y_location == -1 ) {
                throw runtime_error("Failed to locate variable(s)!");
            }
            glVertexAttribPointer(x_location, 1, GL_FLOAT, GL_FALSE, STRIDE, nullptr);
            glVertexAttribPointer(y_location, 1, GL_FLOAT, GL_FALSE, STRIDE,
                                  reinterpret_cast<void *>(sizeof(GLfloat) * 1));
            glEnableVertexAttribArray(x_location);
            glEnableVertexAttribArray(y_location);
        }
        const GLfloat circle_color[] = {0, 0, 0, 1};

        glClearColor(1, 1, 1, 1);

        //save circle centers
        float o_centers[8] = {} ;


        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            if(WinOrNot() != '-'){
                glfwSetWindowShouldClose(window, GL_TRUE);
            }
            else if(GetCountSteps() == 9){
                std::cout << "Draw";
                glfwSetWindowShouldClose(window, GL_TRUE);
            }

            glUseProgram(render_program.id);
            glBindVertexArray(vao);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            if(press && x_hod){
                const auto x_count = GetCountX();
                GLfloat x_center;
                GLfloat y_center;
                if (MouseButtonIsPressed('x',x_center, y_center)) {
                    data[16 + 8 * x_count] = x_center - 0.1;
                    data[17 + 8 * x_count] = y_center - 0.1;
                    data[18 + 8 * x_count] = x_center + 0.1;
                    data[19 + 8 * x_count] = y_center + 0.1;
                    data[20 + 8 * x_count] = x_center - 0.1;
                    data[21 + 8 * x_count] = y_center + 0.1;
                    data[22 + 8 * x_count] = x_center + 0.1;
                    data[23 + 8 * x_count] = y_center - 0.1;
                    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
                    x_hod = false;
                }
                else
                   std::cout << "Square if already taken" << endl;
                press = false;

            }
            glDrawArrays(GL_LINES,0,8 + 4 * GetCountX());

            glUseProgram(circle_program.id);

            const auto o_count = GetCountO();
            for(size_t i = 0; i < o_count; i++){
                circle_program.Draw(o_centers[i], o_centers[i+4] , 0.1, circle_color);
            }
            glUseProgram(0);

            glUseProgram(render_program.id);

            if(press && !x_hod){
                if (MouseButtonIsPressed('o', o_centers[o_count], o_centers[4 + o_count]))
                    x_hod = true;
                else
                    std::cout << "Square if already taken" << endl;
                press = false;
            }
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

    }
    catch (const exception& e)
    {
        glfwTerminate();
        cout << e.what() << endl;
        return EXIT_FAILURE;
    }
}

