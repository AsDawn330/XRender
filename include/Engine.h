#ifndef _ENGINE__H
#define _ENGINE__H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Engine {
public:
    Engine(unsigned int width, unsigned int height, const std::string& title);
    Engine();
    ~Engine();
    // 禁止拷贝和赋值（因为窗口和GL上下文是唯一的）
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    bool shouldClose() const;
    void Update();
    GLFWwindow* GetWindow() const { return m_window; }
private:
    GLFWwindow* m_window;
};

#endif
