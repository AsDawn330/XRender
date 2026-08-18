#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unistd.h>


#include "Shader.h"
#include "Camera.h"
#include "Transform.h"
#include "Mesh.h"
#include "Engine.h"
#include "Texture.h"

int main() {
    chdir(PROJECT_SOURCE_DIR); 
    Engine engine = Engine();

    // --- 5. 初始化场景资源 (必须在 GLAD 初始化之后) ---
    Shader shader("assets/shaders/test_basic.vert", 
              "assets/shaders/test_basic.frag");
    
    Texture texture;
    texture.LoadFromPath("./assets/textures/test_basic.jpg");

    Mesh plane = Plane(); // 假设你的静态工厂方法叫 CreateCube
    Transform mesh_transform;        // 立方体默认在原点

    Camera camera;
    camera.aspectRatio = 800.0f / 600.0f;
    camera.transform.setPosition(glm::vec3(0.0f, 2.0f, 5.0f)); // 相机往后退
    camera.transform.setRotation(glm::vec3(-15.0f, 0.0f, 0.0f)); // 俯视

    // --- 6. 极简渲染循环 ---
    while (!engine.shouldClose()) {
        // 清屏（颜色缓冲 + 深度缓冲）
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mesh_transform.rotate(glm::vec3(0.0f, 3.0f * engine.GetDeltaTime(), 0.0f));
        // 绑定 Shader 并传入 MVP 矩阵 以及贴图设置
        shader.Use();
        shader.setInt("ourTexture", 0);
        glm::mat4 mvp = camera.getProjectionMatrix() * camera.getViewMatrix() * mesh_transform.getMatrix();
        shader.setMat4("uModel", mvp);
        texture.Bind();
        

        // 绘制立方体
        plane.Draw(shader);

        // 交换缓冲并处理事件
        engine.Update();
    }


    return 0;
}