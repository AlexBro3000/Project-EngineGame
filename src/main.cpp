#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>


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


int main(void)
{
    GLFWwindow* window;
    const char* title = "Engine Game";

    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "Failed to initialize library GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(window_width, window_height, title, NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	
	if (!gladLoadGL())
	{
        std::cout << "Failed to initialize library GLAD" << std::endl;
        return -1;
	}

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}