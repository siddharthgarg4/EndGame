//
//  OpenGlShader.hpp
//  EndGame
//
//  Created by Siddharth on 06/06/20.
//

#ifndef OpenGlShader_hpp
#define OpenGlShader_hpp
#include <EndGame/Src/EndGamePCH.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/Shader.hpp>

namespace EndGame {

    struct OpenGlDataType {
        uint32_t type;
        uint32_t count;
        uint32_t size;
    };

    enum ShaderType {
         unknown, fragment, vertex
    };

    class OpenGlShader : public Shader {
        public:
            static OpenGlDataType shaderDataTypeToOpenGlDataType(ShaderDataType type);
            OpenGlShader(const std::string &name, std::string &vertexSource, std::string &fragmentSource);
            OpenGlShader(const std::string &filepath);
            ~OpenGlShader();
            void bind() const override;
            void unbind() const override;
            const std::string &getName() const override { return name; }
            //overloaded uniform functions
            void uploadUniform(const std::string &name, const int &data) override;
            void uploadUniform(const std::string &name, const float &data) override;
            void uploadUniform(const std::string &name, const glm::vec2 &data) override;
            void uploadUniform(const std::string &name, const glm::vec3 &data) override;
            void uploadUniform(const std::string &name, const glm::vec4 &data) override;
            void uploadUniform(const std::string &name, const glm::mat3 &data) override;
            void uploadUniform(const std::string &name, const glm::mat4 &data) override;
        private:
            uint32_t rendererId;
            std::string name;
            std::unordered_map<ShaderType, std::string> preprocessShaderSource(std::string &shaderSourceString);
            //map includes opengl glenum type linked with the source code
            void compileShader(const std::unordered_map<ShaderType, std::string> &shaderSources);
    };
}

#endif
