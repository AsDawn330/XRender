cmake_minimum_required(VERSION 3.10)
project(XRender)

# 设置 C++ 标准为 17
set(CMAKE_CXX_STANDARD 17)

#添加 Shader 文件
file(GLOB_RECURSE SHADER_FILES 
    "${CMAKE_SOURCE_DIR}/assets/shaders/*.vert"
    "${CMAKE_SOURCE_DIR}/assets/shaders/*.frag"
)

set(SHADER_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets/shaders")
set(SHADER_DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}/assets/shaders")


# 1. 添加可执行文件，把你的源码和 GLAD 的源码都加进去
add_executable(XRenderer 
    src/main.cpp 
    src/Shader.cpp
    src/Mesh.cpp
    
    ${SHADER_FILES}
)

# 2. 告诉编译器去哪里找头文件（包含我们自己的 include 目录）
# target_include_directories(XRender PRIVATE include)
target_include_directories(XRenderer PRIVATE 
    include
    third_party/glm
    third_party/glad/include
)

# 3. 让 CMake 自动寻找系统里的 OpenGL 和 GLFW
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# 添加 第三方 GLAD 库
add_library(glad STATIC 
    third_party/glad/src/glad.c
)
target_include_directories(glad PUBLIC 
    third_party/glad/include
)
# 4. 将 OpenGL ，GLFW ，GLAD 链接到你的可执行文件上

target_link_libraries(XRenderer PRIVATE OpenGL::GL glfw glad)

#将shader文件复制到目标文件夹
add_custom_command(TARGET XRenderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SHADER_SOURCE_DIR}"
        "${SHADER_DEST_DIR}"
    COMMENT "Copying shaders to output directory..."
)
