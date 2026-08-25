# 驭形 Driveform

**Driveform — Modular Vehicle Dynamics Framework**

驭形（Driveform）是一套独立于具体游戏引擎的载具动力学、调校与验证框架。项目目标不是再实现一个只服务于 Unreal Engine 的 Vehicle Plugin，而是建立：

- 独立 **C++20 Driveform Core**；
- 稳定的 **C ABI SDK**；
- 可替换的 **Physics Backend**；
- 以 GitHub Pages 为正式入口的 **Web Editor**；
- Unreal / Unity / Godot 等引擎适配层；
- 自动化测试、Telemetry 与 Reference Vehicle 基准体系。

> 核心原则：**机械系统由 Driveform 求解，刚体世界由宿主 Physics Backend 提供。**

## 当前技术基线

| 层 | 方案 |
|---|---|
| Core | C++20 |
| Public ABI | C ABI / opaque handle / POD struct |
| Build | CMake |
| Web Editor | React + TypeScript + Vite + Three.js |
| Browser Simulation | Driveform Core → WebAssembly |
| Reference Physics | Jolt（仅作为参考后端，不进入 Core 依赖） |
| Unreal | C++ + Chaos Adapter |
| Unity | C# + Native C ABI |
| Godot | C++ GDExtension |
| Authoring Data | JSON + JSON Schema（初期） |

## 仓库结构

```text
Driveform/
├─ Core/                  # 与引擎无关的 C++20 动力学核心
├─ SDK/                   # 稳定 C ABI 与语言包装
├─ Physics/               # Physics Backend 接口与参考实现
├─ Integrations/          # Unreal / Unity / Godot 适配
├─ Web/                   # GitHub Pages Web Editor + WASM
├─ Tests/                 # Unit / Regression / Benchmark
├─ Samples/               # Reference Vehicle 与示例
├─ Docs/                  # TDD / 架构 / 路线图 / 开发规范
└─ .github/workflows/     # CI 与 GitHub Pages 部署
```

## Web Editor

网页编辑器将直接作为本仓库 GitHub Pages 的站点内容：

**https://syurli.github.io/Driveform/**

`main` 分支中 `Web/Editor` 的构建产物由 GitHub Actions 自动部署到 Pages。首期页面先提供项目入口与开发状态，后续逐步接入 Three.js 视口、WASM Core、动力网络、曲线编辑和 Telemetry。

## 第一阶段目标

1. 建立可编译的 Core / C ABI / Physics Interface 最小闭环；
2. 建立 Web Editor 与 GitHub Pages 自动部署；
3. 建立 Fixed Step、Vehicle Runtime、Schema 与 Telemetry 基础；
4. 接入 Jolt Reference Backend；
5. 完成 Powertrain → Suspension/Contact → Wheel → Track 的纵向验证；
6. 以 UE5.8 + Chaos 作为首个正式宿主引擎适配。

详见：

- [`Docs/TDD.md`](Docs/TDD.md)
- [`Docs/ARCHITECTURE.md`](Docs/ARCHITECTURE.md)
- [`Docs/ROADMAP.md`](Docs/ROADMAP.md)
- [`Docs/DEVELOPMENT.md`](Docs/DEVELOPMENT.md)

## 设计边界

`Core/` 中禁止直接依赖：

- Unreal Engine / Chaos
- Unity
- Godot
- Jolt
- Three.js
- 任意宿主引擎对象模型

MMT / UE4 Tracked Vehicles 等项目只作为行为和架构研究参考，不作为 Driveform 的直接代码依赖。

## License

许可证尚未冻结。在正式引入第三方代码或公开发布 SDK 前，将单独确定 Core、Editor、Samples 与第三方依赖的授权策略。
