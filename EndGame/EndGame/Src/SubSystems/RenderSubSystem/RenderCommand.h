//
//  RenderCommand.h
//  
//
//  Created by Siddharth on 19/06/20.
//

#ifndef RenderCommand_h
#define RenderCommand_h
#include <EndGame/Src/SubSystems/RenderSubSystem/RendererApi.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderApiFactory.hpp>

namespace EndGame {

    class RenderCommand {
        public:
            inline static void init() { rendererApi->init(); }
            inline static void clear() { rendererApi->clear(); }
            inline static void setClearColor(const glm::vec4 &color) { rendererApi->setClearColor(color); }
            inline static void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray, uint32_t count = 0) { rendererApi->drawIndexed(vertexArray, count); }
            inline static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { rendererApi->setViewport(x, y, width, height); }
        private:
            //gets created in renderer.cpp
            static std::unique_ptr<RendererApi> rendererApi;
    };
}

#endif
