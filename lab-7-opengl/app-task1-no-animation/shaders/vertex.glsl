#version 430 core

in float x;
in float y;
in vec3 rgb;

out vec3 color;

void main(){
    gl_Position = vec4(x, y, 0, 1);
    gl_PointSize = 2;
    color = rgb;
}
