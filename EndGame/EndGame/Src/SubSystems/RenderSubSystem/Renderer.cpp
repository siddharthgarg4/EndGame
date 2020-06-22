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
    std::unique_ptr<SceneData> Renderer::sceneData = std::make_unique<SceneData>();

    void Renderer::beginScene(OrthographicCamera &camera) {
        sceneData->cameraViewProjection = camera.getViewProjectionMatrix();
    }

    void Renderer::endScene() {}

    void Renderer::submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform) {
        shader->bind();
        shader->uploadUniformMat4("u_viewProjection", sceneData->cameraViewProjection);
        shader->uploadUniformMat4("u_transform", transform);
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }
}
