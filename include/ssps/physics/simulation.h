#ifndef SSPS_SIMULATION
#define SSPS_SIMULATION

#include <stdlib.h>
#include "ssps/physics/vec3.h"



/**
 * @brief
 */
typedef enum SSPS_ObjType {
    OBJ_TYPE_BASE,
    OBJ_TYPE_SPHERE,
} SSPS_ObjType;



/**
 * @brief
 */
typedef struct SSPS_BaseObj {
    SSPS_ObjType type;
    Vec3 pos, vel, acc;
    float mass;
} SSPS_BaseObj;

/**
 * @brief
 */
void 
SSPS_BaseObj_update(SSPS_BaseObj *obj, float dt);



/**
 * @brief
 */
typedef struct SSPS_Sphere {
    SSPS_BaseObj obj_base;
    float radius;
} SSPS_Sphere;

/**
 * @brief
 */
void 
SSPS_Sphere_update(SSPS_Sphere *sphere, float dt);



/**
 * @brief
 */
typedef struct SSPS_Simulation {
    SSPS_BaseObj** objs;
    size_t num_objs;
} SSPS_Simulation;

/**
 * @brief
 */
void
SSPS_Simulation_update(SSPS_Simulation *simulation, float dt);


#endif