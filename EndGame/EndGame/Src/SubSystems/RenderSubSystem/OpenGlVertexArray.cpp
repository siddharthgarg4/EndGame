//
//  OpenGlVertexArray.cpp
//  
//
//  Created by Siddharth on 09/06/20.
//

#include "OpenGlVertexArray.hpp"
#include <glad/glad.h>
#include <EndGame/Src/Core.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/OpenGlShader.hpp>

namespace EndGame {

    OpenGlVertexArray::OpenGlVertexArray() {
        glGenVertexArrays(1, &vertexArrayId);
    }

    OpenGlVertexArray::~OpenGlVertexArray() {
        glDeleteVertexArrays(1, &vertexArrayId);
    }

    void OpenGlVertexArray::bind() const {
        glBindVertexArray(vertexArrayId);
    }

    void OpenGlVertexArray::unbind() const {
        glBindVertexArray(0);
    }

    void OpenGlVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer, bool shouldUnbindAfterCall) {
        const auto &bufferLayout = vertexBuffer->getLayout();
        EG_ENGINE_ASSERT(bufferLayout.getLayouts().size(), "Vertex Buffer has no layout!");
        //binding vertex array and buffer
        glBindVertexArray(vertexArrayId);
        vertexBuffer->bind();
        //binding layout and vertex buffer to the vertex array
        uint32_t index = 0;
        for (const auto &layout : bufferLayout) {
            glEnableVertexAttribArray(index);
            //converting EndGame type to OpenGl Type containing size and count of elements
            OpenGlDataType openGlDataType = OpenGlShader::shaderDataTypeToOpenGlDataType(layout.type);
            glVertexAttribPointer(index, openGlDataType.count, openGlDataType.type,
                layout.normalized ? GL_TRUE : GL_FALSE, bufferLayout.getStride(),
                //converting layout.offset to required const void *
                reinterpret_cast<const void *>((intptr_t)layout.offset));
            index++;
        }
        vertexBuffers.push_back(vertexBuffer);
        //unbinding array if requested by client
        if (shouldUnbindAfterCall) {
            glBindVertexArray(0);
            vertexBuffer->unbind();
        }
    }

    void OpenGlVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer, bool shouldUnbindAfterCall) {
        glBindVertexArray(vertexArrayId);
        indexBuffer->bind();
        //assigning array object as the variable
        this->indexBuffer = indexBuffer;
        //unbinding array if requested by client
        if (shouldUnbindAfterCall) {
            glBindVertexArray(0);
            indexBuffer->unbind();
        }
    }
}
