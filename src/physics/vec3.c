#include "ssps/physics/vec3.h"

Vec3
Vec3_add(Vec3 v1, Vec3 v2) {
    return (Vec3){
        .x = v1.x + v2.x,
        .y = v1.y + v2.y,
        .z = v1.z + v2.z
    };
}

Vec3
Vec3_mul(Vec3 v1, Vec3 v2) {
    return (Vec3){
        .x = v1.x * v2.x,
        .y = v1.y * v2.y,
        .z = v1.z * v2.z
    };
}

Vec3
Vec3_init(float val) {
    return (Vec3){
        .x = val,
        .y = val,
        .z = val
    };
}