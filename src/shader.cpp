#include "Shader.h"
#include "glad/glad.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>

Shader::Shader(const string &vertexPath, const string &fragmentPath): program(0)
{
    string vertexCode = ReadShaderFile(vertexPath);
    string fragmentCode = ReadShaderFile(fragmentPath);
    CompileAndLinkShader(vertexCode, fragmentCode);
}
Shader::~Shader()
{
    glDeleteProgram(program);
}
string Shader::ReadShaderFile(const string &path)
{
    ifstream file(path);
    if (file.is_open())
    {
        file.seekg(0, ios::end);
        size_t size = file.tellg();
        string result(size, '\0');
        file.seekg(0);
        file.read(&result[0], size);
        file.close();
        return result;
    }
    else
    {
        cout << "Failed to open shader file: " << path << endl;
    }
    return "";
}
void Shader::CompileAndLinkShader(const string &vertexCode, const string &fragmentCode)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char * vertexSourceCode = vertexCode.c_str();
    glShaderSource(vertexShader, 1, &vertexSourceCode, NULL);
    glCompileShader(vertexShader);
    GLint success;
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
        GLint logLength;
        glGetShaderiv(vertexShader,GL_INFO_LOG_LENGTH,&logLength);
        if(logLength > 0){
            vector<char> log(logLength);
            glGetShaderInfoLog(vertexShader,logLength,nullptr,log.data());
            cerr << "[Vertex Shader Compile Error] : " << log.data() << endl;
        }
        glDeleteShader(vertexShader);
        return;
    }

    GLuint fragmentShader = glad_glCreateShader(GL_FRAGMENT_SHADER);
    const char * fragmentSourceCode = fragmentCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSourceCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success){
        GLint logLength;
        glGetShaderiv(fragmentShader,GL_INFO_LOG_LENGTH,&logLength);
        if(logLength > 0){
            vector<char> log(logLength);
            glGetShaderInfoLog(fragmentShader,logLength,nullptr,log.data());
            cerr << "[Fragment Shader Compile Error] : " << log.data() << endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            vector<char> log(logLength);
            glGetProgramInfoLog(program, logLength, nullptr, log.data());
            cerr << "[Shader Link Error] : \r\n" << log.data() << endl;
        }
        glDeleteProgram(program);
        program = 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return;
}
void Shader::Use() const
{
    glUseProgram(program);
}
void Shader::setInt(const string &name, int value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}
void Shader::setFloat(const string &name, float value) const
{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}
void Shader::setVec3(const string &name, vec3 value) const
{
    glUniform3f(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z);
}
void Shader::setMat4(const string &name, mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
void Shader::setVec4(const string &name, vec4 value) const
{
    glUniform4f(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z, value.w);
}
void Shader::setBool(const string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}
