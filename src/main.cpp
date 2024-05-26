#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stb_image.h>

#include "graphic/buffer/EBO.h"
#include "graphic/buffer/VAO.h"
#include "graphic/buffer/VBO.h"
#include "graphic/shader/ShaderProgram.h"
#include "graphic/texture/Texture.h"
#include "system/manager/Directory.h"
#include "system/manager/ResourceManager.h"
#include "system/window/Window.h"
#include <iostream>

int window_width  = 1000;
int window_height = 1000;

void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    window_width = width;
    window_height = height;
    glViewport(0, 0, window_width, window_height);
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        std::cout << "press" << std::endl;
}



int main(int argc, char** argv)
{
    ResourceManager::Init(argc, argv);

    Window::Init();

    ShaderProgram shader = ResourceManager::ShaderProgram::load("Main", "main_vert.glsl", "main_frag.glsl");

    GLfloat vertices[] =
    {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -0.2f, -0.2f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, -0.2f,  1.2f,
         0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  1.2f,  1.2f,
         0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,  1.2f, -0.2f,
    };

    GLuint indices[] =
    {
        0, 2, 1,
        0, 3, 2,
    };

    VAO vao;
    vao.bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO vbo(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO ebo(indices, sizeof(indices));

    // Links VBO to VAO
    vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.linkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.linkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));


    // Unbind all to prevent accidentally modifying them
    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    // TEXTURE

    Texture texture(
        "C:\\Users\\alexb\\Desktop\\Новая папка\\Project-EngineGame\\build\\Debug\\res\\textures\\default\\brick-5.png",
        GL_TEXTURE_2D,
        GL_TEXTURE0,
        GL_RGB,
        GL_UNSIGNED_BYTE
    );
    texture.useShaderUniform(shader, "u_texture");

    /* Loop until the user closes the window */
    while (!Window::isShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        texture.bind();
        
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        Window::swapBuffers();
        glfwPollEvents();
    }

    vao.~VAO();
    vbo.~VBO();
    ebo.~EBO();
    texture.~Texture();

    Window::Terminate();
    ResourceManager::Terminate();

    return 0;
}