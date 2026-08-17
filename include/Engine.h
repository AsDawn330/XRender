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

    float GetTime() const { return m_currentFrameTime; }
    float GetDeltaTime() const { return m_deltaTime; };
private:
    GLFWwindow* m_window;
    float m_lastFrameTime;
    float m_currentFrameTime;
    float m_deltaTime;

    void UpdateTime();
};

#endif
