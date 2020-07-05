//
//  OpenGlTexture.hpp
//  
//
//  Created by Siddharth on 04/07/20.
//

#ifndef OpenGlTexture_h
#define OpenGlTexture_h
#include <EndGame/Src/SubSystems/RenderSubSystem/Texture.h>
#include <EndGame/Src/EndGamePCH.hpp>

namespace EndGame {

    class OpenGlTexture2D : public Texture2D {
        public:
            OpenGlTexture2D(const std::string &filepath);
            virtual ~OpenGlTexture2D();
            virtual uint32_t getWidth() override { return width; };
            virtual uint32_t getHeight() override { return height; }
            virtual void bind(uint32_t slot = 0) override;
            virtual void unbind() override;
        private:
            uint32_t height;
            uint32_t width;
            uint32_t rendererId;
            std::string filepath;
    };
}

#endif