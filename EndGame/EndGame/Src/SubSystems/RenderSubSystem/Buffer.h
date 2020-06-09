//
//  Buffer.h
//  
//
//  Created by Siddharth on 06/06/20.
//

#ifndef Buffer_h
#define Buffer_h
#include <EndGame/Src/EndGamePCH.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/Shader.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderApiUtilities.hpp>

namespace EndGame {

    struct BufferLayoutElement {
        std::string name;
        ShaderDataType type;
        uint32_t size;
        uint32_t offset;
        bool normalized;
        BufferLayoutElement(ShaderDataType type, const std::string &name, bool normalized = false) : 
            name(name), type(type), size(RenderApiUtilities::shaderDataTypeSize(type)), offset(0), normalized(normalized) {}
    };

    class BufferLayout {
        public:
            BufferLayout() {}
            BufferLayout(const std::initializer_list<BufferLayoutElement>& layouts) : layouts(layouts) { calculateStrideAndOffset(); }
            inline uint32_t getStride() const { return stride; }
            inline const std::vector<BufferLayoutElement> getLayouts() const { return layouts; }
            std::vector<BufferLayoutElement>::iterator begin() { return layouts.begin(); }
            std::vector<BufferLayoutElement>::iterator end() { return layouts.end(); }
            std::vector<BufferLayoutElement>::const_iterator begin() const { return layouts.begin(); }
            std::vector<BufferLayoutElement>::const_iterator end() const { return layouts.end(); }
        private:
            void calculateStrideAndOffset() {
                //in case of recalculation
                stride = 0;
                for (auto& layout: layouts) {
                    layout.offset = stride;
                    stride += layout.size;
                }
            }
            std::vector<BufferLayoutElement> layouts;
            uint32_t stride = 0;
    };

    class VertexBuffer {
        public:
            //creating vertex buffer will not bind to currently bound vertex array
            //the returned buffer will not be in bound state
            virtual ~VertexBuffer() {}
            virtual void bind() const = 0;
            virtual void unbind() const = 0;
            virtual void setLayout(const BufferLayout &layout) = 0;
            virtual const BufferLayout &getLayout() const = 0;
    };

    class IndexBuffer {
        public:
            //creating index buffer will bind to currently bound vertex array
            //the returned buffer will not be in bound state
            virtual ~IndexBuffer() {}
            virtual void bind() const = 0;
            virtual void unbind() const = 0;
            virtual uint32_t getCount() const = 0;
    };
}

#endif
