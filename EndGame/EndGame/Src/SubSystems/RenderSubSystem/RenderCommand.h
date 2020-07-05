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
            inline static void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray) { rendererApi->drawIndexed(vertexArray); }
        private:
            //gets created in renderer.cpp
            static std::unique_ptr<RendererApi> rendererApi;
    };
}

#endif
