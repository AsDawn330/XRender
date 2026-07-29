cmake_minimum_required(VERSION 3.10)
project(XRender)

# 设置 C++ 标准为 17
set(CMAKE_CXX_STANDARD 17)

# 1. 添加可执行文件，把你的源码和 GLAD 的源码都加进去
add_executable(XRenderer 
    src/main.cpp 
    src/glad.c
)

# 2. 告诉编译器去哪里找头文件（包含我们自己的 include 目录）
# target_include_directories(XRender PRIVATE include)
include_directories(include)
# 3. 让 CMake 自动寻找系统里的 OpenGL 和 GLFW
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# 4. 将 OpenGL 和 GLFW 链接到你的可执行文件上
target_link_libraries(XRenderer PRIVATE OpenGL::GL glfw)