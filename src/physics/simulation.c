#include "ssps/physics/simulation.h"


const float g = -9.8f;
const float cor = 0.75f;  // see https://en.wikipedia.org/wiki/Coefficient_of_restitution


void 
SSPS_BaseObj_update(SSPS_BaseObj *const obj, float dt) {
    obj->vel.y += g * dt;

    const Vec3 dx = Vec3_mul(obj->vel, Vec3_init(dt));
    obj->pos = Vec3_add(obj->pos, dx);

    if (obj->pos.y < 0.0f) {
        obj->pos.y = 0.0f;
        obj->vel.y = -obj->vel.y * cor;    
    }
}


void 
SSPS_Sphere_update(SSPS_Sphere *const sphere, float dt) {
    sphere->obj_base.vel.y += g * dt;

    float y_dx = sphere->obj_base.vel.y * dt;
    sphere->obj_base.pos.y += y_dx;

    if (sphere->obj_base.pos.y < 0.0f) {
        sphere->obj_base.pos.y = 0.0f;
        sphere->obj_base.vel.y = -(sphere->obj_base.vel.y) * cor;
    }
}


/**
 * @brief
 */
void
SSPS_Simulation_update(SSPS_Simulation *const simulation, float dt) {
    for (int i = 0; i < simulation->num_objs; i++) {
        SSPS_BaseObj* obj = (simulation->objs[i]);

        switch (obj->type)
        {
            case OBJ_TYPE_BASE:
                SSPS_BaseObj_update(obj, dt);
                break;
            case OBJ_TYPE_SPHERE:
                SSPS_Sphere* sphere = (SSPS_Sphere*)obj;
                SSPS_Sphere_update(sphere, dt);
                break;
        }
    }
}