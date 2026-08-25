#pragma once

#include <cstdint>

namespace driveform {

class World {
public:
    explicit World(float fixedStepSeconds = 1.0F / 120.0F) noexcept;

    void SetFixedStep(float seconds) noexcept;
    [[nodiscard]] float GetFixedStep() const noexcept;
    [[nodiscard]] std::uint64_t GetStepCount() const noexcept;

    void Step(float deltaTime) noexcept;

private:
    float fixedStepSeconds_;
    float accumulatorSeconds_{0.0F};
    std::uint64_t stepCount_{0};
};

} // namespace driveform
