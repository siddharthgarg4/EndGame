//
//  OpenGlShader.hpp
//  EndGame
//
//  Created by Siddharth on 06/06/20.
//

#ifndef OpenGlShader_hpp
#define OpenGlShader_hpp
#include <EndGame/Src/EndGamePCH.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/Shader.h>

namespace EndGame {

    struct OpenGlDataType {
        uint32_t type;
        uint32_t count;
        uint32_t size;
    };

    class OpenGlShader : public Shader {
        public:
            static OpenGlDataType shaderDataTypeToOpenGlDataType(ShaderDataType type);
            OpenGlShader(std::string &vertexSource, std::string &fragmentSource);
            ~OpenGlShader();
            void bind() const override;
            void unbind() const override;
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
    };
}

#endif
