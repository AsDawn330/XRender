#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "glm.hpp"
using namespace std;
using namespace glm;

class Shader
{
public:
    Shader(const string &vertexPath, const string &fragmentPath);
    ~Shader();
    void Use() const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;
    void setBool(const string &name, bool value) const;
    void setVec3(const string &name, vec3 value) const;
    void setVec4(const string &name, vec4 value) const;
    void setMat4(const string &name, mat4 value) const;
private:
    unsigned int program;
    string ReadShaderFile(const string &path);
    void CompileAndLinkShader(const string &vertexCode, const string &fragmentCode);

};
#endif
