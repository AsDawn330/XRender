XRender 渲染器阶段性目标与模块规划
阶段一：底层基础设施与渲染管线入门 (Infrastructure & Pipeline)
🎯 阶段目标：搭建稳固的工程骨架，彻底理解现代 OpenGL 的“可编程管线”核心机制。
📦 模块规划：
Shader 管理模块：封装 Shader 类，实现从文件读取、编译、链接及完善的错误日志输出。
几何数据管理模块：深入理解并封装 VAO、VBO、EBO，掌握顶点数据的内存布局。
基础图元渲染：在屏幕上绘制出第一个彩色三角形，打通“CPU 传数据 -> GPU 处理 -> 屏幕显示”的完整闭环。
工程化规范：引入 .gitignore，规范代码目录（将 Shader 源码独立到 assets/shaders 目录）。
阶段二：数学基础与 3D 空间变换 (Math & Transformations)
🎯 阶段目标：引入数学库，摆脱硬编码，让场景具备真正的三维空间概念。
📦 模块规划：
数学库集成：通过 Homebrew 引入 GLM 库，并配置到 CMake。
变换系统 (Transform)：实现 Model（模型）、View（观察）、Projection（投影）三大矩阵。
相机系统 (Camera)：封装 Camera 类，实现 MVP 矩阵的动态计算，让 3D 场景具备纵深感。
渲染引擎（Engine）：封装Engine 类，实现OpenGL的窗口初始化和循环过程，不在main函数中写复杂的OpenGL逻辑。
阶段三：交互系统与输入控制 (Input System)
🎯 阶段目标：建立一套解耦的输入处理机制，实现第一人称视角的自由漫游。
📦 模块规划：
键盘输入模块：实现 WASD 移动与 Shift 加速，处理基于时间步长（DeltaTime）的平滑移动。
鼠标输入模块：捕获鼠标光标，计算鼠标偏移量，实现视角的平滑旋转。
事件分发机制：将 GLFW 的回调函数与 Camera 类解耦，为后续更复杂的输入（如 UI 交互）打基础。
阶段四：光照与材质系统 (Lighting & Materials)
🎯 阶段目标：赋予场景立体感和真实感，掌握 Fragment Shader 的核心计算。
📦 模块规划：
Phong 光照模型：实现环境光 (Ambient)、漫反射 (Diffuse)、镜面高光 (Specular) 三大核心组件。
光源类型扩展：支持平行光 (Directional)、点光源 (Point)、聚光灯 (Spot)。
材质系统 (Material)：将材质的反射率、高光指数等属性抽离，支持不同物体呈现不同的质感。
阶段五：纹理映射与模型加载 (Textures & Models)
🎯 阶段目标：丰富渲染器的视觉表现力，从“色块”走向“真实世界”。
📦 模块规划：
纹理系统：引入 stb_image 库，实现图片加载、纹理生成与采样。
多纹理混合：支持漫反射贴图、镜面光贴图、法线贴图的组合使用。
模型加载器：引入 Assimp 库，解析 obj/gltf 等格式，实现 Mesh 和 Model 的层级封装。
阶段六：高级渲染与性能优化 (Advanced & Optimization)
🎯 阶段目标：提升画面表现力与运行效率，向现代渲染器靠拢。
📦 模块规划：
高级光照：法线贴图、视差贴图、阴影映射 (Shadow Mapping)。
后处理特效：引入 Framebuffer (FBO)，实现泛光 (Bloom)、色调映射等后处理效果。
性能优化：实例化渲染 (Instancing)、视锥体剔除、渲染状态管理。