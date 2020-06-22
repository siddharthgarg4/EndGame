//
//  Renderer.hpp
//  
//
//  Created by Siddharth on 19/06/20.
//

#ifndef Renderer_hpp
#define Renderer_hpp
#include <EndGame/Src/SubSystems/RenderSubSystem/Shader.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/RendererApi.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/OrthographicCamera.hpp>

namespace EndGame {

    struct SceneData {
        glm::mat4 cameraViewProjection;
    };

    class Renderer {
        public:
            static void beginScene(OrthographicCamera &camera);
            static void endScene();
            static void submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray,
                const glm::mat4 &transform = glm::mat4(1.0f));
            inline static RendererApi::Api getApi() { return RendererApi::getApi(); } 
        private:
            static std::unique_ptr<SceneData> sceneData;
    };
}

#endif
