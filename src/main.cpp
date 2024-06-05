#include <thread>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/client/camera/Camera.h"
#include "graphic/buffer/EBO.h"
#include "graphic/buffer/VAO.h"
#include "graphic/buffer/VBO.h"
#include "graphic/shader/ShaderProgram.h"
#include "graphic/texture/Texture.h"
#include "system/manager/Directory.h"
#include "system/manager/ResourceManager.h"
#include "system/window/Event.h"
#include "system/window/Window.h"

//GLfloat vertices[] =
//{
//    -0.5f, 0.0f,  0.5f, 0.0f, 0.0f,
//    -0.5f, 0.0f, -0.5f, 5.0f, 0.0f,
//     0.5f, 0.0f, -0.5f, 0.0f, 0.0f,
//     0.5f, 0.0f,  0.5f, 5.0f, 0.0f,
//     0.0f, 0.8f,  0.0f, 2.5f, 5.0f
//};
//GLuint indices[] =
//{
//    0, 1, 2,
//    0, 2, 3,
//    0, 1, 4,
//    1, 2, 4,
//    2, 3, 4,
//    3, 0, 4
//};

//GLfloat vertices[] =
//{ //     COORDINATES     /    TexCoord   /        NORMALS       /
//    -0.5f, 0.0f,  0.5f,     0.0f, 0.0f,      0.0f, -1.0f, 0.0f,
//    -0.5f, 0.0f, -0.5f,     5.0f, 0.0f,      0.0f, -1.0f, 0.0f,
//     0.5f, 0.0f,  0.5f,     0.0f, 5.0f,      0.0f, -1.0f, 0.0f,
//     0.5f, 0.0f, -0.5f,     5.0f, 5.0f,      0.0f, -1.0f, 0.0f,
//
//     0.0f, 0.8f,  0.0f,     2.5f, 5.0f,     -0.8f, 0.5f,  0.0f,
//    -0.5f, 0.0f, -0.5f,     5.0f, 0.0f,     -0.8f, 0.5f,  0.0f,
//    -0.5f, 0.0f,  0.5f,     0.0f, 0.0f,     -0.8f, 0.5f,  0.0f,
//
//     0.0f, 0.8f,  0.0f,     2.5f, 5.0f,      0.0f, 0.5f, -0.8f,
//     0.5f, 0.0f, -0.5f,     0.0f, 0.0f,      0.0f, 0.5f, -0.8f,
//    -0.5f, 0.0f, -0.5f,     5.0f, 0.0f,      0.0f, 0.5f, -0.8f,
//
//     0.0f, 0.8f,  0.0f,     2.5f, 5.0f,      0.8f, 0.5f,  0.0f,
//     0.5f, 0.0f,  0.5f,     5.0f, 0.0f,      0.8f, 0.5f,  0.0f,
//     0.5f, 0.0f, -0.5f,     0.0f, 0.0f,      0.8f, 0.5f,  0.0f,
//
//     0.0f, 0.8f,  0.0f,     2.5f, 5.0f,      0.0f, 0.5f,  0.8f,
//    -0.5f, 0.0f,  0.5f,     0.0f, 0.0f,      0.0f, 0.5f,  0.8f,
//     0.5f, 0.0f,  0.5f,     5.0f, 0.0f,      0.0f, 0.5f,  0.8f,
//};

GLfloat vertices[] =
{ //     COORDINATES     /    TexCoord   /        NORMALS       /
    -0.5f, 0.0f,  0.5f,     0.0f, 0.0f,      -0.5f, -0.5f,  0.5f,
    -0.5f, 0.0f, -0.5f,     5.0f, 0.0f,      -0.5f, -0.5f, -0.5f,
     0.5f, 0.0f,  0.5f,     0.0f, 5.0f,      0.5f, -0.5f,  0.5f,
     0.5f, 0.0f, -0.5f,     5.0f, 5.0f,      0.5f, -0.5f, -0.5f,

     0.0f, 0.8f,  0.0f,     2.5f, 5.0f,     0.0f, 0.8f,  0.0f,
    -0.5f, 0.0f, -0.5f,     5.0f, 0.0f,     -0.5f, 0.0f, -0.5f,
    -0.5f, 0.0f,  0.5f,     0.0f, 0.0f,     -0.5f, 0.0f,  0.5f,

     0.0f, 0.8f,  0.0f,     2.5f, 5.0f,      0.0f, 0.8f,  0.0f,
     0.5f, 0.0f, -0.5f,     0.0f, 0.0f,      0.5f, 0.0f, -0.5f,
    -0.5f, 0.0f, -0.5f,     5.0f, 0.0f,      -0.5f, 0.0f, -0.5f,

     0.0f, 0.8f,  0.0f,     2.5f, 5.0f,      0.0f, 0.8f,  0.0f,
     0.5f, 0.0f,  0.5f,     5.0f, 0.0f,      0.5f, 0.0f,  0.5f,
     0.5f, 0.0f, -0.5f,     0.0f, 0.0f,      0.5f, 0.0f, -0.5f,

     0.0f, 0.8f,  0.0f,     2.5f, 5.0f,      0.0f, 0.8f,  0.0f,
    -0.5f, 0.0f,  0.5f,     0.0f, 0.0f,      -0.5f, 0.0f,  0.5f,
     0.5f, 0.0f,  0.5f,     5.0f, 0.0f,      0.5f, 0.0f,  0.5f,
};


// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2, 2, 1, 3,
    4, 5, 6, 7, 8, 9,
    10, 11, 12,
    13, 14, 15,
};

GLfloat lightVertices[] =
{
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
};
GLuint lightIndices[] =
{
    0, 1, 2, 0, 2, 3,
    0, 4, 7, 0, 7, 3,
    3, 7, 6, 3, 6, 2,
    2, 6, 5, 2, 5, 1,
    1, 5, 4, 1, 4, 0,
    4, 5, 6, 4, 6, 7
};

int main(int argc, char** argv)
{
    ResourceManager::Init(argc, argv);
    Window::         Init();
    Event::          Init();

    // SHADER

    ShaderProgram shader = ResourceManager::ShaderProgram::load("Main",  "main_vert.glsl",  "main_frag.glsl");
    ShaderProgram light  = ResourceManager::ShaderProgram::load("Light", "light_vert.glsl", "light_frag.glsl");

    // BUFFER

    VAO vao;
    vao.bind();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices,  sizeof(indices));
    vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*) 0);
    vao.linkAttrib(vbo, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.linkAttrib(vbo, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    VAO light_vao;
    light_vao.bind();
    VBO light_vbo(lightVertices, sizeof(lightVertices));
    EBO light_ebo(lightIndices, sizeof(lightIndices));
    light_vao.linkAttrib(light_vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    light_vao.unbind();
    light_vbo.unbind();
    light_ebo.unbind();

    // TEXTURE

    Texture texture(
        "C:\\Users\\alexb\\Desktop\\Новая папка\\Project-EngineGame\\build\\Debug\\res\\textures\\default\\brick-5.png",
        GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE
    );
    texture.useShaderUniform(shader, "u_texture_0", 0);

    // CAMERA

    Camera camera(glm::vec3(0.0f, 0.25f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f));

    // LIGHT

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos   = glm::vec3(1.0f, 0.5f, 0.2f);
    glm::mat4 lightModel = glm::translate(glm::mat4(1.0f), lightPos);
    light.useUniform("model", lightModel);
    light.useUniform("color", lightColor);

    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.useUniform("model", model);
    shader.useUniform("light_color", lightColor);
    shader.useUniform("light_position", lightPos);

    // Установка начальных значений

    float crntTime = glfwGetTime();
    float delta;

    // Настройка

    // glEnable(GL_CULL_FACE);  // Отбражение лицевой стороны
    glEnable(GL_DEPTH_TEST); // Тест глубины

    while (!Window::isShouldClose())
    {
        // Стабилизация FPS
        float FPS = 80.0f;
        delta = glfwGetTime() - crntTime;
        if (delta < 1.0f / FPS)
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000.0f * (1.0f / FPS - delta))));
        crntTime += delta;

        // Управление
        {
            if (Event::isKeyDown(GLFW_KEY_ESCAPE)) {
                Window::setShouldClose(true);
            }
            if (Event::isKeyDown(GLFW_KEY_TAB)) {
                if (Event::isCursorLocked())
                    Event::setCursorLocked(false);
                else
                    Event::setCursorLocked(true);
            }



            if (Event::isKeyPressed(GLFW_KEY_W)) {
                camera.toPosition(glm::vec3(0, 0, 1.0f), delta);
            }
            if (Event::isKeyPressed(GLFW_KEY_S)) {
                camera.toPosition(glm::vec3(0, 0, -1.0f), delta);
            }
            if (Event::isKeyPressed(GLFW_KEY_D)) {
                camera.toPosition(glm::vec3(1.0f, 0, 0), delta);
            }
            if (Event::isKeyPressed(GLFW_KEY_A)) {
                camera.toPosition(glm::vec3(-1.0f, 0, 0), delta);
            }
            if (Event::isKeyPressed(GLFW_KEY_SPACE)) {
                camera.toPosition(glm::vec3(0, 1.0f, 0), delta);
            }
            if (Event::isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
                camera.toPosition(glm::vec3(0, -1.0f, 0), delta);
            }

            if (Event::isCursorLocked()) {
                camera.toRotate(glm::vec3(-Event::getCursorMovement().y, -Event::getCursorMovement().x, 0.0f), 0.05f);
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 projview = camera.getProjection() * camera.getView();
        glm::vec3 position = camera.getPosition();

        shader.use();
        shader.useUniform("projview", projview);
        shader.useUniform("position", position);
        texture.bind();
        vao.bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        light.use();
        light.useUniform("projview", projview);
        light_vao.bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        Window::swapBuffers();
        Event:: pollEvents();
    }

    vao.~VAO();
    vbo.~VBO();
    ebo.~EBO();
    texture.~Texture();

    light_vao.~VAO();
    light_vbo.~VBO();
    light_ebo.~EBO();

    ResourceManager::Terminate();
    Window::         Terminate();
    Event::          Terminate();

    return 0;
}