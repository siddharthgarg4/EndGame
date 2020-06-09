//
//  VertexArray.h
//  
//
//  Created by Siddharth on 09/06/20.
//

#ifndef VertexArray_h
#define VertexArray_h
#include <EndGame/Src/EndGamePCH.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/Buffer.h>

namespace EndGame {

    class VertexArray {
        public:
            //constructor simply creates and does not bind 
            //if bind is needed either explicitly bind or add vertex/index buffer which handles binding
            virtual ~VertexArray() {}
            virtual void bind() const = 0;
            virtual void unbind() const = 0;
            //can set shouldUnbindAfterCall to true/false to decide if buffer/array are bound/unbound after call
            virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer, bool shouldUnbindAfterCall = true) = 0;
            virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer, bool shouldUnbindAfterCall = true) = 0;
            //getters
            virtual const std::vector<std::shared_ptr<VertexBuffer>> &getVertextBuffers() const = 0;
            virtual const std::shared_ptr<IndexBuffer> &getIndexBuffer() const = 0;
    };
}

#endif
