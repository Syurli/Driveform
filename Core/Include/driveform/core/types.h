#pragma once

#include <cstdint>

namespace driveform {

struct Vec3 {
    float x{0.0F};
    float y{0.0F};
    float z{0.0F};
};

struct Quat {
    float x{0.0F};
    float y{0.0F};
    float z{0.0F};
    float w{1.0F};
};

struct Transform {
    Vec3 position{};
    Quat rotation{};
};

using BodyId = std::uint64_t;
using SurfaceId = std::uint32_t;

} // namespace driveform
