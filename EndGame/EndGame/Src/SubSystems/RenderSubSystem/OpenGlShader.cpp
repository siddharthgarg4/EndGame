//
//  OpenGlShader.cpp
//  EndGame
//
//  Created by Siddharth on 06/06/20.
//

#include "OpenGlShader.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <EndGame/Src/Core.h>

namespace EndGame {

    OpenGlShader::OpenGlShader(std::string &vertexSource, std::string &fragmentSource) {
        GLint shaderDidCompile = 0;
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* vertexShaderSource = vertexSource.c_str();
        glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderDidCompile);
        if (shaderDidCompile == GL_FALSE) {
            //vertex shader did not compile
            GLint logLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<GLchar> infoLog(logLength);
            glGetShaderInfoLog(vertexShader, logLength, &logLength, &infoLog[0]);
            glDeleteShader(vertexShader);
            EG_ENGINE_ERROR("{0}", infoLog.data());
            EG_ENGINE_ASSERT(false, "OpenGl Vertex Shader failed to compile");
            return;
        }
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const GLchar* fragmentShaderSource = fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shaderDidCompile);
        if (shaderDidCompile == GL_FALSE) {
            //fragment shader did not compile
            GLint logLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<GLchar> infoLog(logLength);
            glGetShaderInfoLog(fragmentShader, logLength, &logLength, &infoLog[0]);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            EG_ENGINE_ERROR("{0}", infoLog.data());
            EG_ENGINE_ASSERT(false, "OpenGl Fragment Shader failed to compile");
            return;
        }
        rendererId = glCreateProgram();
        glAttachShader(rendererId, vertexShader);
        glAttachShader(rendererId, fragmentShader);
        glLinkProgram(rendererId);
        GLint programDidLink = 0;
        glGetProgramiv(rendererId, GL_LINK_STATUS, &programDidLink);
        if (programDidLink == GL_FALSE) {
            //program did not link
            GLint logLength = 0;
            glGetProgramiv(rendererId, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<GLchar> infoLog(logLength);
            glGetProgramInfoLog(rendererId, logLength, &logLength, &infoLog[0]);
            glDeleteProgram(rendererId);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            EG_ENGINE_ERROR("{0}", infoLog.data());
            EG_ENGINE_ASSERT(false, "OpenGl Program failed to link");
            return;
        }
        glDetachShader(rendererId, vertexShader);
        glDetachShader(rendererId, fragmentShader);
    }

    OpenGlShader::~OpenGlShader() {
        glDeleteProgram(rendererId);
    }

    void OpenGlShader::bind() const {
        glUseProgram(rendererId);
    }

    void OpenGlShader::unbind() const {
        glUseProgram(0);
    }

    void OpenGlShader::uploadUniformMat4(const std::string &name, const glm::mat4 &matrix) {
        GLint uniformLocation = glGetUniformLocation(rendererId, name.c_str());
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    OpenGlDataType OpenGlShader::shaderDataTypeToOpenGlDataType(ShaderDataType type) {
        switch(type) {
            case ShaderDataType::None: {
                EG_ENGINE_ASSERT(false, "None ShaderDataType not handled!");
                return OpenGlDataType{0, 0, 0};
            }
            case ShaderDataType::Bool : {
                return OpenGlDataType{GL_BOOL, 1, 1};
            } 
            case ShaderDataType::Mat3 : {
                return OpenGlDataType{GL_FLOAT, 3 * 3, 4 * 3 * 3};
            } 
            case ShaderDataType::Mat4 : {
                return OpenGlDataType{GL_FLOAT, 4 * 4, 4 * 4 * 4};
            } 
            case ShaderDataType::Int : {
                return OpenGlDataType{GL_INT, 1, 4};
            } 
            case ShaderDataType::Int2 : {
                return OpenGlDataType{GL_INT, 2, 4 * 2};
            } 
            case ShaderDataType::Int3 : {
                return OpenGlDataType{GL_INT, 3, 4 * 3};
            } 
            case ShaderDataType::Int4 : {
                return OpenGlDataType{GL_INT, 4, 4 * 4};
            } 
            case ShaderDataType::Float : {
                return OpenGlDataType{GL_FLOAT, 1, 4};
            } 
            case ShaderDataType::Float2 : {
                return OpenGlDataType{GL_FLOAT, 2, 4 * 2};
            } 
            case ShaderDataType::Float3 : {
                return OpenGlDataType{GL_FLOAT, 3, 4 * 3};
            } 
            case ShaderDataType::Float4 : {
                return OpenGlDataType{GL_FLOAT, 4, 4 * 4};
            } 
        }
        EG_ENGINE_ASSERT(false, "Unknown ShaderDataType!");
        return OpenGlDataType{0, 0, 0};
    }
}
