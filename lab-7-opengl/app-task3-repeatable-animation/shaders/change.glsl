#version 430 core

layout(local_size_x = 1) in;

uniform float t;


struct Point{

    float t0;
    vec2 v;
    vec4 rgba;

};

layout(std140, binding = 0) buffer ssbo{
    Point points[];
};
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
    vec2 pos = point.v * (t - point.t0);

    if(pos.x <= -1 || pos.x >= 1 || pos.y <= -1 || pos.y >= 1){
        pos.x = 0;
        pos.y = 0;
        point.v.x = -1 + 2*xorshift();
        point.v.y = -1 + 2*xorshift();
        point.rgba.x = xorshift();
        point.rgba.y = xorshift();
        point.rgba.z = xorshift();
        point.rgba.a = 1;
        point.t0 = t;
        points[gl_GlobalInvocationID.x] = point;
    }
}