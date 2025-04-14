#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// #include <raylib.h>

#include <windows.h>

#include "ssps/physics/vec3.h"
#include "ssps/physics/simulation.h"

#include "ssps/rendering/raylib_renderer.h"

#define ARENA_IMPLEMENTATION
#include "ssps/common/arena.h"



DWORD WINAPI simulation_thread(LPVOID lp_param);
DWORD WINAPI renderer_thread(LPVOID lp_param);

static SSPS_Simulation* simulation = NULL;
static Arena* simulation_allocator = {0};



int
main (void) {
    SSPS_Sphere sphere_1 = (SSPS_Sphere){
        .obj_base = (SSPS_BaseObj){
            .type = OBJ_TYPE_SPHERE,
            .pos = { .x = 5.0f, .y = 15.0f, .z = 5.0f},
            .vel = Vec3_init(0),
            .acc = Vec3_init(0),
            .mass = 10e10f
        },
        .radius = 1.0f
    };
    SSPS_Sphere* sphere_ptr_1 = &sphere_1;


    SSPS_Sphere sphere_2 = (SSPS_Sphere){
        .obj_base = (SSPS_BaseObj){
            .type = OBJ_TYPE_SPHERE,
            .pos = { .x = -5.0f, .y = 20.0f, .z = -5.0f},
            .vel = Vec3_init(0),
            .acc = Vec3_init(0),
            .mass = 10e10f
        },
        .radius = 1.0f
    };
    SSPS_Sphere* sphere_ptr_2 = &sphere_2;

    SSPS_Sphere sphere_3 = (SSPS_Sphere){
        .obj_base = (SSPS_BaseObj){
            .type = OBJ_TYPE_SPHERE,
            .pos = { .x = 2.0f, .y = 10.0f, .z = -5.0f},
            .vel = Vec3_init(0),
            .acc = Vec3_init(0),
            .mass = 10e10f
        },
        .radius = 1.0f
    };
    SSPS_Sphere* sphere_ptr_3 = &sphere_3;


    const size_t capacity = 5;
    SSPS_BaseObj** objs = malloc(capacity * sizeof(SSPS_BaseObj*));
    objs[0] = (SSPS_BaseObj*)sphere_ptr_1;
    objs[1] = (SSPS_BaseObj*)sphere_ptr_2;
    objs[2] = (SSPS_BaseObj*)sphere_ptr_3;


    SSPS_Simulation simulation = (SSPS_Simulation){
        .objs = objs,
        .num_objs = 3
    };
    SSPS_Simulation* simulation_ptr = &simulation;



    SSPS_RAYLIB_init(simulation_ptr);
    SSPS_RAYLIB_run();


    free(objs);
}



DWORD WINAPI
simulation_thread(LPVOID lp_param) {
    return 0;
}

DWORD WINAPI 
renderer_thread(LPVOID lp_param) {
    return 0;
}