#include "Window.h"

#include "../console/Console.h"
#include <format>
//#include <filesystem>

GLFWwindow*     Window::window = nullptr;           // Указатель на окно GLFW
WindowSettings  Window::setting = WindowSettings(); // Настройки окна GLFW
//double          Window::crnt_time = 0.0;            // Текущее время
//double          Window::prev_time = 0.0;            // Предыдущее время
//int             Window::frames = 0;                 // Количество кадров

int Window::Init()
{
    /* Инициалзация библиотеки GLFW */
    if (glfwInit()) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // glfwWindowHint(GLFW_SAMPLES, 4);
        // glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

        Console::Info("The GLFW library initialization was successful");
    }
    else {
        Console::Error("Failed to initialize GLFW library");
        return -1;
    }
    
    /* Инициалзация оконного приложения */
    Window::window = glfwCreateWindow(setting.width, setting.height, setting.title, NULL, NULL);
    if (window) {
        /* Делаем контекст окна текущим */
        glfwMakeContextCurrent(window);
        Console::Info("The window creation was successful");
    }
    else {
        glfwTerminate();
        Console::Error("Failed to create window");
        return -1;
    }

    // glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    // glfwSetKeyCallback(window, glfwKeyCallback);

    /* Инициалзация библиотеки GLAD */
    if (gladLoadGL()) {
        glViewport(0, 0, setting.width, setting.height);
        Console::Info("The GLAD library initialization was successful");
    }
    else {
        glfwTerminate();
        Console::Error("Failed to initialize GLAD library");
        return -1;
    }

    Console::Info("Renderer:",       reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    Console::Info("OpenGL Version:", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

    // Window::crnt_time = glfwGetTime();
    // Window::prev_time = crnt_time;
    // Window::frames = 0;

	return 0;
}

void Window::Terminate()
{
	glfwTerminate();
}

//void Window::setCursorMode(int mode)
//{
//	glfwSetInputMode(window, GLFW_CURSOR, mode);
//}

//void Window::setShouldClose(bool flag)
//{
//	glfwSetWindowShouldClose(window, flag);
//}

bool Window::isShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}