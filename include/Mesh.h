#ifndef MESH_H
#define MESH_H
#include "glm.hpp"
#include <vector>
class Shader;

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh
{
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    virtual~Mesh();
    void Draw(const Shader& shader) const;

    Mesh(const Mesh& other) = delete;
    Mesh& operator=(const Mesh& other) = delete;
private:
    void setupMesh();
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};





#endif
