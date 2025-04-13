#ifndef SSPS_SIMULATION
#define SSPS_SIMULATION


typedef Vec3 Vec3;


/**
 * @brief
 */
typedef struct {
    Vec3 pos, vel, acc;
    float mass;
} ObjBase;


/**
 * @brief
 */
typedef struct {
    ObjBase obj_base;
    float radius;
} SSPSCircle;



/**
 * @brief
 */
void 
SimObj_init(ObjBase *obj);


/**
 * @brief
 */
void 
SimObj_update(ObjBase *obj, float dt);

#endif