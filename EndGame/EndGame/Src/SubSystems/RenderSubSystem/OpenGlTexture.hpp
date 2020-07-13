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
            OpenGlTexture2D(const uint32_t &width, const uint32_t &height, const void *data);
            ~OpenGlTexture2D();
            uint32_t getWidth() override { return width; };
            uint32_t getHeight() override { return height; }
            void bind(uint32_t slot = 0) override;
            void unbind() override;
            void setData(uint32_t size, void *data) override;
            bool operator==(const Texture &other) const override { return this->rendererId == ((OpenGlTexture2D &)other).rendererId; }
        private:
            uint32_t height, width;
            uint32_t internalFormat, dataFormat;
            uint32_t rendererId;
            std::string filepath;
            void setTextureFormatForChannels(const int &numChannels);
            uint32_t bytesPerPixelForFormat(const uint32_t &format);
    };
}

#endif
