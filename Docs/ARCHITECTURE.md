# Architecture

## Dependency rule

Driveform follows a strict inward dependency rule:

```text
Web / Integrations / Physics Backends
              ↓
             SDK
              ↓
            Core
```

`Core/` must never include headers from Physics backend implementations, Web, Unreal, Unity or Godot.

## Runtime layers

### Core
Owns deterministic-ish fixed-step vehicle state and algorithms:

- runtime / clock
- vehicle schema/runtime state
- control
- powertrain
- suspension
- wheel / track solvers
- contact/surface model
- force accumulation
- telemetry

### SDK/C
Stable process/library boundary. Public API rules:

- opaque handles
- POD structs
- explicit size/version fields when structs become externally extensible
- no STL, exceptions, RTTI contracts or host-engine types across ABI
- caller/callee allocation ownership must be explicit

### Physics Interface
Defines the minimum world services required by Driveform. Query submission should favor batches to avoid N wheel probes causing N engine/API boundary crossings.

### Physics Backends
Concrete adapters such as Jolt and Chaos. They translate host-world state into Driveform-neutral types and apply generated forces back to the host world.

### Integrations
Engine-facing usability layer: assets, components, inspectors, visual binding, input, debug draw, audio/VFX hooks and networking bridge.

### Web
The browser is a first-class authoring target. `Web/Editor` is the actual GitHub Pages product entry; `Web/WASM` will contain the native-to-WASM bridge and build glue.

## Simulation data flow

```text
Input
  → Control
  → Powertrain
  → Contact Query Build
  → Physics Backend Batch Query
  → Suspension
  → Wheel / Track Solver
  → Reaction Torque
  → Force Accumulator
  → Physics Backend Apply
  → Runtime State / Telemetry
```

## Asset direction

Authoring starts as human-readable JSON + JSON Schema. Runtime may later compile this to `.driveformbin`. Engine-specific assets should reference or import the common Driveform definition instead of becoming the source of truth.

## Threading

Core should not assume a specific engine job system. Initial code is single-thread safe-by-design at the world level; later batching APIs should allow host schedulers to parallelize independent vehicles. Core should avoid creating hidden background threads.

## Visual/physics separation

A physical track is a virtual contact model. Track meshes, spline links, skeletal deformation and UV animation are render concerns. The runtime only exposes state such as left/right track distance, wheel compression and sprocket angle.
