#pragma once

class VertexBuffer{
private:
    unsigned int m_RendererID; /* Unique ID for every type of object created */
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    
    void bind() const;
    void unbind() const;
};
