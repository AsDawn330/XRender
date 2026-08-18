#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "glm.hpp"
#include "gtc/quaternion.hpp"


class Transform
{
public:

    Transform();
    Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const { return scale; }
    glm::quat getQuaternion() const;
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
    mutable glm::vec3 rotation;  //Rotation is Degree like 0,90,180 if need Radian use a tranformer
    glm::vec3 scale;
    mutable glm::quat quaternion = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    mutable glm::mat4 matrix = glm::mat4(1.0f);
    mutable bool dirty = true;
    mutable bool quaternionDirty = true;
    mutable bool eulerDirty = false;
    void updateMatrix() const;
};

#endif
