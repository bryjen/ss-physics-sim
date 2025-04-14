#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "ssps/physics/simulation.h"


const float cor = 0.75f;  // see https://en.wikipedia.org/wiki/Coefficient_of_restitution
const float grav_const = 6.67430e-11f;


static Vec3 gravitational_force = { .x = 0.0f, .y = -9.80665f, .z = 0.0f };



// sums up forces acting on the object, then moves it by an appropriate amount given dt (delta time).
void apply_forces(SSPS_BaseObj*, Vec3*, size_t, float);

// concats/appends two `Vec3` arrays in place
void append_vec3_arr_in_place(Vec3**, size_t*, const Vec3*, size_t);

// assumes that each other body in the simulation has an attractive (gravitational) force on the current object.
// calculates a list of such gravitational forces acting on the current object given the other objects.
void get_grav_forces_from_other_objects(const SSPS_Simulation*, SSPS_BaseObj*, int, Vec3**, size_t*);


void 
SSPS_BaseObj_update(SSPS_BaseObj *const obj, Vec3* acting_forces, size_t acting_forces_count, float dt) {
    apply_forces(obj, acting_forces, acting_forces_count, dt);

    if (obj->pos.y < 0.0f) {
        obj->pos.y = 0.0f;
        obj->vel.y = -obj->vel.y * cor;    
    }
}


void 
SSPS_Sphere_update(SSPS_Sphere *const sphere, Vec3* acting_forces, size_t acting_forces_count, float dt) {
    apply_forces(&(sphere->obj_base), acting_forces, acting_forces_count, dt);

    if (sphere->obj_base.pos.y < 0.0f) {
        sphere->obj_base.pos.y = 0.0f;
        sphere->obj_base.vel.y = -(sphere->obj_base.vel.y) * cor;
    }
}


// assumes that each other body in the simulation has an attractive (gravitational) force on the current object.
// calculates a list of such gravitational forces acting on the current object given the other objects.
void
get_grav_forces_from_other_objects(
        const SSPS_Simulation *const simulation, 
        SSPS_BaseObj* curr_obj, 
        int curr_idx,
        Vec3** out_grav_forces,
        size_t* out_grav_forces_count) {

    int i = 0;

    *out_grav_forces_count = simulation->num_objs - 1;
    Vec3* grav_forces = malloc(*out_grav_forces_count * sizeof(Vec3));
    for (int j = 0; j < simulation->num_objs; j++) {
        if (curr_idx == j) {
            continue;
        }

        SSPS_BaseObj* other_obj = (simulation->objs[j]);
        Vec3 displacement = Vec3_sub(other_obj->pos, curr_obj->pos);
        float distance = Vec3_mag(displacement);
        Vec3 unit_displacement = Vec3_scal_mul(1 / distance, displacement);
        
        float grav_force_scalar = (grav_const * other_obj->mass) / powf(distance, 2.0f);
        Vec3 grav_force = Vec3_scal_mul(grav_force_scalar, unit_displacement);
        grav_forces[i++] = grav_force;
    }

    *out_grav_forces = grav_forces;
}





void
SSPS_Simulation_update(SSPS_Simulation *const simulation, float dt) {
    int current_obj_idx = 0;
    for (SSPS_BaseObj** obj = simulation->objs; obj < simulation->objs + simulation->num_objs; obj++) {
        Vec3* grav_forces = NULL;
        size_t grav_forces_count;
        get_grav_forces_from_other_objects(simulation, *obj, current_obj_idx, &grav_forces, &grav_forces_count);

        // add persistent downward gravity
        // append_vec3_arr_in_place(&grav_forces, &grav_forces_count, &gravitational_force, 1);


        switch ((*obj)->type)
        {
            case OBJ_TYPE_BASE:
                SSPS_BaseObj_update(*obj, grav_forces, grav_forces_count, dt);
                break;
            case OBJ_TYPE_SPHERE:
                SSPS_Sphere* sphere = (SSPS_Sphere*)(*obj);
                SSPS_Sphere_update(sphere, grav_forces, grav_forces_count, dt);
                break;
        }

        current_obj_idx++;
        free(grav_forces);
    }
}


void
apply_forces(SSPS_BaseObj *const obj, Vec3* acting_forces, size_t acting_forces_count, float dt) {
    for (Vec3* force = acting_forces; force < acting_forces + acting_forces_count; force++) {
        Vec3 dv = Vec3_mul(*force, Vec3_init(dt));
        obj->vel = Vec3_add(obj->vel, dv);
    }

    Vec3 dx = Vec3_mul(obj->vel, Vec3_init(dt));
    obj->pos = Vec3_add(obj->pos, dx);
}


void 
append_vec3_arr_in_place(Vec3** to_append, size_t* to_append_size, const Vec3* other, size_t other_size) {
    Vec3* temp = realloc(*to_append, (*to_append_size + other_size) * sizeof(Vec3));
    *to_append = temp;

    memcpy(*to_append + *to_append_size, other, other_size * sizeof(Vec3));
    *to_append_size += other_size;
}