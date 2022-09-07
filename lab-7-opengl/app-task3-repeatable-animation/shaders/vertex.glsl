#version 430 core

uniform float t;

in float t0;
in vec2 v;
in vec4 rgba;


out vec4 color;

void main(){
    float x = v.x * (t - t0);
    float y = v.y * (t - t0);
    float size = rgba.r * 4 + rgba.g * 3+ rgba.b *5 + rgba.a;
    gl_PointSize = size;
    gl_Position = vec4(x, y, 0 , 1);
    color = rgba;
}