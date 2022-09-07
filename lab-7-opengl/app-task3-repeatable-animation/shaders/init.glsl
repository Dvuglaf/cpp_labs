#version 430 core

layout(local_size_x = 1) in;

uniform float t;
struct Point {
    float t0;
    vec2 v;
    vec4 rgba;

};
layout(std140, binding = 0) buffer ssbo {
    Point points[];
};

// "Перемешивает" два значения в одно
uint xxhash(uint x, uint y) {
    x = x * 3266489917 + 374761393;
    x = (x << 17) | (x >> 15);
    x += y * 3266489917;
    x *= 668265263;
    x ^= x >> 15;
    x *= 2246822519;
    x ^= x >> 13;
    x *= 3266489917;
    x ^= x >> 16;
    return x;
}

// Внутреннее состояние xorshift
uint xorshiftState = xxhash(floatBitsToUint(t), gl_GlobalInvocationID.x);

// Xorshift - возвращает псевдослучайное значение в диапазоне [0, 1]
float xorshift() {
    uint x = xorshiftState;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    xorshiftState = x;

    // Приведение к диапазону [0, 1]
    uint m = 0x00ffffff;
    return (x & m) * (1.0f / 0x1000000);
}


void main() {
    Point point = points[gl_GlobalInvocationID.x];

    point.t0 = t;
    point.v.x = -1 + xorshift() * 2;
    point.v.y = -1 + xorshift() * 2;
    point.rgba.r = xorshift();
    point.rgba.g = xorshift();
    point.rgba.b = xorshift();
    point.rgba.a = 1;

    points[gl_GlobalInvocationID.x] = point;
}
