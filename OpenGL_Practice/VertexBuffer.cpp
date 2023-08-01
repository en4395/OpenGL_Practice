#include "VertexBuffer.h"
#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size){
    glGenBuffers(1, &m_RendererID); // 1 buffer with id buffer
    /* Select/Bind a buffer*/
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // type GL_ARRAY_BUFFER and id buffer
    /* Specify data */
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::bind() const{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::unbind() const{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
