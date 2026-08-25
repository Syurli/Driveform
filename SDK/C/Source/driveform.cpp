#include <driveform/driveform.h>
#include <driveform/core/world.h>

#include <new>

struct DF_World {
    driveform::World impl;

    explicit DF_World(float fixedStep) : impl(fixedStep) {}
};

DF_Version dfGetVersion(void) {
    return DF_Version{0, 1, 0};
}

DF_WorldHandle dfCreateWorld(float fixed_step_seconds) {
    return new (std::nothrow) DF_World(fixed_step_seconds);
}

void dfDestroyWorld(DF_WorldHandle world) {
    delete world;
}

void dfWorldSetFixedStep(DF_WorldHandle world, float fixed_step_seconds) {
    if (world) {
        world->impl.SetFixedStep(fixed_step_seconds);
    }
}

float dfWorldGetFixedStep(DF_WorldHandle world) {
    return world ? world->impl.GetFixedStep() : 0.0F;
}

uint64_t dfWorldGetStepCount(DF_WorldHandle world) {
    return world ? world->impl.GetStepCount() : 0;
}

void dfWorldStep(DF_WorldHandle world, float delta_time_seconds) {
    if (world) {
        world->impl.Step(delta_time_seconds);
    }
}
