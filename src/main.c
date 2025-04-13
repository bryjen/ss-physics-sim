#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>
#include "ssps/physics/vec3.h"
#include "ssps/physics/simulation.h"


/*
int main(void) {
    ObjBase obj = (ObjBase){
        .pos = Vec3_init(0),
        .vel = Vec3_init(0),
        .acc = Vec3_init(0),
        .mass = 10,
    };
    obj.pos.y = 20;

    const size_t target_fps = 60;
    const size_t runtime = 10;
    for (int i = 0; i < target_fps * runtime; i++) {
        Sleep(1000 / target_fps);

        const float dt = 1.0f / target_fps;
        SimObj_update(&obj, dt);

        printf("%d - %.2f\n", i, obj.pos.y);
    }
    return 0;
}
*/

Vector2 
to_raylib_vector2(Vec3 v) {
    return (Vector2) { v.x, v.y };
}

Vector3
to_raylib_vector3(Vec3 v) {
    return (Vector3) { v.x, v.y, v.z };
}


int
main (void) {
    const int screen_width = 960;
    const int screen_height = 540;

    InitWindow(screen_width, screen_height, "ssps");


    // init objects
    ObjBase obj = (ObjBase){
        .pos = { .x = (float)screen_width / 2, .y = (float)screen_height * 0.75f, .z = 0.0f},
        .vel = Vec3_init(0),
        .acc = Vec3_init(0),
        .mass = 10,
    };


    // init time/frame controls
    double prev_time = GetTime();
    double current_time = 0.0;
    double update_draw_time = 0.0;
    double wait_time = 0.0;
    float delta_time = 0.0f;

    float acc_time_counter = 0.0f;

    const int target_fps = 60;

    // keep track of collisions
    bool is_falling = true;
    float last_collision = -1.0f;
    int collisions_acc = 0;

    while (!WindowShouldClose()) {
        // update
        acc_time_counter += delta_time;


        if (delta_time > 0) {
            SimObj_update(&obj, delta_time * 5);
        }
        Vector2 ball_pos = to_raylib_vector2(obj.pos);

        if (is_falling && obj.vel.y > 0) {
            is_falling = false;
            collisions_acc++;
            last_collision = acc_time_counter;
        }

        if (!is_falling && obj.vel.y < 0) {
            is_falling = true;
        }



        // draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawCircleV(ball_pos, 10.0f, BLUE);
            DrawText(TextFormat("TARGET FPS: %i", target_fps), GetScreenWidth() - 220, 10, 20, LIME);
            if (delta_time != 0) {
                DrawText(TextFormat("CURRENT FPS: %i", (int)(1.0f/delta_time)), GetScreenWidth() - 220, 40, 20, GREEN);
            }

            if (collisions_acc > 0) {
                DrawText(TextFormat("COLLISION #%d: %f", collisions_acc, last_collision), GetScreenWidth() - 220, 70, 20, BLACK);
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
            }
        }
        else delta_time = (float)update_draw_time;    // Framerate could be variable

        prev_time = current_time;
    }

    CloseWindow();
    return 0;
}