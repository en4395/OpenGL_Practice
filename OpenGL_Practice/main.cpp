#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

/* Used as parseShader's return type, returning two strings */
struct ShaderProgramSource{
    std::string vertexSource;
    std::string fragmentSource;
};

static ShaderProgramSource parseShader(const std::string& filePath){
    std::ifstream stream(filePath); // Create input filestream, open file
    if(!stream.is_open()){ // If file cannot be opened
        std::cout << "FATAL ERROR OCCURRED. FILE COULD NOT BE OPENED\n";
        exit(0);
    }
    
    /* Used to track shader types and place them in a shader string stream array */
    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    
    const int SHADER_TYPE_COUNT = 2;
    std::string line; // Will hold current line of file
    std::stringstream ss[SHADER_TYPE_COUNT]; // Will hold shader source
    ShaderType type = ShaderType::NONE;
    
    while(getline(stream, line)){
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else{
            ss[(int)type] << line << '\n';
        }
    }
    
    return {ss[0].str(), ss[1].str()};
}

static unsigned int compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if ( result == GL_FALSE )
    {
      int length;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
      char* message = (char*)alloca(length * sizeof(char));
      glGetShaderInfoLog(id, length, &length, message);
      std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: " << message << std::endl;
      glDeleteShader(id);
      return 0;
    }

    return id;
}

/* Provide openGL with shader source code/text so that OpenGL compiles that program, link these two shaders, then give us a unique ID for that shader back. */
static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /*
     I had to add this to run this on Mac. Otherwise, GLSL version 330 was not recognised.
     I wish I could credit wherever I got this code block from. It was in a StackExchange thread.
    */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
      std::cout << "I'm apple machine" << std::endl;
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* You can't use openGL functions from GLEW until you call glewInit()*/
    if(glewInit()!=GLEW_OK){
        std::cout << "Error!" << std::endl;
    }
    
    /* Store vertex positions */
    float positions[] = {
        0.0f, 0.5f,   // 0
        0.5f, 0.0f,   // 1
        0.0f, -0.5f,  // 2
        -0.5f, 0.0f,  // 3
    };
    
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    
    
    /* Create a vertex array object */
    unsigned int vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );
    
    /* Instantiate a vertex buffer */
    VertexBuffer vb(positions, 2*6*sizeof(float));
    
    /* Vertex Attributes
     glVertexArrtibPointer(index, size, type, normalized, stride, pointer)
     These will be linked to the vertex array object that is currently bound (vao) */
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    
    /* Instantiate an index buffer */
    IndexBuffer ib(indices, 6);
    
    ShaderProgramSource source = parseShader("/Users/ellanoyes/Development/OpenGL/OpenGL_Practice/OpenGL_Practice/resources/shaders/Basic.shader");
    
    std::cout << "VERTEX SOURCE: " << source.vertexSource <<"\nFRAGMENT SOURCE: " << source.fragmentSource << std::endl;
    
    /* Create and bind shader */
    unsigned int shader = createShader(source.vertexSource, source.fragmentSource);
    glUseProgram(shader);
    int location = glGetUniformLocation(shader, "u_Color");
    glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f); // Writes the color value for the fragment shader.
    float r = 0.0f;
    float inc = 0.02f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glUniform4f(location, r, 0.3f, 0.8f, 1.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); 
        
        if(r > 1.0f)
            inc = -0.02f;
        else if(r < 0.0f)
            inc = 0.02f;
    
        r += inc;
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
