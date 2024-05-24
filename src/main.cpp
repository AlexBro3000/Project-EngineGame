#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "graphic/buffer/EBO.h"
#include "graphic/buffer/VAO.h"
#include "graphic/buffer/VBO.h"
#include "graphic/shader/ShaderProgram.h"
#include "system/manager/ResourceManager.h"
#include "system/window/Window.h"
#include <iostream>


//GLfloat point[] = {
//    -0.5f,  -0.5f, 0.0f,
//     0.5f,  -0.5f, 0.0f,
//     0.0f,   0.5f, 0.0f,
//
//     0.0f,  -0.5f, 0.0f,
//     0.25f,  0.0f, 0.0f,
//    -0.25f,  0.0f, 0.0f,
//};
//GLuint index[] = {
//    0, 3, 5,
//    3, 1, 4,
//    5, 4, 2,
//};
//
//GLfloat color[] = {
//    1.0f, 0.0f, 0.0f,
//    0.0f, 1.0f, 0.0f,
//    0.0f, 0.0f, 1.0f,
//
//    1.0f, 0.0f, 0.0f,
//    0.0f, 1.0f, 0.0f,
//    0.0f, 0.0f, 1.0f
//};

int window_width  = 1000;
int window_height = 800;

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


    //glBindVertexArray(VAO);

    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
 
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //glEnableVertexAttribArray(0);


    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Vertices coordinates
    GLfloat vertices[] =
    {
        -0.5f,      -0.5f,      0.0f,   1.0f, 0.0f, 0.0f,
        0.5f,       -0.5f,      0.0f,   0.0f, 1.0f, 0.0f,
        0.0f,       0.5f,       0.0f,   0.0f, 0.0f, 1.0f,
        -0.25f,     0.0f,       0.0f,   0.5f, 0.5f, 0.0f,
        0.25f,      0.0f,       0.0f,   0.5f, 0.0f, 0.5f,
        0.0f,       -0.5f,      0.0f,   0.0f, 0.5f, 0.5f,
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 3, 5, // Lower left triangle
        3, 2, 4, // Upper triangle
        5, 4, 1 // Lower right triangle
    };

    //// Create reference containers for the Vartex Array Object, the Vertex Buffer Object, and the Element Buffer Object
    //GLuint VAO, VBO, EBO;

    //// Generate the VAO, VBO, and EBO with only 1 object each
    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    //// Make the VAO the current Vertex Array Object by binding it
    //glBindVertexArray(VAO);

    //// Bind the VBO specifying it's a GL_ARRAY_BUFFER
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //// Introduce the vertices into the VBO
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //// Bind the EBO specifying it's a GL_ELEMENT_ARRAY_BUFFER
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //// Introduce the indices into the EBO
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //// Enable the Vertex Attribute so that OpenGL knows to use it
    //glEnableVertexAttribArray(0);
    //// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    //// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);
    //// Bind the EBO to 0 so that we don't accidentally modify it
    //// MAKE SURE TO UNBIND IT AFTER UNBINDING THE VAO, as the EBO is linked in the VAO
    //// This does not apply to the VBO because the VBO is already linked to the VAO during glVertexAttribPointer
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    VAO vao;
    vao.bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO vbo(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO ebo(indices, sizeof(indices));

    // Links VBO to VAO
    vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    vao.linkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    vao.unbind();
    vbo.unbind();
    ebo.unbind();



    
    /*GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);*/

    /* Loop until the user closes the window */
    while (!Window::isShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        shader.use();
        
        //glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        vao.bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        
        Window::swapBuffers();
        glfwPollEvents();
    }

    vao.~VAO();
    vbo.~VBO();
    ebo.~EBO();

    Window::Terminate();
    ResourceManager::Terminate();

    return 0;
}