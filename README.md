# Tanxl GameEngine

**A 2D game engine written in C++ with OpenGL.**  
*一款使用 C++ 与 OpenGL 开发的 2D 游戏引擎。*

Tanxl (TEnGinE) is an independently developed 2D game engine featuring a modular
OpenGL renderer, an NPC / dialogue / story system, multi-language text, a map
editor, and Steam integration. Development has been continuous since 2022.

> **Status / 状态**
>
> - **Active development.** The milestone list below reflects the real, ongoing
>   development progress — the newest entry at the bottom is always the current
>   state.
>   *开发持续进行中。下方里程碑列表展示真实的开发进度——末尾条目即最新状态。*
> - **Latest public release: Version 0.3 Build 19.**
>   *最新公开发布版本：0.3 Build 19。*
> - Public releases are cut periodically (roughly **weekly**) from the milestones
>   below (marked ✔). Because internal development often produces several builds
>   per week, the *published* version trails the internal development milestone.
>   *公开发布版会定期（约每周一次）从下方里程碑中整理而出（标注 ✔）。由于内部开发往往每周产出多个版本，已发布版本会落后于内部开发里程碑。*

---

## Features / 特性

- **Modular OpenGL renderer** — a coordinator plus dedicated sub-renderers
  (NPC renderer, map layers via Shader Storage Buffer Objects, instanced drawing).
  *模块化 OpenGL 渲染器——协调器 + 独立子渲染器（NPC 渲染器、基于 SSBO 的地图层、实例化绘制）。*
- **NPC, dialogue & story system** — data-driven NPCs, conversation flows, and
  an event / observer mechanism.
  *NPC、对话与剧情系统——数据驱动的非玩家角色、对话流程与事件/观察者机制。*
- **Multi-language localization** — Chinese / English / French / Russian text,
  loaded from external text files with per-font configuration.
  *多语言本地化——中/英/法/俄文本，从外部文本文件加载，支持逐字体配置。*
- **Map editor & minimap** — in-engine map data management and a minimap view.
  *地图编辑器与小地图——引擎内地图数据管理与小地图视图。*
- **Audio** — sound effects and music via irrKlang.
  *音频——基于 irrKlang 的音效与音乐。*
- **Steam integration** — Steamworks SDK support.
  *Steam 集成——支持 Steamworks SDK。*
- **Configurable fonts & text rendering** — font size / tracking / line-height
  driven by configuration files.
  *可配置字体与文本渲染——字号 / 字间距 / 行距由配置文件驱动。*

---

## Build / 构建

### Requirements / 环境要求

- Visual Studio **2022**, platform toolset **v143**.
  *Visual Studio 2022，平台工具集 v143。*
- Configuration: **Release | x64** only.
  *配置：仅 Release | x64。*
- Third-party libraries are bundled under `Vendor/` (with `include/`, `lib/`, `dll/`):
  *第三方库已置于 `Vendor/`（含 `include/`、`lib/`、`dll/`）：*
  - GLFW, GLEW, SOIL2, irrKlang, FreeType
  - Steamworks SDK (`steam_api64`)

### Steps / 步骤

1. Open the solution in VS2022 (toolset v143).
   *用 VS2022（工具集 v143）打开解决方案。*
2. Select the **Release | x64** configuration.
   *选择 Release | x64 配置。*
3. Build and run.
   *生成并运行。*

> **Stability note / 稳定性说明:** Milestones marked ✔ are kept buildable.
> Development builds created between releases may temporarily fail to compile;
> if you encounter a broken build, fall back to the previous marked milestone or
> wait for the next release.
> *标注 ✔ 的里程碑保持可编译。两次发布之间的开发版本可能临时无法编译；
> 若遇到无法编译的版本，请回退到上一个标注里程碑或等待下一版本。*

---

## Development Milestones (TURBO) / 开发里程碑

This list tracks **actual development progress** (newest at the bottom).  
*本列表展示**真实的开发进度**（最新在末尾）。*

> ✔ = this milestone was packaged as a public release.  
> ✔ = 该里程碑已被整理为公开发布版本。

- [Version 0.1 Build 42 — TURBO 01 — 2022/09/24](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/745737dd7657d30426fc1ade26ca015d0c392047) ✔
- [Version 0.1 Build 48 — TURBO 02 — 2022/11/12](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/334cef132c790e15d9a2321cdc2d881da438fd65) ✔
- [Version 0.1 Build 54 — TURBO 03 — 2022/12/28](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/cba724e443b5c5c32b80dc338edd35bad98b1ea1) ✔
- [Version 0.1 Build 59 — TURBO 04 — 2023/01/09](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/45e2517d92d02644875805aad026954023ebf752) ✔
- [Version 0.1 Build 69 — TURBO 05 — 2023/02/08](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/668e63193569930469e8e93d450e292638e82ff8) ✔
- [Version 0.1 Build 78 — TURBO 06 — 2023/02/28](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/38f6f5835381561ccf2a1e040bc867a6ddc2924d) ✔
- [Version 0.1 Build 86 — TURBO 07 — 2023/03/20](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/4c083c16ffc2f8e0eb5dafd16e0ae263981e46a7) ✔
- [Version 0.1 Build 94 — TURBO 08 — 2023/04/13](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/ec9d0cfdff6d284175f5c357f9f9f14d9260c9dd) ✔
- [Version 0.2 Build 2 — TURBO 09 — 2023/05/06](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/7d6711d4d0cbd6a7f75a68c10aaf19466e553625)
- [Version 0.2 Build 11 — TURBO 10 — 2023/06/25](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/35f1a96851b843b0c724f94eaf823e7cf8985195)
- [Version 0.2 Build 21 — TURBO 11 — 2023/07/27](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/e02e79bebd58f3d8ec21a3896072baee969952a8)
- [Version 0.2 Build 30 — TURBO 12 — 2023/08/22](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/34618423237e965420dd21ced3d7ff98177926bc)
- [Version 0.2 Build 42 — TURBO 13 — 2023/10/07](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/5fb0fb0dbcd7fe2bacb193f1be104e84ce177925)
- [Version 0.2 Build 51 — TURBO 14 — 2023/11/01](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/d576d4a004261f2930944bca9fc2b46871568198)
- [Version 0.2 Build 64 — TURBO 15 — 2023/12/05](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/6667508d8e879692aec7abb6dcb3036e8e47e196)
- [Version 0.2 Build 77 — TURBO 16 — 2024/01/08](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/16afba4c5d5e4e043b4748fe0cb60ba1064cdb80)
- [Version 0.2 Build 87 — TURBO 17 — 2024/01/31](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/86a35800bc19258acf2027a006760055f9b164a3)
- [Version 0.2 Build 94 — TURBO 18 — 2024/02/28](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/3e4d95e6c29ae9662377623ebcdc9da194468ae3)
- [Version 0.3 Build 6 — TURBO 19 — 2024/04/07](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/a4e3350dac8e38d9e5a9cdea44363fe828f67b53)
- [Version 0.3 Build 16 — TURBO 20 — 2024/05/21](https://github.com/NormanGrimes/Tanxl_GameEngine/commit/33795ff366eadd764a4506654dbb07b6f56f0c24)
- Version 0.3 Build 22 — TURBO 21 — 2024/06/13
- Version 0.3 Build 31 — TURBO 22 — 2024/07/10
- Version 0.3 Build 42 — TURBO 23 — 2024/08/14
- Version 0.3 Build 52 — TURBO 24 — 2024/09/24
- Version 0.3 Build 59 — TURBO 25 — 2024/10/28
- Version 0.3 Build 66 — TURBO 26 — 2024/12/11
- Version 0.3 Build 74 — TURBO 27 — 2025/01/07
- Version 0.3 Build 85 — TURBO 28 — 2025/02/06
- Version 0.4 Build 04 — TURBO 29 — 2025/04/02
- Version 0.4 Build 15 — TURBO 30 — 2025/05/26
- Version 0.4 Build 25 — TURBO 31 — 2025/07/07
- Version 0.4 Build 37 — TURBO 32 — 2025/08/29
- Version 0.4 Build 47 — TURBO 33 — 2025/10/17
- Version 0.4 Build 56 — TURBO 34 — 2025/11/17
- Version 0.4 Build 66 — TURBO 35 — 2025/12/11
- Version 0.4 Build 78 — TURBO 36 — 2026/01/12
- Version 0.4 Build 88 — TURBO 37 — 2026/02/02
- Version 0.4 Build 99 — TURBO 38 — 2026/03/09
- Version 0.5 Build 10 — TURBO 39 — 2026/04/24
- Version 0.5 Build 20 — TURBO 40 — 2026/05/29
- Version 0.5 Build 31 — TURBO 41 — 2026/06/30
- Version 0.5 Build 41 — TURBO 42 — 2026/08/04

---

## Links / 链接

- **Steam:** [TANXL on Steam](https://store.steampowered.com/app/1929530/Tanxl/)
- **Repository:** https://github.com/NormanGrimes/Tanxl_GameEngine

---

## License / 许可证

GPL-2.0 license

---

## Author / 作者

WiChG_Programing
