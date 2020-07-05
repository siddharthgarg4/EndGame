//
//  OpenGlRendererApi.hpp
//  
//
//  Created by Siddharth on 19/06/20.
//

#ifndef OpenGlRendererApi_hpp
#define OpenGlRendererApi_hpp
#include <EndGame/Src/SubSystems/RenderSubSystem/RendererApi.hpp>

namespace EndGame {

    class OpenGlRendererApi : public RendererApi {
        public:
            void init() override;
            ~OpenGlRendererApi() = default;
            void clear() override;
            void setClearColor(const glm::vec4 &color) override;
            void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray) override;
    };
}

#endif
