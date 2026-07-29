#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // 1. 初始化 GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // 2. 配置窗口属性 (Mac 必须指定 OpenGL 3.3 Core Profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac 专属

    // 3. 创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "XRenderer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 4. 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return -1;
    }

    // 5. 渲染循环
    while (!glfwWindowShouldClose(window)) {
        // 设置背景颜色 (深蓝色)
        glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 交换前后缓冲区
        glfwSwapBuffers(window);
        // 处理输入事件
        glfwPollEvents();
    }

    // 6. 清理资源
    glfwTerminate();
    return 0;
}