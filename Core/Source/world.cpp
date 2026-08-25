#include <driveform/core/world.h>

#include <algorithm>

namespace driveform {

World::World(float fixedStepSeconds) noexcept
    : fixedStepSeconds_(std::max(fixedStepSeconds, 0.0001F)) {}

void World::SetFixedStep(float seconds) noexcept {
    fixedStepSeconds_ = std::max(seconds, 0.0001F);
}

float World::GetFixedStep() const noexcept {
    return fixedStepSeconds_;
}

std::uint64_t World::GetStepCount() const noexcept {
    return stepCount_;
}

void World::Step(float deltaTime) noexcept {
    accumulatorSeconds_ += std::max(deltaTime, 0.0F);

    while (accumulatorSeconds_ >= fixedStepSeconds_) {
        // Vehicle solve pipeline will be inserted here in Phase 0/1.
        accumulatorSeconds_ -= fixedStepSeconds_;
        ++stepCount_;
    }
}

} // namespace driveform
