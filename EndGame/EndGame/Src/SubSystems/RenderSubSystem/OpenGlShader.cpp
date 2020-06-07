//
//  OpenGlShader.cpp
//  EndGame
//
//  Created by Siddharth on 06/06/20.
//

#include "OpenGlShader.hpp"
#include <EndGame/Src/Core.h>
#include <glad/glad.h>

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
}