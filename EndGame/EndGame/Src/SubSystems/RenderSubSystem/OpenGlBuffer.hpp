//
//  OpenGlBuffer.hpp
//  
//
//  Created by Siddharth on 06/06/20.
//

#ifndef OpenGlBuffer_hpp
#define OpenGlBuffer_hpp
#include <EndGame/Src/EndGamePCH.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/Buffer.h>

namespace EndGame {

    class OpenGlVertexBuffer : public VertexBuffer {
        public:
            OpenGlVertexBuffer(uint32_t size, float *vertices = nullptr);
            ~OpenGlVertexBuffer();
            void bind() const override;
            void unbind() const override;
            void setData(uint32_t size, const void *data) override;
            void setLayout(const BufferLayout &layout) override { vertexBufferLayout = layout; }
            const BufferLayout &getLayout() const override { return vertexBufferLayout; }
        private:
            uint32_t vertexBufferId;
            BufferLayout vertexBufferLayout;
    };

    class OpenGlIndexBuffer : public IndexBuffer {
        public:
            OpenGlIndexBuffer(uint32_t size, uint32_t *indices);
            ~OpenGlIndexBuffer();
            void bind() const override;
            void unbind() const override;
            uint32_t getSize() const override;
        private:
            uint32_t indexBufferId;
            uint32_t size;
    };
}

#endif
