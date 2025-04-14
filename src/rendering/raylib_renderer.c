#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "ssps/physics/simulation.h"
#include "ssps/rendering/raylib_renderer.h"

// NOTE:
// As of the writing of this, physics is decoupled from framerate, but simulation backend gets 
// called per-frame rendering (by keeping track of dt)


#define PANIC(msg)                             \
    do {                                       \
        fprintf(stderr, "PANIC: %s\n", msg);   \
        abort();                               \
    } while (0)



static double prev_time = 0.0; 
static double current_time = 0.0;
static double update_draw_time = 0.0;
static double wait_time = 0.0;
static float delta_time = 0.0f;

static float acc_time_counter = 0.0f;

static const int target_fps = 120;


static SSPS_Simulation* simulation = NULL;



static inline Vector2 
to_raylib_vector2(Vec3 v) {
    return (Vector2) { v.x, v.y };
}


static inline Vector3
to_raylib_vector3(Vec3 v) {
    return (Vector3) { v.x, v.y, v.z };
}



void 
SSPS_RAYLIB_draw_shapes(const SSPS_Simulation* const simulation) {
    for (int i = 0; i < simulation->num_objs; i++) {
        SSPS_BaseObj* obj = (simulation->objs[i]);

        switch (obj->type)
        {
            case OBJ_TYPE_BASE:
                // TODO
                break;
            case OBJ_TYPE_SPHERE:
                SSPS_Sphere* sphere = (SSPS_Sphere*)obj;
                Vector3 sphere_pos = to_raylib_vector3(sphere->obj_base.pos);
                DrawSphere(sphere_pos, sphere->radius, RED);
                DrawSphereWires(sphere_pos, sphere->radius, 10, 10, MAROON);
                break;
        }
    }
}

void 
SSPS_RAYLIB_draw_position_text(const SSPS_Simulation* const simulation) {
    for (int i = 0; i < simulation->num_objs; i++) {
        SSPS_BaseObj* obj = (simulation->objs[i]);
        Vec3 pos = obj->pos;
        DrawText(TextFormat("#%d\t: %.2f %.2f %.2f", i, pos.x, pos.y, pos.z), GetScreenWidth() - 500, 70 + (30 * i), 20, LIME); }
}



void
SSPS_RAYLIB_init(SSPS_Simulation* sim) {
    simulation = sim;
    prev_time = GetTime();
}

void 
SSPS_RAYLIB_run() {
    if (!simulation) {
        PANIC("No simulation provided");
    }

    
    SSPS_BaseObj* temp = simulation->objs[0];


    const int screen_width = (int)(1920 * 0.8f);
    const int screen_height = (int)(1080 * 0.8f);

    InitWindow(screen_width, screen_height, "ssps");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 20.0f, 20.0f, 20.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    DisableCursor();



    while (!WindowShouldClose()) {
        // update
        acc_time_counter += delta_time;

        UpdateCamera(&camera, CAMERA_FREE);
        if (IsKeyPressed('Z')) {
            camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        }

        if (delta_time > 0) {
            SSPS_Simulation_update(simulation, delta_time * 4);
        }


        // draw
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
            {
                SSPS_RAYLIB_draw_shapes(simulation);
                DrawGrid(20, 1.0f);
            }
            EndMode3D();


            DrawText(TextFormat("TARGET FPS: %i", target_fps), GetScreenWidth() - 220, 10, 20, LIME);
            if (delta_time != 0) {
                DrawText(TextFormat("CURRENT FPS: %i", (int)(1.0f/delta_time)), GetScreenWidth() - 220, 40, 20, GREEN);
            }

#ifndef NDEBUG
            SSPS_RAYLIB_draw_position_text(simulation);
#endif
        }

        EndDrawing();


        // post processing stuff

        current_time = GetTime();
        update_draw_time = current_time - prev_time;
        
        if (target_fps > 0)          // We want a fixed frame rate
        {
            wait_time = (1.0f/(float)target_fps) - update_draw_time;
            if (wait_time > 0.0) 
            {
                WaitTime((float)wait_time);
                current_time = GetTime();
                delta_time = (float)(current_time - prev_time);

#ifndef NDEBUG
                printf("dt: %.3fs\n", delta_time);
#endif
            }
        }
        else delta_time = (float)update_draw_time;    // Framerate could be variable

        prev_time = current_time;
    }

    CloseWindow();
}