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

    class OpenGlShader : public Shader {
        public:
            OpenGlShader(std::string &vertexSource, std::string &fragmentSource);
            ~OpenGlShader();
            void bind() const override;
            void unbind() const override;
        private:
            uint32_t rendererId;
    };
}

#endif
