//
//  OpenGlBuffer.cpp
//  
//
//  Created by Siddharth on 06/06/20.
//

#include "OpenGlBuffer.hpp"
#include <glad/glad.h>
#include <EndGame/Src/Core.h>

namespace EndGame {
    //MARK: Vertex Buffer Implementation
    OpenGlVertexBuffer::OpenGlVertexBuffer(uint32_t size, float *vertices) {
        glGenBuffers(1, &vertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
        if (vertices == nullptr) {
            //dynamic draw
            glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
        } else {
            //static draw
            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    OpenGlVertexBuffer::~OpenGlVertexBuffer() {
        glDeleteBuffers(1, &vertexBufferId);
    }

    void OpenGlVertexBuffer::bind() const {
       glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    } 

    void OpenGlVertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    } 

    void OpenGlVertexBuffer::setData(uint32_t size, const void *data) {
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }
    //MARK: Index Buffer Implementation
    OpenGlIndexBuffer::OpenGlIndexBuffer(uint32_t size, uint32_t *indices) : size(size) {
        glGenBuffers(1, &indexBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    OpenGlIndexBuffer::~OpenGlIndexBuffer() {
        glDeleteBuffers(1, &indexBufferId);
    }

    void OpenGlIndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    }

    void OpenGlIndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t OpenGlIndexBuffer::getSize() const {
        return size;
    }
}
