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
            OpenGlVertexBuffer(float *vertices, uint32_t size);
            ~OpenGlVertexBuffer();
            void bind() const override;
            void unbind() const override;
        private:
            uint32_t vertexBufferId;
    };

    class OpenGlIndexBuffer : public IndexBuffer {
        public:
            OpenGlIndexBuffer(uint32_t *indices, uint32_t count);
            ~OpenGlIndexBuffer();
            void bind() const override;
            void unbind() const override;
            uint32_t getCount() const override;
        private:
            uint32_t indexBufferId;
            uint32_t count;
    };
}

#endif
