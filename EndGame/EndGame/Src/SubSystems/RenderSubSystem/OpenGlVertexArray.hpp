//
//  OpenGlVertexArray.hpp
//  
//
//  Created by Siddharth on 09/06/20.
//

#ifndef OpenGlVertexArray_hpp
#define OpenGlVertexArray_hpp
#include <EndGame/Src/SubSystems/RenderSubSystem/VertexArray.h>

namespace EndGame {

    class OpenGlVertexArray : public VertexArray {
        public:
            OpenGlVertexArray();
            ~OpenGlVertexArray();
            void bind() const override;
            void unbind() const override;
            void addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer, bool shouldUnbindAfterCall = true) override;
            void setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer, bool shouldUnbindAfterCall = true) override;
            virtual const std::vector<std::shared_ptr<VertexBuffer>> &getVertextBuffers() const override { return vertexBuffers; }
            virtual const std::shared_ptr<IndexBuffer> &getIndexBuffer() const override { return indexBuffer; }
        private:
            uint32_t vertexArrayId;
            uint32_t vertexBufferIndex = 0;
            std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
            std::shared_ptr<IndexBuffer> indexBuffer;
    };
}

#endif
