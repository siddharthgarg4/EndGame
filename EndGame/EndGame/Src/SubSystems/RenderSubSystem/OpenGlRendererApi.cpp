//
//  OpenGlRendererApi.cpp
//  
//
//  Created by Siddharth on 19/06/20.
//

#include "OpenGlRendererApi.hpp"
#include <glad/glad.h>

namespace EndGame {
    void OpenGlRendererApi::init() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGlRendererApi::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGlRendererApi::setClearColor(const glm::vec4 &color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGlRendererApi::drawIndexed(const std::shared_ptr<VertexArray> &vertexArray) {
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }
    
    void OpenGlRendererApi::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(x, y, width, height);
    }
}