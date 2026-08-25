# Jolt Reference Backend

This directory will contain the official standalone/reference physics backend.

Jolt is intentionally **not** a dependency of `Core/`. Its role is to provide a reproducible world for:

- Web/Standalone simulation
- CI regression tests
- benchmark scenes
- reference vehicle tuning

Initial implementation task: map `IPhysicsBackend` batch queries/body state/force APIs to Jolt without leaking Jolt types across the interface.
