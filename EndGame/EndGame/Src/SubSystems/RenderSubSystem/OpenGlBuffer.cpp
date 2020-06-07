//
//  OpenGlBuffer.cpp
//  
//
//  Created by Siddharth on 06/06/20.
//

#include "OpenGlBuffer.hpp"
#include <EndGame/Src/Core.h>
#include <glad/glad.h>

namespace EndGame {
    //MARK: Vertex Buffer Implementation
    OpenGlVertexBuffer::OpenGlVertexBuffer(float *vertices, uint32_t size) {
        glGenBuffers(1, &vertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
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
    //MARK: Index Buffer Implementation
    OpenGlIndexBuffer::OpenGlIndexBuffer(uint32_t *indices, uint32_t count) : count(count) {
        glGenBuffers(1, &indexBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
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

    uint32_t OpenGlIndexBuffer::getCount() const {
        return count;
    }
}
