# Driveform TDD v0.1

## 1. 定位

Driveform 是独立于具体游戏引擎的载具动力学、调校与验证框架。核心产品由四部分组成：

1. **Driveform Core**：C++20 动力学核心；
2. **Driveform Physics Bridge**：宿主物理世界抽象；
3. **Driveform Editor**：Web 参数、曲线、结构、试车与 Telemetry 工具；
4. **Driveform SDK**：稳定 C ABI 与各引擎原生 Wrapper。

首版聚焦 **轮式 + 履带式**，后续再扩展两轮、船舶、固定翼和旋翼载具。

## 2. 核心原则

- Core 中不得出现 Unreal、Chaos、Unity、Godot、Jolt、Three.js 类型或头文件。
- Driveform 负责发动机、传动、悬挂、轮胎/履带、接触模型和力生成；Physics Backend 负责刚体、碰撞查询和施力。
- 同一份 Core 同时编译 Native 与 WASM，避免 Web Preview 与 Runtime 形成两套模拟逻辑。
- Public SDK 使用 C ABI：opaque handle、POD struct、版本字段；禁止跨 ABI 传 STL、异常、模板、宿主引擎类型。
- Runtime 固定步长，默认 120 Hz；渲染帧率不得直接改变动力学结果。
- `Step()` 热路径原则上 0 heap allocation，物理查询尽量 batch。
- Simulation LOD 从第一版进入架构，而不是后补。

## 3. 技术栈

| 层 | 技术 |
|---|---|
| Core | C++20 |
| ABI | C |
| Build | CMake |
| Web | React + TypeScript + Vite |
| 3D | Three.js，后续 WebGPU 优先 |
| WASM | Emscripten |
| Reference Physics | Jolt |
| Unreal | C++ + Chaos Adapter |
| Unity | C# + Native Plugin |
| Godot | C++ GDExtension |
| Authoring | JSON + JSON Schema |
| Runtime Asset | 后续 `.driveformbin` |

## 4. 总体架构

```text
Web Editor
  ↓ TypeScript Wrapper
Driveform WASM
  ↓
C ABI
  ↓
Driveform Core
  ├─ Control
  ├─ Powertrain
  ├─ Suspension
  ├─ Contact / Surface
  ├─ Wheel Solver
  ├─ Track Solver
  ├─ Telemetry
  └─ Fixed Step Runtime
        ↓
IPhysicsBackend
  ├─ Jolt Reference Backend
  ├─ Chaos Backend
  ├─ Unity Backend
  └─ Godot Backend
```

## 5. 动力链

首版动力链：

```text
Engine
  ↓
Clutch / Torque Converter interface
  ↓
Gearbox
  ↓
Differential / Steering Transmission
  ↓
Final Drive
  ↓
Wheel / Sprocket
  ↓
Tire / Track
  ↓
Ground
```

必须保留负载反向反馈：

```text
Ground Force
  ↓
Wheel/Track Reaction
  ↓
Final Drive
  ↓
Differential
  ↓
Gearbox
  ↓
Engine Load
```

这保证上坡、陷车、急转、高挡低速等工况会真实影响发动机转速和动力响应。

## 6. Engine / Gearbox / Differential

Engine 首版至少支持 IdleRPM、MaxRPM、RevLimitRPM、RotationalInertia、EngineBrake、ThrottleResponse 与 TorqueCurve。

Gearbox 支持 Manual / Automatic / SemiAutomatic；换挡策略与机械 Gearbox 分离。

Differential 首版支持 Open、Locked、Simple LSD，并为履带车辆保留 Controlled Differential 与左右独立驱动拓扑。

## 7. Suspension 与 Contact

Wheel / Track 共用 Suspension 与 Surface 系统。Suspension Probe 至少包含 MountPosition、Direction、RestLength、MaxCompression、MaxDroop、SpringRate、Compression/Rebound Damping。

第一版不使用完整实体轮胎/实体履带参与高成本刚体约束。优先：

- Wheel：Sphere/Cylinder ShapeCast，必要时 Raycast Fast Mode；
- Track：每侧多 Contact Probe；
- Visual Track 与 Physics Track 完全解耦。

## 8. Track Solver

履带系统采用虚拟 Moving Friction Surface 思路。每个接触点至少计算：

- NormalLoad
- Track Surface Velocity
- Ground Velocity
- Longitudinal Slip
- Lateral Slip
- Longitudinal/Lateral Friction
- Rolling Resistance
- Reaction Force / Reaction Torque

履带主动轮线速度：`Vtrack = ωsprocket × Rsprocket`。

摩擦必须支持各向异性，至少独立配置纵向与横向静/动摩擦。首版不模拟真实履带板链约束；视觉层可使用 Spline、Skin、Shader 或实例化履带板。

## 9. Wheel Solver

首版至少支持 WheelAngularVelocity、WheelRadius、SteeringAngle、NormalLoad、LongitudinalSlip、SlipAngle、BrakeTorque、DriveTorque、RollingResistance。

第一阶段采用可调 Slip Curve 模型，不直接追求完整 Pacejka；Tire Model 使用可替换接口，为后续 Brush / Pacejka / Custom Solver 留空间。

## 10. Surface

Driveform 定义自己的 Surface / Contact Material，不直接依赖宿主 Physical Material。最终响应由车辆接触材质与地面材质组合决定，例如 Rubber+Asphalt、SteelTrack+Dirt。

后续可扩展 Grip 与 Passability/Resistance、Sinkage、Soil Shear、Snow/Mud 等模型。

## 11. Physics Backend

`IPhysicsBackend` 首版提供：

- BatchRaycast / 后续 BatchShapeCast
- GetTransform
- GetLinearVelocity
- GetAngularVelocity
- GetVelocityAtPoint
- GetSurface
- ApplyForce
- ApplyForceAtPoint
- ApplyTorque

Jolt 仅作为官方 Reference Backend，用于 Web Editor、Standalone、CI、Benchmark 与 Regression；UE Runtime 默认仍与 Chaos 世界交互，避免双物理世界同步问题。

## 12. Simulation Tick

默认 120 Hz Fixed Step：

```text
Input Sampling
→ Controller
→ Powertrain Pre-Solve
→ Build Contact Queries
→ Batch Physics Query
→ Suspension Solve
→ Wheel / Track Solve
→ Powertrain Reaction Solve
→ Force Accumulation
→ Apply Forces
→ Runtime State
→ Telemetry
```

后续允许不同子系统使用多频率更新，但必须保证固定时钟语义稳定。

## 13. Simulation LOD

- **FULL**：完整动力链、Suspension、Per-contact Slip、Reaction；玩家与近距离 Hero Vehicle。
- **REDUCED**：减少 Probe、降低接触求解频率、简化瞬态；普通 AI。
- **PROXY**：性能包线、目标速度/加速度/转向半径；远距离车辆。
- **SLEEP**：停止模拟。

LOD 的本质是替换不同精度模型，不只是降低 Tick Rate。

## 14. Web Editor

GitHub Pages 直接作为正式编辑器入口：`https://syurli.github.io/Driveform/`。

首版界面结构：System Tree + 3D View + Inspector + Curve/Telemetry。后续逐步实现：

- Vehicle Assembly
- Powertrain Graph
- Curve Editor
- Test Bench
- Surface / Slope / Split-μ 场景
- Telemetry Graph
- Debug Draw
- `.driveform` 导入导出

## 15. Unreal Bridge

UE5.8 是首个正式宿主集成。UE 层只负责 Chaos Adapter、Actor/Mesh Binding、Input、Visual Track/Wheel、Audio/VFX、Blueprint API、Debug Draw 与后续 Replication Bridge。

Core 不知道 UObject、FVector、FTransform、Chaos 类型。

## 16. Reference Vehicles

首期固定三台：

- `DF-Car-01`：四轮汽车，验证 Tire / Suspension / Differential；
- `DF-Truck-01`：6×6/8×8，验证多轴、重载与动力分配；
- `DF-Track-01`：履带车辆，验证 Track Surface、差速转向、Pivot Turn、Reaction Torque。

## 17. 测试与性能

测试分 Unit / Dynamics / Vehicle Regression / Performance。

标准 Regression 至少覆盖：Acceleration、Braking、Slope、Turning、Split-μ、Bump、Idle、GearShift、PivotTurn。

阶段性能目标：单台 FULL solver ≤ 0.10 ms；16 台 FULL ≤ 1 ms；64 台 Mixed LOD ≤ 2 ms（不计宿主物理引擎自身刚体求解）。这些是优化目标，不是首个原型的硬门槛。

## 18. 初版不做

完整实体履带链、软体轮胎、轮胎热力学、气缸燃烧、燃油系统、结构破坏、泥雪体积塑性、船舶、飞机、直升机、正式 Unity/Godot SDK、完整网络预测均不进入 v0.1。

## 19. 参考项目原则

MMT / UE4_Tracked_Vehicles 只作为行为与架构研究参考：机械组件组合、Physics Substep、Moving Friction Surface、各向异性摩擦、Surface Response 与 Reaction Force 等思想值得继承，但 Driveform 不直接移植其 UE4 实现，也不在许可证未人工确认前复制源码。
