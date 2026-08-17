#include "Camera.h"


glm::mat4 Camera::getProjectionMatrix() const
{
    if (projectionType == ProjectionType::PERSPECTIVE)
    {
        return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
    }
    else
    {
        float HalfHeight = orthoSize;
        float HalfWidth = orthoSize * aspectRatio;


        return glm::ortho(-HalfWidth, HalfWidth, -HalfHeight, HalfHeight, nearClip, farClip);
    }
}


glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(transform.getPosition(), transform.getPosition() + transform.getForward(), transform.getUp());
}
