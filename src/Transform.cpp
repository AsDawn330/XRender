#include "Transform.h"

//Constructor
Transform::Transform() : position(0.0f), rotation(0.0f), scale(1.0f)
{
}
Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
    : position(position), rotation(rotation), scale(scale)
{
}
//Matrix
const glm::mat4& Transform::getMatrix() const
{
    if (dirty)
    {
        updateMatrix();
        dirty = false;
    }
    return matrix;
}
void Transform::updateMatrix() const
{
    if (eulerDirty)
    {
        rotation = glm::degrees(glm::eulerAngles(quaternion));
        eulerDirty = false;
    }
    if (quaternionDirty)
    {
        quaternion = glm::quat(glm::radians(rotation));
        quaternionDirty = false;
    }

    glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotate = glm::toMat4(quaternion);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), scale);

    matrix = translate * rotate * scale;
}
//Direction
glm::vec3 Transform::getForward() const
{
    return glm::vec3(quaternion * glm::vec3(0.0f, 0.0f, -1.0f));
}
glm::vec3 Transform::getRight() const
{
    return glm::vec3(quaternion * glm::vec3(1.0f, 0.0f, 0.0f));
}
glm::vec3 Transform::getUp() const
{
    return glm::vec3(quaternion * glm::vec3(0.0f, 1.0f, 0.0f));
}
//Rotate
void Transform::rotate(const glm::vec3 deltaRotation)
{
    if (eulerDirty)
    {
        rotation = glm::degrees(glm::eulerAngles(quaternion));
        eulerDirty = false;
    }
    rotation += deltaRotation;
    dirty = true;
    quaternionDirty = true;
}
void Transform::rotate(const glm::quat deltaQuaternion)
{
    if (quaternionDirty)
    {
        quaternion = glm::quat(glm::radians(rotation));
        quaternionDirty = false;
    }
    quaternion *= deltaQuaternion;
    dirty = true;
    quaternionDirty = true;
    eulerDirty = true;
}
