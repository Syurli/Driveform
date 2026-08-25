#pragma once

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct DF_World* DF_WorldHandle;

typedef struct DF_Version {
    uint32_t major;
    uint32_t minor;
    uint32_t patch;
} DF_Version;

DF_Version dfGetVersion(void);
DF_WorldHandle dfCreateWorld(float fixed_step_seconds);
void dfDestroyWorld(DF_WorldHandle world);
void dfWorldSetFixedStep(DF_WorldHandle world, float fixed_step_seconds);
float dfWorldGetFixedStep(DF_WorldHandle world);
uint64_t dfWorldGetStepCount(DF_WorldHandle world);
void dfWorldStep(DF_WorldHandle world, float delta_time_seconds);

#if defined(__cplusplus)
}
#endif
