#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Transform.h"

enum class ProjectionType{
    PERSPECTIVE,
    ORTHOGRAPHIC
};

class Camera{
public:
    Transform transform;

    ProjectionType projectionType;
    float orthoSize;
    float fov;

    float nearClip;
    float farClip;
    float aspectRatio;

    glm::vec3 backgroundColor;

    Camera() 
    : Camera(Transform(), 45.0f, 0.1f, 100.0f, 
             ProjectionType::PERSPECTIVE, 16.0f / 9.0f, 5.0f, 
             glm::vec3(0.1f, 0.1f, 0.1f)) 
    {}

    // 全参构造函数：使用成员初始化列表，高效且清晰
    Camera(Transform transform, float fov, float nearClip, float farClip, 
                ProjectionType projectionType, float aspectRatio, float orthoSize, 
                glm::vec3 backgroundColor)
        : transform(transform),
        fov(fov),
        nearClip(nearClip),
        farClip(farClip),
        projectionType(projectionType),
        aspectRatio(aspectRatio),
        orthoSize(orthoSize),
        backgroundColor(backgroundColor)
    {}

    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;
};

#endif
