//
//  RendererApi.hpp
//  
//
//  Created by Siddharth on 19/06/20.
//

#ifndef RendererApi_hpp
#define RendererApi_hpp
#include <glm/glm.hpp>
#include <EndGame/Src/EndGamePCH.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/VertexArray.h>

namespace EndGame {

    class RendererApi {
        public:
            enum class Api {
                None = 0,
                OpenGl = 1
            };
            virtual void init() = 0;
            virtual ~RendererApi() = default;
            virtual void clear() = 0;
            virtual void setClearColor(const glm::vec4 &color) = 0;
            virtual void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray) = 0;
            inline static Api getApi() { return api; }
        private:
            static Api api;
    };
}

#endif
