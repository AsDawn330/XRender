#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

class Transform
{
public:

    Transform();
    Transform(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale);
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getRotation() const { return rotation; }
    glm::vec3 getScale() const { return scale; }
    glm::quat getQuaternion() const { return quaternion; }
    const glm::mat4& getMatrix() const;
    void setPosition(const glm::vec3 position) { this->position = position; dirty = true; }
    void setRotation(const glm::vec3 rotation) { this->rotation = rotation; dirty = true; quaternionDirty = true; eulerDirty = false; }
    void setScale(const glm::vec3 scale) { this->scale = scale; dirty = true; }
    void setQuaternion(const glm::quat quaternion) { this->quaternion = quaternion; dirty = true; eulerDirty = true; quaternionDirty = false; }
    
    glm::vec3 getForward() const;
    glm::vec3 getRight() const;
    glm::vec3 getUp() const;

    void rotate(const glm::vec3 deltaRotation);
    void rotate(const glm::quat deltaQuaternion);
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::quat quaternion;
    mutable glm::mat4 matrix;
    mutable bool dirty;
    mutable bool quaternionDirty = true;
    mutable bool eulerDirty = false;
    void updateMatrix() const;
};

#endif
