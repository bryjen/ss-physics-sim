#ifndef SSPS_VEC3
#define SSPS_VEC3

#include <math.h>

/**
 * @brief
 */
typedef struct Vec3 {
    float x, y, z;
} Vec3;


extern inline Vec3
Vec3_add(Vec3 v1, Vec3 v2) {
    return (Vec3){
        .x = v1.x + v2.x,
        .y = v1.y + v2.y,
        .z = v1.z + v2.z
    };
}

extern inline Vec3
Vec3_sub(Vec3 v1, Vec3 v2) {
    return (Vec3){
        .x = v1.x - v2.x,
        .y = v1.y - v2.y,
        .z = v1.z - v2.z
    };
}

extern inline Vec3
Vec3_scal_mul(float scalar, Vec3 v) {
    return (Vec3){
        .x = scalar * v.x,
        .y = scalar * v.y,
        .z = scalar * v.z
    };
}

extern inline Vec3
Vec3_mul(Vec3 v1, Vec3 v2) {
    return (Vec3){
        .x = v1.x * v2.x,
        .y = v1.y * v2.y,
        .z = v1.z * v2.z
    };
}

extern inline Vec3
Vec3_init(float val) {
    return (Vec3){
        .x = val,
        .y = val,
        .z = val
    };
}


extern inline float
Vec3_mag(Vec3 v) {
    return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

#endif