#include "Engine.h"

Engine::Engine(unsigned int width, unsigned int height, const std::string& title) {
    // 1. 初始化 GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW!");
    }
    // 2. 配置 OpenGL 版本和核心模式
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    // 3. 创建窗口
    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window!");
    }
    // 4. 设置上下文并初始化 GLAD
    glfwMakeContextCurrent(m_window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD!");
    }
    // 5. 设置默认的 OpenGL 状态
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    std::cout << "Engine initialized successfully. OpenGL Version: " 
              << glGetString(GL_VERSION) << std::endl;
}
Engine::Engine() : Engine(800, 600, "Default Window") {}
Engine::~Engine() {
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

bool Engine::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void Engine::Update() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
    UpdateTime();
}

void Engine::UpdateTime() {
    m_currentFrameTime = static_cast<float>(glfwGetTime());
    m_deltaTime = m_currentFrameTime - m_lastFrameTime;
    m_lastFrameTime = m_currentFrameTime;
}
