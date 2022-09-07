#version 430 core

in float x;
in float y;

void main() {
    gl_Position = vec4(x, y, 0, 1);
}