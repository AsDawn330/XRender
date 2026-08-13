#include "Transform.h"
#include "gtc/constants.hpp"
#include "gtc/matrix_transform.hpp"


//Constructor
Transform::Transform() : position(0.0f), rotation(0.0f), scale(1.0f)
{
}
Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
    : position(position), rotation(rotation), scale(scale)
{
}
//Rotation & Quaternion
glm::vec3 Transform::getRotation() const{
    if (eulerDirty)
    {
        rotation = glm::degrees(glm::eulerAngles(quaternion));
        eulerDirty = false;
    }
    return rotation;
}
glm::quat Transform::getQuaternion() const{
    if (quaternionDirty)
    {
        quaternion = glm::quat(glm::radians(rotation));
        quaternionDirty = false;
    }
    return quaternion;
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
    glm::mat4 rotate = glm::mat4_cast(quaternion);
    glm::mat4 scale_m = glm::scale(glm::mat4(1.0f), scale);

    matrix = translate * rotate * scale_m;
}
//Direction
glm::vec3 Transform::getForward() const
{
    if (quaternionDirty)
    {
        quaternion = glm::quat(glm::radians(rotation));
        quaternionDirty = false;
        eulerDirty = true;
    }
    return quaternion * glm::vec3(0.0f, 0.0f, -1.0f);
}
glm::vec3 Transform::getRight() const
{
    if (quaternionDirty)
    {
        quaternion = glm::quat(glm::radians(rotation));
        quaternionDirty = false;
        eulerDirty = true;
    }
    return quaternion * glm::vec3(1.0f, 0.0f, 0.0f);
}
glm::vec3 Transform::getUp() const
{
    if (quaternionDirty)
    {
        quaternion = glm::quat(glm::radians(rotation));
        quaternionDirty = false;
        eulerDirty = true;
    }
    return quaternion * glm::vec3(0.0f, 1.0f, 0.0f);
}
//Rotate
void Transform::rotate(const glm::vec3 deltaRotation)
{
    if (eulerDirty)
    {
        rotation = glm::degrees(glm::eulerAngles(quaternion));
        eulerDirty = false;
    }
    glm::quat delta = glm::quat(glm::radians(deltaRotation));
    rotate(delta);
}
void Transform::rotate(const glm::quat deltaQuaternion)
{
    if (quaternionDirty)
    {
        quaternion = glm::quat(glm::radians(rotation));
        quaternionDirty = false;
    }
    quaternion = deltaQuaternion * quaternion;
    dirty = true;
    quaternionDirty = true;
    eulerDirty = true;
}
