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
            OpenGlShader(std::string &vertexSource, std::string &fragmentSource);
            ~OpenGlShader();
            void bind() const override;
            void unbind() const override;
            void uploadUniformMat4(const std::string &name, const glm::mat4 &matrix) override;
            static OpenGlDataType shaderDataTypeToOpenGlDataType(ShaderDataType type);
        private:
            uint32_t rendererId;
    };
}

#endif
