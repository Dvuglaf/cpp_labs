#version 430 core

in float dummy;

uniform int segments;
uniform vec2 center;
uniform float radius;

const float PI = 3.14159;

void main() {
    float angle = 2 * PI / segments * gl_VertexID;
    float x = center.x + radius * cos(angle) + dummy;
    float y = center.y + radius * sin(angle) + dummy;
    gl_Position = vec4(x, y, 0, 1);
}