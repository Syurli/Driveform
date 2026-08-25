# Development Guide

## Prerequisites

Native foundation:

- CMake 3.25+
- C++20 compiler (MSVC 2022 / Clang / GCC)

Web Editor:

- Node.js 22+
- npm

WASM/Jolt/UE dependencies are intentionally not required for Phase 0 native smoke tests.

## Native build

```bash
cmake -S . -B build -DDRIVEFORM_BUILD_TESTS=ON
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

## Web Editor

```bash
cd Web/Editor
npm install
npm run dev
```

Production check:

```bash
npm run build
```

`vite.config.ts` uses `/Driveform/` as its base because the production editor is hosted at the repository GitHub Pages path.

## Code rules

### Core

- C++20 only.
- Do not include Unreal/Chaos/Jolt/Unity/Godot/Three.js headers.
- Prefer value types, spans and explicit ownership.
- No heap allocation in simulation hot paths unless profiled and justified.
- No hidden worker threads.
- New physics queries should have a batch-friendly path.

### ABI

- C ABI is the compatibility contract.
- No STL or engine-specific types across ABI.
- No exceptions across ABI.
- Avoid transferring allocation ownership without an explicit API.
- External structs that may grow must eventually include `struct_size` and `version`.

### Web

- The Web UI is a real authoring product, not a duplicate simulation implementation.
- Physics/dynamics calculations that affect runtime behavior belong in Core/WASM.
- TypeScript should focus on editing, visualization, orchestration and persistence.

## Branch / change policy

`main` should remain buildable. Prefer small feature branches/PRs once active development starts. Changes that alter schema, public C ABI or physics behavior should update the corresponding Docs and regression expectations in the same change.

## Third-party reference policy

External projects such as MMT / UE4_Tracked_Vehicles may be studied for behavior and architecture. Do not copy source into Driveform unless its license has been explicitly reviewed and the dependency is intentionally approved. The preferred approach for the dynamics core is independent reimplementation from documented behavior, equations and tests.

## Pages deployment

`.github/workflows/pages.yml` builds `Web/Editor` and deploys `dist/` using GitHub Pages Actions. Repository Settings → Pages should use **GitHub Actions** as the source if GitHub does not enable it automatically on the first deployment.
