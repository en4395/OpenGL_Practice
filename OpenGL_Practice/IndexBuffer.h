#pragma once

class IndexBuffer{
private:
    unsigned int m_RendererID; /* Unique ID for every type of object created */
    unsigned int m_Count;
public:
    IndexBuffer(const void* data, unsigned int count);
    ~IndexBuffer();
    
    void bind() const; /* Will want to call this on a const object later */
    void unbind() const;
    
    inline unsigned int getCount() const {return m_Count;};
};
