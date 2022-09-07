#version 430 core

uniform float t;

in  vec2 v;
in vec3 rgb;

out vec3 color;

void main(){
    float x = v.x * t;
    float y = v.y * t;
    gl_Position = vec4(x, y, 0, 1);
    gl_PointSize=4;
    color = rgb;
}
