# OpenGL_Practice
Practicing using OpenGL following tutorials from "The Cherno"'s OpenGL playlist. 

## Setting up OpenGL on Mac using XCode
I don't hate C++ programming using XCode. It's ok. But setting up OpenGL was a pain. All this setup for one lousy triangle?

## Download GLFW and GLEW
1. Download GLFW [here](https://www.glfw.org/)
2. Download GLEW [here](https://glew.sourceforge.net/)

## Setting up a project in XCode

### Creating a Project
1. Create a new Command Line Tool project. Choose a project name and select C++ as the language. Select a target directory.
<img src=https://github.com/en4395/Workshop_Images/blob/main/OpenGL_Xcode_Setup/XCode_Setup_1.png width=550>

<img src=https://github.com/en4395/Workshop_Images/blob/main/OpenGL_Xcode_Setup/XCode_Setup_2.png width=550> 

<img src=https://github.com/en4395/Workshop_Images/blob/main/OpenGL_Xcode_Setup/XCode_Setup_3.png width=550>

### Project Settings
1. In the *Search Paths* section of *Build Settings*, add the header search paths for GLEW and GLFW (/usr/local/include)

<img src=https://github.com/en4395/Workshop_Images/blob/main/OpenGL_Xcode_Setup/XCode_Setup_4.png width=550>

2. In the *Signing and Capabilities* tab, select "Disable Library Validation"

<img src=https://github.com/en4395/Workshop_Images/blob/main/OpenGL_Xcode_Setup/XCode_Setup_5.png width=550>

3. In the *Build Phases* tab, click "Link Binary With Libraries". Click the + button, then add OpenGL.framework.

<img src=https://github.com/en4395/Workshop_Images/blob/main/OpenGL_Xcode_Setup/XCode_Setup_6.png width=550> 

<img src=https://github.com/en4395/Workshop_Images/blob/main/OpenGL_Xcode_Setup/XCode_Setup_7.png width=550>

4. Still under "Link Binary With Libraries", click +, "Add Other...", then "Add Files...'

<img src=https://github.com/en4395/Workshop_Images/blob/main/OpenGL_Xcode_Setup/XCode_Setup_8.png width=550>

To find the GLEW library, start in Macintosh HD, then perform "cmd + shift + . " to show hidden files. Navigate through /usr/local/Cellar/(glew or glfw version)/lib/

<img src=https://github.com/en4395/Workshop_Images/blob/main/OpenGL_Xcode_Setup/XCode_Setup_9.png width=550>

Click open. Follow the same steps to add GLFW. 

<img src=https://github.com/en4395/Workshop_Images/blob/main/OpenGL_Xcode_Setup/XCode_Setup_10.png width=550>

### Quick Test
1. In main.cpp, include the GLEW and GLFW header files

<img src=https://github.com/en4395/Workshop_Images/blob/main/OpenGL_Xcode_Setup/XCode_Setup_11.png width=550>

2. Click the build button. "Build Successful" will confirm that things are in order so far.

## WARNING! One more step if you're following an OpenGL tutorial or copying code compiled on Windows:
Ok, this caused me so much grief until I figured it out.

1. `In the main()` function add:

```
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```
Prior to creating a windowed mode window and its OpenGL context.

2. After declaring and defining your indices, create a default vertex array object: 

```
unsigned int vao;
glGenVertexArrays(1, &vao);
glBindVertexArray(vao);
```

I think this is because Mac uses the core profile (while Windows uses compatibility profile by default) so will not bind to a default vertex array.

Things should run smoothly after that. Figuring out this setup was a big drama for me. I almost submitted to learning Metal instead. 
