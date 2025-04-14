#ifndef SSPS_VEC3
#define SSPS_VEC3

/**
 * @brief
 */
typedef struct Vec3 {
    float x, y, z;
} Vec3;


Vec3 Vec3_add(Vec3 v1, Vec3 v2);
Vec3 Vec3_mul(Vec3 v1, Vec3 v2);
Vec3 Vec3_init(float val);

#endif