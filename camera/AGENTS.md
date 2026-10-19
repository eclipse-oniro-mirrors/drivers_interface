# AGENTS.md - OpenHarmony 相机 HDI 接口（drivers_interface_camera）

> 目录级指令文件，作用于本仓全部文件（源码树路径 `drivers/interface/camera/`）。
> 上游通用规则见 `../AGENTS.md`；**相机专属规则以本文件为准**（冲突时本文件优先）。

## 0. 遇到问题读哪里

| 遇到问题 | 读取路径 |
|----------|----------|
| 不确定本仓职责、与实现仓的边界 | §1.1、§1.3 |
| 不确定改动落在哪个版本/目录/文件 | §1.2、§1.4 |
| 不知道这类任务该先读哪些文档 | §2.1、§2.2 |
| 任务描述、日志、接口里出现不认识的术语 | §2.3 |
| 不确定能不能直接改、要不要先确认 | §3.2、§3.3 |
| 需要构建、Lint、契约检查命令 | §4.2–§4.4 |
| 需要完成判定标准与汇报格式 | §4.5、§4.6 |
| 改完 `.idl` 后是否需要同步实现仓 | §1.3、§2.2、§4.4 |
| 构建环境不可用、只有本仓切片 | §4.1、§4.7 |

## 1. 代码地图

### 1.1 仓库定位与职责

本仓是组件 `@ohos/drivers_interface_camera`（version 4.0，subsystem `hdf`，见 `bundle.json:2-14`），是相机驱动与相机服务之间的 IDL 契约定义方。

- 本仓维护：各版本 `.idl` 契约、`bundle.json`/`BUILD.gn`/`camera.gni` 构建配置、手写 C++ 库 `metadata/`（`src`/`include`）与 `sequenceable/`。
- 本仓不维护：proxy/stub/headers 等生成物；相机 HDI 实现（在 `drivers/peripheral/camera`）。
- 消费方：相机服务、多媒体等上层服务；`bundle.json:60-311` 的 `inner_kits` 即对外暴露面。

### 1.2 关键区域

| 子域 | 目录 | 活跃构建 | 说明 |
|------|------|----------|------|
| 基础相机接口 | `v1_0/` | 是 | ICameraHost, ICameraDevice, IStreamOperator, IOfflineStreamOperator, 回调, Types |
| v1_1 扩展 | `v1_1/` | 是 | ICameraHost/ICameraDevice/IStreamOperator 扩展, Types 扩展 |
| v1_2 图像处理 | `v1_2/` | 是 | IImageProcessService/IImageProcessSession/IImageProcessCallback |
| v1_3 视频处理 | `v1_3/` | 是 | IVideoProcessService/IVideoProcessSession/IVideoProcessCallback |
| v1_4 视频扩展 | `v1_4/` | 是 | IVideoProcessCallback/IVideoProcessService 扩展 |
| v1_5 综合 | `v1_5/` | 是 | ICameraHost/ICameraDevice/IStreamOperator 扩展 + 视频处理 |
| v1_6 延续 | `v1_6/` | 是 | IImageProcessService/ICameraHost 扩展 |
| v1_7 最新 | `v1_7/` | 是 | IImageProcessService 扩展；`Types.idl:49` 新增 `EXTENDED_STREAM_OHOS_ENHANCED_GAINMAP` |
| 元数据（混合） | `metadata/` | 是 | 手写 C++ shared library（`metadata:metadata`）**+** hdi-gen 子目标 `metadata/v1_0`（`ICameraVendorTag.idl`、`VendorTagType.idl`，目标 `camera_vendor_tag_idl_target`，见 `bundle.json:38,62-76`）；语义文档 `metadata/README_zh.md` |
| 序列化（手写） | `sequenceable/` | 是 | `buffer_handle`、`buffer_producer`、`map_data` 三个 Parcelable 类型，非 hdi-gen 产物 |

### 1.3 架构边界与继承关系

- **`.idl` 是唯一真相源**：proxy/stub/headers、`*_idl_target`、`*_idl_headers` 均由 `hdi-gen` 在构建时生成，本仓不包含手写 proxy/stub。
- **8 个版本并行活跃**：v1_0–v1_7 全部列在 `bundle.json:37-58` 的 `sub_component` 中（父文件"历史版本目录不在活跃构建中"的表述**不适用于相机仓**）。
- **版本链（精确）**：`v1_7` 的 `stub_deps`/`proxy_deps` 同时依赖 `../v1_2`–`../v1_6`；`v1_6` 依赖 `../v1_2`–`../v1_5`；`v1_5` 依赖 `../v1_3`、`../v1_4`。新版本必须依赖其与上一版本之间**所有**中间版本，且 `stub_deps` 与 `proxy_deps` 成对出现。
- **Types 不跨版本共享**：每版本自带 `Types.idl`，通过 `import` 引用旧版本类型；不得用旧版本文件覆盖新版本。
- **继承关系**：本文件继承 `../AGENTS.md`（跨子域 Ask-before、构建命令模式、术语表）；与相机实际不符的通用表述不生效。

### 1.4 常见任务 → 入口路径

| 任务类型 | 入口路径 |
|----------|----------|
| 新增/修改相机接口方法 | 最新版本目录 `v1_7/` 下对应 `I*.idl` + `Types.idl`；需要新版本时新建 `v1_8/` |
| 流类型、扩展流信息 | `v1_7/Types.idl`（`ExtendedStreamInfoType` 等枚举） |
| 图像处理会话 | `v1_2`/`v1_3`/`v1_5`/`v1_6`/`v1_7` 的 `IImageProcessService.idl`、`IImageProcessSession.idl`（按版本实际存在的文件） |
| 视频处理会话 | `v1_3`/`v1_4`/`v1_5` 的 `IVideoProcessService.idl`、`IVideoProcessSession.idl` |
| vendor tag / 元数据语义 | `metadata/v1_0/ICameraVendorTag.idl`、`VendorTagType.idl`、`metadata/README_zh.md` |
| 序列化（buffer/map）类型 | `sequenceable/buffer_handle`、`buffer_producer`、`map_data` |
| 组件、依赖、发布单元 | `bundle.json`、`camera.gni` |

## 2. 知识路由

### 2.1 按任务类型路由

| 任务类型 | 必读 | 关键点 |
|----------|------|--------|
| 新增 IDL 方法 / 修改签名 | 本文件 §3.1–§3.3、目标版本 `Types.idl`、`bundle.json:60-311`、`../AGENTS.md` Ask-before | 触及 ABI，必须走接口评审；不得原地改签名 |
| 新增版本目录（如 `v1_8/`） | `bundle.json:37-58`、最新版本 `BUILD.gn`（v1_7）、§3.1 版本链规则 | 漏同步 `sub_component`/`inner_kits` 会导致版本不参与构建与发布 |
| 修改 `bundle.json` | `bundle.json` 现有 `sub_component`/`inner_kits` 对应关系、§3.3 | 发布单元变更影响消费方 SDK |
| 修改 `camera.gni` 特性开关 | `camera.gni`、`bundle.json:15-18` features | `drivers_interface_camera_feature_vendor_tag`（默认 true）、`..._coverage`（默认 false）必须在两处同时出现 |
| 修改 vendor tag / 元数据 | `metadata/README_zh.md`、`metadata/v1_0/*.idl`、`bundle.json:38,62-76` | tag 语义属于公共契约，按 ABI 对待 |
| 修改 `sequenceable/*` | 引用该类型的 `v1_*/BUILD.gn`（`sequenceable_pub_deps`/`stub_deps`） | 影响 Parcelable 序列化兼容性 |
| 修改构建目标或依赖 | 对应 `BUILD.gn`、`../AGENTS.md` 依赖评审条款 | 新生产依赖须经 `bundle.json` 评审 |
| 文档/注释变更 | 本文件 §5 风格要求 | 不改 ABI，但不得删除或改写既有错误码语义 |

### 2.2 按路径路由

| 改动路径 | 必读 / 必须同步 |
|----------|----------------|
| `v1_0/**` | 最上游基础类型：变更影响 v1_1–v1_7，改前必须列出全部上游引用 |
| `v1_1/**`–`v1_7/**` | 该版本 `Types.idl` + 上一版本对应文件（`extends`/`import` 关系） |
| `metadata/**` | `bundle.json:38,62-76`、`metadata/README_zh.md` |
| `sequenceable/**` | 使用该类型的版本 `BUILD.gn` 依赖项 |
| `bundle.json` | `sub_component` ↔ `inner_kits` ↔ `features` 三处一致性；§3.3 |
| `camera.gni` | `bundle.json` features、实现仓 `drivers/peripheral/camera` 的对应开关 |
| `AGENTS.md`（本文件） | 仅在本仓结构/约束真实变化时更新；不得写入未经验证的路径、目标名或命令 |

### 2.3 按术语路由

| 术语 | 含义 | 命中后的动作 |
|------|------|--------------|
| `.idl` / `hdi-gen` | IDL 契约源文件 / 代码生成工具 | 只改 `.idl`，生成物由构建产生 |
| proxy / stub | 上层调用代理 / 下层实现桩（构建生成） | 出现 `_proxy.h/.cpp`、`_stub.h/.cpp` 改动即违规 |
| `hdi()` / `module_name` | `BUILD.gn` 的 HDI 目标模板 / 模块名 | 新版本照最新版本 `BUILD.gn` 结构，`module_name` 保持 `camera_service` |
| `no_other_header_files` | 限制额外头文件导出的模板开关 | 当前为 true：`metadata/v1_0`、`v1_5`、`v1_6`、`v1_7`；新版本保持一致后再评估 |
| `stub_deps` / `proxy_deps` | 版本间依赖声明 | 必须成对同步（§3.1） |
| `sequenceable_pub_deps` / `sequenceable_ext_deps` | 序列化类型依赖 / 图形等外部依赖 | 改动 sequenceable 时检查所有引用版本 |
| `LOG_DOMAIN` | 接口库日志域 | v1_0–v1_6 为 `0xD002513`；新增版本沿用，改变需评审 |
| `sub_component` / `inner_kits` | 构建子目标清单 / 内部 SDK 暴露面 | 改一处必须同步另一处（§3.3） |
| `innerapi_tags` / `sa_profile` | 内部 API 标签 / 安全属性配置 | 本仓 `bundle.json` **当前无**这两个字段；若目标分支存在，修改前须确认芯片 SDK/平台 SDK 兼容性（§3.3） |
| `camera_idl_target` / `camera_idl_headers` | hdi-gen 生成的构建目标 / 头文件目标 | 由 `.idl` + `BUILD.gn` 决定，不手改 |
| vendor tag / `ICameraVendorTag` | 相机元数据标签接口 | 读 `metadata/README_zh.md` 与 `metadata/v1_0/*.idl` |
| `ExtendedStreamInfoType` / `EXTENDED_STREAM_*` | 扩展流信息枚举 | 读最新版本 `Types.idl` |
| `_V1_x` 后缀 | 同名方法的新版本签名（如 `OpenCamera_V1_1`、`GetStreamOperator_V1_1`） | 新版本只能新增 `_V1_x` 方法，不得修改旧方法签名 |
| `OHOS::HDI::Camera::V1_x` | 生成代码与手写 C++ 使用的命名空间 | 手写代码沿用同构命名空间 |
| `drivers/peripheral/camera` | 相机 HDI 实现仓 | 接口变更后必须核对实现同步（§4.4） |

### 2.4 计划阶段与编辑前声明

开始任何任务前，必须先输出以下 5 项；缺少任一项即视为未完成前置检查：

1. **任务分类**：新增接口 / 修改签名 / 新增版本 / 构建配置 / metadata / sequenceable / 文档。
2. **目标版本与目录**，以及是否为活跃构建（对照 §1.2）。
3. **已读文档清单**：按 §2.1–§2.3 命中的条目逐项列出。
4. **命中的约束与 Ask-before 项**（§3.2、§3.3）及确认结论。
5. **影响面与验证计划**：是否影响 ABI、是否需同步 `drivers/peripheral/camera`、将执行的 §4.4 命令。

## 3. 约束边界

### 3.1 架构不变量

- `.idl` 是唯一真相源：生成物不得手改，只能改 `.idl` / `BUILD.gn` 后由构建重生成。
- 版本号即 ABI 契约：跨版本交互必须通过版本化库显式选择。
- 8 个版本并行活跃构建，全部在 `bundle.json` `sub_component` 中。
- 版本链依赖必须完整传递（v1_7 → v1_2..v1_6），`proxy_deps` 与 `stub_deps` 成对。
- 扩展方法使用 `_V1_x` 后缀，避免与基版本方法签名冲突。
- `Types.idl` 不跨版本共享；每版本独立维护，通过 `import` 引用旧类型。
- `metadata/` 同时包含手写 C++ 库与 hdi-gen 子目标 `metadata/v1_0`，两者边界不得混淆。

### 3.2 禁止事项（Do not）

- 不要手改 `hdi-gen` 生成的 proxy/stub/headers、`*_idl_target`、`*_idl_headers`。
- 不要删除、重命名已发布的 IDL 方法，或复用/调整已有方法的码值。
- 不要在 IDL `struct` 中间插入字段（破坏 Parcelable ABI）；字段只追加末尾。
- 不要修改 `bundle.json` 的 `sub_component` 而不同步 `inner_kits`，反之亦然。
- 不要在本仓库中实现 HDI 逻辑；实现属 `drivers/peripheral/camera`。
- 不要新建版本时只依赖最近一个版本而跳过中间版本。
- 不要引入未经 `bundle.json` 评审的生产依赖。
- 不要删除既有错误码、日志域，或降低既有权限校验语义。
- 不要在验证过程中执行刷写、烧写、擦除、格式化等破坏性设备操作。

### 3.3 Ask-before（先确认再动手）

| 操作 | 确认内容 | 确认对象 |
|------|----------|----------|
| 新增/删除 IDL 方法（含 `_V1_x` 扩展） | 是否影响 ABI 与消费方 | 接口评审团队 |
| 新增版本目录（如 `v1_8/`） | `sub_component`/`inner_kits`/版本链三处一致性 | 项目负责人 |
| 修改 `bundle.json` 的 `sub_component` 或 `inner_kits` | 两字段是否同步 | 项目负责人 |
| 修改 `innerapi_tags`/`sa_profile`（若目标分支存在） | 芯片 SDK/平台 SDK 兼容性 | 芯片适配团队 |
| 修改 `camera.gni` 特性开关默认值 | 是否影响其他子域或产品形态构建 | 构建团队 |
| 修改 `metadata/v1_0` vendor tag IDL | ABI 影响 + `bundle.json:62-76` 同步 | 接口评审团队 |
| 变更涉及权限/隐私语义的接口 | 是否触发安全与隐私评审 | 安全/隐私评审 |
| 引入新的生产依赖 | 是否经 `bundle.json` 依赖评审 | 依赖评审团队 |
| 新增、重命名或删除 IDL 文件 | 对所有消费方与 `inner_kits` 的影响 | 相关消费方 |
| 修改 `v1_0` 基础类型 | 对 v1_1–v1_7 的连带影响 | 接口评审团队 |

### 3.4 安全、权限与隐私边界

- 相机采集数据属敏感数据：新增接口的注释、示例、日志中不得出现图像内容、元数据明文或可识别用户的信息。
- 本仓不得新增绕过上层权限校验、或降低既有校验语义的接口能力（如隐式打开设备、跳过回调校验）；涉及校验契约的变更必须升级确认。
- vendor tag 与扩展流信息是公共契约，修改前评估越权读取元数据的风险。
- 涉及分布式相机/跨设备场景时先确认信任边界；本仓不定义信任逻辑，不得在此假定。

### 3.5 DFX、日志与错误码

- 错误码：负值表示错误（如 `CAMERA_BUSY = -1`），非负表示状态/类型；新增只能追加，不得改动既有取值与语义。
- 日志域：接口库 `LOG_DOMAIN = 0xD002513`（v1_0–v1_6 的 `BUILD.gn` defines）；新增版本沿用，变更需评审。
- 注释：新增方法/枚举/结构必须有 `@brief`、`@since`、`@version`、`@param`、`@return`，`@since` 与目标版本一致。
- 不得为"简化改动"而删除既有日志、错误码或 `[in]`/`[out]` 方向注解。

### 3.6 依赖与许可

- 不得引入未经 `bundle.json` 评审的生产依赖；`component.deps.components`/`third_party` 为受控清单。
- 所有新增文件保留 Apache 2.0 版权头。
- `metadata/`、`sequenceable/` 为手写 C++，引入第三方代码前必须完成许可评审。

### 3.7 设备与破坏性操作

- 本仓为纯接口定义，默认验证应只读；不得执行刷写、烧写、擦除、格式化等设备操作。
- 如需在真机验证（如 `hdc` 侧载安装），先取得确认，并说明目标设备、影响范围与回滚方式。

### 3.8 相机专属失败模式

| 失败模式 | 后果 | 预防 |
|----------|------|------|
| 手改 `_proxy.h/.cpp`、`_stub.h/.cpp`、`*_idl_headers` | 下次构建即被覆盖，生成不一致 | 只改 `.idl`，由构建重生成 |
| 在 IDL `struct` 中间插入字段 | Parcelable ABI 断裂，旧实现解析错位 | 字段只追加末尾 |
| 新增版本目录但不改 `bundle.json` | 版本不参与构建与发布 | 按 §3.3 三处同步 |
| `proxy_deps`/`stub_deps` 不成对或漏中间版本 | 单独编 proxy 或 stub 时链接失败 | 成对修改并覆盖全部中间版本 |
| 复制旧版本 `BUILD.gn` 时漏 `no_other_header_files`/`LOG_DOMAIN`/`stub_deps` | 导出面或日志域变化 | 与最新版本逐项 diff |
| 误改 `v1_0` 基础类型 | 影响 v1_1–v1_7 全部上游 | 先做影响面评估（§3.3） |
| 调整 `sequenceable` 字段顺序 | 跨进程反序列化失败 | 保持顺序，只追加 |
| 假定 `bundle.json` 含 `innerapi_tags`/`sa_profile` | 校验失败、误导改动 | 先用 §4.2 命令确认字段是否存在 |
| 使用不存在的脚本或未确认的校验命令 | 误以为已验证 | 只用 §4.2/§4.3 中列出的命令 |

## 4. 验证闭环

### 4.1 环境前置条件

- 本仓是 OpenHarmony 源码树的子目录（`drivers/interface/camera`）。§4.3 的构建命令必须在**完整源码树 + Linux/WSL 环境**下、从源码树根目录执行。
- 只有本仓切片（无 `build.sh`/`gn`/`hdi-gen`）时：执行 §4.2，并按 §4.7 明确标注「未验证」。
- 代码块中的 `bash` 命令需 POSIX shell；Windows 环境请用 §4.2 的 PowerShell 等价写法。

### 4.2 最小验证（本仓内可执行，不需要完整源码树）

```powershell
# 1) 组件配置可解析
python -m json.tool bundle.json > $null

# 2) 生成物未被手改：输出中出现 _proxy/_stub 即违规
git diff --name-only | Select-String -Pattern '_(proxy|stub)\.(h|cpp)$'

# 3) IDL 包名与目录版本一致：v1_x → ohos.hdi.camera.v1_x；metadata/v1_0 → ohos.hdi.camera.metadata.v1_0
Select-String -Path .\v1_*\*.idl, .\metadata\v1_0\*.idl -Pattern '^package ' |
  ForEach-Object { $_.Line.Trim() } | Sort-Object -Unique

# 4) 改动范围自查（确认没有越界改动）
git status --porcelain
```

```bash
# 等价的最小验证（POSIX shell）
python -m json.tool bundle.json > /dev/null
git diff --name-only | grep -E '_(proxy|stub)\.(h|cpp)$'
grep -h '^package ' v1_*/*.idl metadata/v1_0/*.idl | sort -u
git status --porcelain
```

### 4.3 构建 / Lint / 契约检查（完整源码树，从源码树根目录执行）

```bash
# 全量构建相机接口组件
./build.sh --product-name rk3568 --build-target drivers_interface_camera

# 单独构建关键目标（目标名与 bundle.json:37-58、60-311 一致）
./build.sh --product-name rk3568 --build-target //drivers/interface/camera/v1_7:camera_idl_target
./build.sh --product-name rk3568 --build-target //drivers/interface/camera/v1_0:libcamera_stub_1.0
./build.sh --product-name rk3568 --build-target //drivers/interface/camera/metadata:metadata
./build.sh --product-name rk3568 --build-target //drivers/interface/camera/sequenceable/buffer_handle:libbuffer_handle_sequenceable_1.0

# 构建配置检查
gn gen --check
```

- 生成物一致性以"构建成功 + §4.2 第 2 步无输出"为准。
- `--lint`、`hdi-gen --check`、`gn format --check` 等标志未在本仓验证；使用前先用 `--help` 确认，或替换为上述可执行检查，不要直接抄写未确认的命令。

### 4.4 任务特定验证

| 任务类型 | 验证方式 | 通过标准 |
|----------|----------|----------|
| 新增/修改 IDL 方法 | §4.2 第 1/3 步 + 目标版本 `camera_idl_target` 构建 | 构建成功；包名与版本一致；生成物无手改 |
| 新增版本目录 | 全量构建 + §3.3 三处同步核对 | 新版本出现在 `sub_component`，`inner_kits` 同步 |
| 修改 `bundle.json` | 与 §2.2 一致性清单逐项核对 | `sub_component`/`inner_kits`/`features` 一致 |
| 特性开关变更 | 全量构建 + `bundle.json:15-18` 对照 | 两处开关同名同义 |
| vendor tag / 元数据 | `metadata:metadata` + `metadata/v1_0` 目标构建 + `bundle.json:62-76` 对照 | 目标可构建，暴露面一致 |
| `sequenceable` 变更 | 引用该类型的各版本 `camera_idl_target` 构建 | 所有引用版本编译通过 |
| 注释/文档变更 | §4.2 全部 | 无生成物改动；包名一致；错误码语义未变 |
| 跨层同步（IDL ↔ 实现） | 人工复核 `drivers/peripheral/camera`（含其 `AGENTS.md`） | 实现已同步，或已登记待办并说明 |

### 4.5 Done 定义

任务完成需同时满足：

1. §2.4 的编辑前声明已输出，且与最终改动一致。
2. §4.2 最小验证全部通过（或按 §4.7 标注未验证）。
3. 受影响版本/目标的 §4.3 构建通过，`bundle.json` 三处字段一致。
4. ABI 影响已判定；如有影响，已取得 §3.3 对应确认。
5. 生成物未被手改；`.idl` 是唯一改动源。
6. 涉及接口变更的，`drivers/peripheral/camera` 实现同步情况已核对并说明。
7. 按 §4.6 输出完成报告。

### 4.6 最终响应期望

完成报告必须包含：

1. 修改文件清单（按 `file:line` 引用）。
2. 任务分类、目标版本/目录及是否为活跃构建。
3. 已读文档与命中的约束/Ask-before 项及结论。
4. 是否影响 ABI、是否影响特性开关默认值。
5. 是否触发跨层同步（`drivers/peripheral/camera` / `bundle.json` / `inner_kits`）。
6. 每条验证命令的执行结果（构建 / 契约检查 / 最小验证）。
7. 未验证项与原因（见 §4.7）。

### 4.7 无法验证时

如果构建环境不可用（如仅有本仓切片）：

1. 列出应执行的 §4.3 命令及各自预期结果，并明确标注「**未验证**」。
2. 至少完成 §4.2 的 4 项本仓内检查，并给出实际输出。
3. 涉及 `drivers/peripheral/camera` 的同步性，必须人工复核 IDL 与实现的匹配性，并说明当前环境无法编译验证的限制。
4. 不得以"构建未执行"为由省略影响面、Ask-before 结论与风险说明。

## 5. 代码风格

### 5.1 版权头

所有文件以 Apache 2.0 版权头开头（`/*` 多行注释块或 `#` 注释块）。

### 5.2 IDL 风格

- **接口命名**：`I` 前缀（ICameraHost, ICameraDevice, IStreamOperator, IImageProcessService）。
- **包声明**：`package ohos.hdi.camera.vX_Y;`；`metadata/v1_0` 为 `ohos.hdi.camera.metadata.v1_0`。
- **共享类型**：版本内 `Types.idl` 定义 enum 与 struct；新版本通过 `import` 引用旧版本类型。
- **enum 值**：负数表示错误码（如 `CAMERA_BUSY = -1`），非负数表示状态/类型。
- **struct 字段**：snake_case 带尾缀下划线（`streamId_`、`width_`）。
- **方向注解**：`[in]`、`[out]` 显式标记每个参数。
- **扩展方法**：新版本同名方法加 `_V1_x` 后缀（如 `CreateImageProcessSession_V1_6`、`OpenCamera_V1_1`）。
- **Javadoc 风格注释**：`@brief`、`@since`、`@version`、`@param`、`@return`。

### 5.3 C++ 风格（`metadata/`、`sequenceable/`）

- **命名空间**：`OHOS::HDI::Camera::V1_0`（四层嵌套），或 `OHOS::Camera`（metadata）。
- **包含守卫**：`#ifndef OHOS_XXX_H / #define / #endif`。
- **类命名**：PascalCase（`BufferHandleSequenceable`、`CameraMetadata`）；**方法**：camelCase；**变量**：snake_case 且成员变量尾缀下划线。
- **常量/宏**：UPPER_SNAKE_CASE（`MAX_SUPPORTED_TAGS`、`HDI_CAMERA_LOGE`）。
- **头文件顺序**：本模块头 → 标准库 → 系统库 → 外部库，每组空行分隔。
- **空指针检查**：`if (ptr == nullptr) { HDI_CAMERA_LOGE("..."); return false; }`。
- **日志宏**：sequenceable 用 `HDI_CAMERA_LOGE/LOGW/LOGI/LOGV/LOGD`，metadata 用 `METADATA_ERR_LOG/WARNING_LOG/INFO_LOG/FATAL_LOG/DEBUG_LOG`。
- **生命周期**：`sptr` 引用计数指针；`new (std::nothrow)` 无异常分配；虚方法显式标注 `override`。

### 5.4 构建风格

- `camera.gni`：`drivers_interface_camera_feature_vendor_tag`（默认 true）、`drivers_interface_camera_feature_coverage`（默认 false）。
- `bundle.json`：`component.deps.components` 为受控依赖清单；`sub_component` 与 `inner_kits` 必须同步。
- 新增版本目录时，以最新版本 `BUILD.gn` 为模板，保持 `module_name = "camera_service"`、`no_other_header_files`、日志域与依赖项一致。
