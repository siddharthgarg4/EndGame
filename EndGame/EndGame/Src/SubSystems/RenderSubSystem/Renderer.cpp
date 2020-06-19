//
//  Renderer.cpp
//  
//
//  Created by Siddharth on 19/06/20.
//

#include "Renderer.hpp"
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderCommand.h>

namespace EndGame {
    //temporary
    std::unique_ptr<RendererApi> RenderCommand::rendererApi = RenderApiFactory::createRendererApi();

    void Renderer::beginScene() {}

    void Renderer::endScene() {}

    void Renderer::submit(const std::shared_ptr<VertexArray> &vertexArray) {
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }
}
