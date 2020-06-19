//
//  Renderer.hpp
//  
//
//  Created by Siddharth on 19/06/20.
//

#ifndef Renderer_hpp
#define Renderer_hpp
#include <EndGame/Src/SubSystems/RenderSubSystem/RendererApi.hpp>

namespace EndGame {

    class Renderer {
        public:
            static void beginScene();
            static void endScene();
            static void submit(const std::shared_ptr<VertexArray> &vertexArray);
            inline static RendererApi::Api getApi() { return RendererApi::getApi(); } 
    };
}

#endif
