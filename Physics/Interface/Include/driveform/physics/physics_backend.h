#pragma once

#include <driveform/core/types.h>

#include <span>

namespace driveform::physics {

struct RaycastRequest {
    Vec3 origin{};
    Vec3 direction{0.0F, 0.0F, -1.0F};
    float distance{0.0F};
};

struct RaycastHit {
    bool hit{false};
    BodyId body{0};
    SurfaceId surface{0};
    Vec3 position{};
    Vec3 normal{0.0F, 0.0F, 1.0F};
    float distance{0.0F};
};

class IPhysicsBackend {
public:
    virtual ~IPhysicsBackend() = default;

    virtual void BatchRaycast(std::span<const RaycastRequest> requests,
                              std::span<RaycastHit> hits) = 0;

    [[nodiscard]] virtual Transform GetTransform(BodyId body) const = 0;
    [[nodiscard]] virtual Vec3 GetLinearVelocity(BodyId body) const = 0;
    [[nodiscard]] virtual Vec3 GetAngularVelocity(BodyId body) const = 0;
    [[nodiscard]] virtual Vec3 GetVelocityAtPoint(BodyId body, Vec3 worldPoint) const = 0;

    virtual void ApplyForce(BodyId body, Vec3 force) = 0;
    virtual void ApplyForceAtPoint(BodyId body, Vec3 force, Vec3 worldPoint) = 0;
    virtual void ApplyTorque(BodyId body, Vec3 torque) = 0;
};

} // namespace driveform::physics
