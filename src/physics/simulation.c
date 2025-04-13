#include "ssps/physics/vec3.h"
#include "ssps/physics/simulation.h"



void 
SimObj_init(ObjBase *const obj) {
}

void 
SimObj_update(ObjBase *const obj, float dt) {
    const float g = -9.8f;

    obj->vel.y += g * dt;

    const Vec3 dx = Vec3_mul(obj->vel, Vec3_init(dt));
    obj->pos = Vec3_add(obj->pos, dx);

    if (obj->pos.y < 0.0f) {
        obj->pos.y = 0.0f;
        obj->vel.y = -obj->vel.y * 0.8f;  // restitution
    }
}