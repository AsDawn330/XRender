#include "Mesh.h"
#include "Shader.h"
#include "glad/glad.h"
#include <cstddef>


Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    this->vertices = vertices;
    this->indices = indices;
    setupMesh();
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}
void Mesh::Draw(const Shader& shader) const
{
    shader.Use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

Mesh Plane()
{   
    return Mesh(
        std::vector<Vertex>{
            Vertex(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec2(1.0f,0.0f)),
            Vertex(glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec2(0.0f,0.0f)),
            Vertex(glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec2(0.0f,1.0f)),
            Vertex(glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f,1.0f,0.0f), glm::vec2(1.0f,1.0f))
        },
        std::vector<unsigned int>{
            0, 1, 2,
            2, 3, 0
        }
    );
}
