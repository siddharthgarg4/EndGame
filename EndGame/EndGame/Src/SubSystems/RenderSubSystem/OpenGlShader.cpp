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

    static GLenum shaderTypeToOpenGlType(ShaderType type) {
        switch(type) {
            case fragment:
                return GL_FRAGMENT_SHADER;
            case vertex:
                return GL_VERTEX_SHADER;
            case unknown:
                break;
        }
        EG_ENGINE_ASSERT(false, "Unknown ShaderType!");
        return 0;
    }

    static ShaderType shaderTypeFromString(std::string type) {
        if (type == "vertex") {
            return ShaderType::vertex;
        } else if (type == "fragment" || type == "pixel") {
            return ShaderType::fragment;
        }
        EG_ENGINE_ASSERT(false, "Unknown ShaderType!");
        return ShaderType::unknown;
    }

    OpenGlShader::OpenGlShader(std::string &vertexSource, std::string &fragmentSource) {
        std::unordered_map<ShaderType, std::string> shaderSources;
        shaderSources[ShaderType::vertex] = vertexSource;
        shaderSources[ShaderType::fragment] = fragmentSource;
        compileShader(shaderSources);
    }

    OpenGlShader::OpenGlShader(const std::string &filepath) {
        std::string fileContents = readContentsFile(filepath);
        std::unordered_map<ShaderType, std::string> shaderSources = preprocessShaderSource(fileContents);
        compileShader(shaderSources);
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

    void OpenGlShader::uploadUniform(const std::string &name, const int &data) {
        GLint uniformLocation = glGetUniformLocation(rendererId, name.c_str());
        glUniform1i(uniformLocation, data);
    }

    void OpenGlShader::uploadUniform(const std::string &name, const float &data) {
        GLint uniformLocation = glGetUniformLocation(rendererId, name.c_str());
        glUniform1f(uniformLocation, data);
    }

    void OpenGlShader::uploadUniform(const std::string &name, const glm::vec2 &data) {
        GLint uniformLocation = glGetUniformLocation(rendererId, name.c_str());
        glUniform2f(uniformLocation, data.x, data.y);
    }

    void OpenGlShader::uploadUniform(const std::string &name, const glm::vec3 &data) {
        GLint uniformLocation = glGetUniformLocation(rendererId, name.c_str());
        glUniform3f(uniformLocation, data.x, data.y, data.z);
    }

    void OpenGlShader::uploadUniform(const std::string &name, const glm::vec4 &data) {
        GLint uniformLocation = glGetUniformLocation(rendererId, name.c_str());
        glUniform4f(uniformLocation, data.x, data.y, data.z, data.w);
    }

    void OpenGlShader::uploadUniform(const std::string &name, const glm::mat3 &data) {
        GLint uniformLocation = glGetUniformLocation(rendererId, name.c_str());
        glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(data));
    }

    void OpenGlShader::uploadUniform(const std::string &name, const glm::mat4 &data) {
        GLint uniformLocation = glGetUniformLocation(rendererId, name.c_str());
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(data));
    }

    //MARK: OpenGl Shader Compilation
    std::string OpenGlShader::readContentsFile(const std::string &filepath) {
        std::ifstream input(filepath, std::ios::in | std::ios::binary);
        std::string fileContents;
        std::cout << input.rdbuf();
        if (input) {
            input.seekg(0, std::ios::end);
            fileContents.resize(input.tellg());
            input.seekg(0, std::ios::beg);
            input.read(&fileContents[0], fileContents.size());
            input.close();
        } else {
            EG_ENGINE_ERROR("Could not open file '{0}'", filepath);
        }
        return fileContents;
    }

    std::unordered_map<ShaderType, std::string> OpenGlShader::preprocessShaderSource(std::string &shaderSourceString) {
        std::unordered_map<ShaderType, std::string> shaderSources;
        std::string token = "#type";
        const size_t typeTokenLength = token.length();
        size_t startShader = shaderSourceString.find(token, 0);
        while(startShader != std::string::npos) {
            size_t endShaderType = shaderSourceString.find_first_of("\r\n", startShader);
            size_t startShaderType = typeTokenLength + startShader + 1;
            size_t startShaderSource = shaderSourceString.find_first_not_of("\r\n", endShaderType);
            //if true means no error
            bool shaderSyntaxError = endShaderType != std::string::npos && startShaderType != std::string::npos;
            EG_ENGINE_ASSERT(shaderSyntaxError, "Shader File Sytax Error!");
            std::string stringShaderType = shaderSourceString.substr(startShaderType, endShaderType - startShaderType);
            ShaderType shaderType = shaderTypeFromString(stringShaderType);
            EG_ENGINE_ASSERT(shaderType, "Shader File Sytax Error!");
            startShader = shaderSourceString.find(token, startShaderSource);
            //check this
            shaderSources[shaderType] = shaderSourceString.substr(startShaderSource, startShader - 
                (startShaderSource == std::string::npos ? shaderSourceString.size() - 1 : startShaderSource));
        }
        return shaderSources;
    }

    void OpenGlShader::compileShader(const std::unordered_map<ShaderType, std::string> &shaderSources) {
        GLuint program = glCreateProgram();
        std::vector<GLenum> glShaderIds;
        glShaderIds.reserve(shaderSources.size());
        //compiling and attaching all the shaders
        for (auto &&[shaderType, shaderSource]: shaderSources) {
            GLenum openGlShaderType = shaderTypeToOpenGlType(shaderType);
            const GLchar* constShaderSource = shaderSource.c_str();
            GLuint shader = glCreateShader(openGlShaderType);
            glShaderSource(shader, 1, &constShaderSource, 0);
            glCompileShader(shader);
            GLint shaderDidCompile = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderDidCompile);
            if (shaderDidCompile == GL_FALSE) {
                //shader did not compile
                GLint logLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
                std::vector<GLchar> infoLog(logLength);
                glGetShaderInfoLog(shader, logLength, &logLength, &infoLog[0]);
                glDeleteShader(shader);
                EG_ENGINE_ERROR("{0}", infoLog.data());
                EG_ENGINE_ASSERT(false, "OpenGl Shader failed to compile");
                for (auto shaderId: glShaderIds) {
                    //current shader compilation failed so delete all previous shaders
                    glDeleteShader(shaderId);
                }
                glDeleteProgram(program);
                return;
            }
            glAttachShader(program, shader);
            glShaderIds.push_back(shader);
        }
        //linking the program
        glLinkProgram(program);
        GLint programDidLink = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &programDidLink);
        if (programDidLink == GL_FALSE) {
            //program did not link
            GLint logLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<GLchar> infoLog(logLength);
            glGetProgramInfoLog(program, logLength, &logLength, &infoLog[0]);
            glDeleteProgram(program);
            for (auto shaderId: glShaderIds) {
                glDeleteShader(shaderId);
            }
            EG_ENGINE_ERROR("{0}", infoLog.data());
            EG_ENGINE_ASSERT(false, "OpenGl Program failed to link");
            return;
        }
        for (auto shaderId: glShaderIds) {
            glDetachShader(program, shaderId);
        }
        //successfully compiled/linked the program
        rendererId = program;
    }
}
