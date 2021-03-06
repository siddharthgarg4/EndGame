//
//  Renderer.cpp
//  
//
//  Created by Siddharth on 19/06/20.
//

#include "Renderer.hpp"
#include <EndGame/Src/SubSystems/RenderSubSystem/Renderer2D.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderCommand.h>

namespace EndGame {
    //temporary
    std::unique_ptr<RendererApi> RenderCommand::rendererApi = RenderApiFactory::createRendererApi();
    std::unique_ptr<SceneData> Renderer::sceneData = std::make_unique<SceneData>();

    void Renderer::init() {
        RenderCommand::init();
        Renderer2D::init();
    }

    void Renderer::beginScene(const OrthographicCamera &camera) {
        //need to store this data since multiple submit calls can be made 
        //3d renderer has multiple shaders unlike 2d
        sceneData->cameraViewProjection = camera.getViewProjectionMatrix();
    }

    void Renderer::endScene() {}


    void Renderer::onWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::setViewport(0, 0, width, height);
    }

    void Renderer::submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform) {
        shader->bind();
        shader->uploadUniform("u_viewProjection", sceneData->cameraViewProjection);
        shader->uploadUniform("u_transform", transform);
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }
}
