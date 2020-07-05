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
        EG_ENGINE_ASSERT(imageData, "Failed to load image!");
        this->height = height;
        this->width = width;
        glGenTextures(1, &rendererId);
        //binding texture
        glBindTexture(GL_TEXTURE_2D, rendererId);
        //creating image data buffer
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        //setting parameters for magnification and minimization
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //freeing image data and unbinding texture
        stbi_image_free(imageData);
        glBindTexture(GL_TEXTURE_2D, 0);
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
}
