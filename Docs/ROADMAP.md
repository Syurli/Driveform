# Roadmap

## Phase 0 — Foundation

目标：形成可编译、可测试、可部署的最小工程闭环。

- [x] 仓库结构与 CMake 基线
- [x] C++20 Core target
- [x] C ABI target
- [x] Fixed-Step World 骨架
- [x] Physics Backend 抽象接口
- [x] Web Editor 工程壳
- [x] GitHub Pages 部署工作流
- [x] Native/Web CI
- [ ] Vehicle Runtime / handle registry
- [ ] Error code / logging / allocator policy
- [ ] JSON Schema v0
- [ ] Telemetry buffer v0
- [ ] Emscripten toolchain 与 WASM C API

**Exit Criteria**：Native smoke test 与 Web build 均通过；Pages 可访问；浏览器能调用同一 Core 的 WASM `World::Step`。

## Phase 1 — Reference World & Powertrain

- [ ] Jolt Reference Backend
- [ ] Standalone sandbox
- [ ] Engine torque curve
- [ ] Clutch
- [ ] Gearbox
- [ ] Differential / Final Drive
- [ ] Reaction torque loop
- [ ] Powertrain telemetry

**Exit Criteria**：在无游戏引擎环境中完成发动机启动、负载、挂挡、换挡和输出轴响应的可视化测试。

## Phase 2 — Suspension & Wheel

- [ ] Surface Material v0
- [ ] Batch Ray/Shape Query pipeline
- [ ] Spring / compression & rebound damping
- [ ] Wheel angular state
- [ ] Longitudinal slip
- [ ] Slip angle
- [ ] Steering / brake / rolling resistance
- [ ] `DF-Car-01`
- [ ] `DF-Truck-01`

**Exit Criteria**：完成加速、制动、坡道、Split-μ、转弯半径 Regression。

## Phase 3 — Track Solver

- [ ] Virtual track contacts
- [ ] Track surface velocity
- [ ] Anisotropic friction
- [ ] Left/right drivetrain split
- [ ] Pivot turn
- [ ] Ground→track→powertrain reaction
- [ ] `DF-Track-01`
- [ ] FULL / REDUCED contact profiles

**Exit Criteria**：履带车具备明显的重量、负载、横向阻力和差速转向特征，同时 Contact 成本显著低于实体履带链方案。

## Phase 4 — Unreal 5.8

- [ ] Chaos Backend
- [ ] `UDriveformVehicleComponent`
- [ ] Vehicle asset importer/binding
- [ ] Blueprint control/state API
- [ ] Debug Draw
- [ ] wheel/track visual binding
- [ ] Web/Jolt ↔ UE/Chaos regression comparison

**Exit Criteria**：同一 Driveform 资产可在 Web/Jolt 与 UE5.8/Chaos 中运行，无需重写动力学逻辑。

## Phase 5 — Vehicle Studio v0.1

- [ ] Vehicle Assembly
- [ ] Powertrain graph
- [ ] Curve editor
- [ ] Test Bench scenes
- [ ] Telemetry graph
- [ ] Debug vectors/contact view
- [ ] Import/export `.driveform`
- [ ] Reference profile comparison

## Later

Unity / Godot 正式 SDK、network snapshot/prediction、marine/fixed-wing/rotorcraft、advanced tire/soil、cloud collaboration 均在陆地载具闭环稳定后再进入路线图。
