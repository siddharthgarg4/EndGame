//
//  Buffer.h
//  
//
//  Created by Siddharth on 06/06/20.
//

#ifndef Buffer_h
#define Buffer_h
#include <EndGame/Src/EndGamePCH.hpp>

namespace EndGame {

    class VertexBuffer {
        public:
            virtual ~VertexBuffer() {}
            virtual void bind() const = 0;
            virtual void unbind() const = 0;
    };

    class IndexBuffer {
        public:
            virtual ~IndexBuffer() {}
            virtual void bind() const = 0;
            virtual void unbind() const = 0;
            virtual uint32_t getCount() const = 0;
    };
}

#endif
