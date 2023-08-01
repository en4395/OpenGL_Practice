#include "IndexBuffer.h"
#include <GL/glew.h>

IndexBuffer::IndexBuffer(const void* data, unsigned int count):m_Count(count){
    glGenBuffers(1, &m_RendererID); // 1 buffer with id buffer
    /* Select/Bind a buffer*/
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); // type GL_ARRAY_BUFFER and id buffer
    /* Specify data */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer(){
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::bind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::unbind() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
