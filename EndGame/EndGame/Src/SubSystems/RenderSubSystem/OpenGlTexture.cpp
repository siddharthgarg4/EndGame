//
//  OpenGlTexture.cpp
//  
//
//  Created by Siddharth on 04/07/20.
//

#include "OpenGlTexture.hpp"
#include <stb_image.h>
#include <glad/glad.h>
#include <EndGame/Src/Core.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderApiUtilities.hpp>

namespace EndGame {
    OpenGlTexture2D::OpenGlTexture2D(const std::string &filepath) : filepath(filepath) {
        int width, height, channels;
        std::string filepathRelativeToExe = RenderApiUtilities::filepathRelativeToExe(filepath);
        stbi_set_flip_vertically_on_load(1);
        stbi_uc *imageData = stbi_load(filepathRelativeToExe.c_str(), &width, &height, &channels, 0);
        EG_ENGINE_ASSERT(imageData!=NULL, stbi_failure_reason());
        //initializing class members
        this->height = height;
        this->width = width;
        //setting data format based on channels
        setTextureFormatForChannels(channels);
        //texture start
        glGenTextures(1, &rendererId);
        //binding texture
        glBindTexture(GL_TEXTURE_2D, rendererId);
        //creating image data buffer
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, this->width, this->height, 0, dataFormat, GL_UNSIGNED_BYTE, imageData);
        //setting parameters for magnification and minimization
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //freeing image data and unbinding texture
        stbi_image_free(imageData);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGlTexture2D::OpenGlTexture2D(const uint32_t &width, const uint32_t &height, const void *data) : width(width), height(height) {
        //default rgba
        setTextureFormatForChannels(4);
        glGenTextures(1, &rendererId);
        glBindTexture(GL_TEXTURE_2D, rendererId);
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGlTexture2D::setTextureFormatForChannels(const int &numChannels) {
        switch(numChannels) {
            case 1:
                internalFormat = GL_RED;
                dataFormat = GL_R8;
                break;
            case 2:
                internalFormat = GL_RG;
                dataFormat = GL_RG8;
                break;
            case 3:
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
                break;
            case 4:
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
                break;
            default:
                EG_ENGINE_ASSERT(false, "Image format not yet supported!");
                break;
        }
    }

    uint32_t OpenGlTexture2D::bytesPerPixelForFormat(const uint32_t &format) {
        switch(format) {
            case GL_RED: case GL_R8:
                return 1;
            case GL_RG: case GL_RG8:
                return 2;
            case GL_RGB8: case GL_RGB:
                return 3;
            case GL_RGBA8: case GL_RGBA:
                return 4;
            default:
                EG_ENGINE_ASSERT(false, "Image format not yet supported!");
                break;
        }
        return 0;
    }

    OpenGlTexture2D::~OpenGlTexture2D() {
        glDeleteTextures(1, &rendererId);
    }

    void OpenGlTexture2D::bind(uint32_t slot) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, rendererId);
    }

    void OpenGlTexture2D::unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGlTexture2D::setData(uint32_t size, void *data) {
        EG_ENGINE_ASSERT(size == width * height * bytesPerPixelForFormat(dataFormat), "Data must span entire texture!");
        glBindTexture(GL_TEXTURE_2D, rendererId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
