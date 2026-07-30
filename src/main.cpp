#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include "Mesh.h"


int main() {
    // 1. 初始化 GLFW 和 OpenGL 上下文（Shader 编译必须有上下文）
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Shader Test", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        return -1;
    }

    // ==========================================
    // 测试 1：正常 Shader 加载与编译
    // ==========================================
    Shader basicShader("assets/shaders/test_basic.vert", "assets/shaders/test_basic.frag");
    std::vector<Vertex> vertices = {
    // 位置 (vec3)          // 法线 (vec3)       // 纹理坐标 (vec2)
    { glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) }, // 右上
    { glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f) }, // 右下
    { glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) }, // 左下
    { glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f) }  // 左上
    };
    std::vector<unsigned int> indices = {
    0, 1, 3, // 第一个三角形 (右上, 右下, 左上)
    1, 2, 3  // 第二个三角形 (右下, 左下, 左上)
    };

    Mesh testMesh(vertices, indices);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "Mesh setup failed! OpenGL Error Code: " << err << std::endl;
    }

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);

    // 保持窗口打开，方便你观察控制台输出
    std::cout << "Press ESC to exit..." << std::endl;
    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);
        testMesh.Draw(basicShader);
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL Error Code: " << err << std::endl;
        }
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
