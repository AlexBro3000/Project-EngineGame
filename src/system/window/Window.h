#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * @brief Структура, представляющая настройки окна GLFW.
 */
struct WindowSettings
{
    int     width;    // Ширина окна GLFW
    int     height;   // Высота окна GLFW
    char*   title;    // Заголовок окна GLFW

    /**
     * @brief Конструктор структуры WindowSettings по умолчанию.
     */
    WindowSettings() : width(800), height(800), title("Window") {}

    /**
     * @brief Конструктор структуры WindowSettings.
     * @param width - Ширина окна.
     * @param height - Высота окна.
     * @param title - Заголовок окна.
     */
    WindowSettings(int width, int height, char* title) : width(width), height(height), title(title) {}
};

/**
 * @brief Класс для работы с окном GLFW.
 */
class Window
{
private:
    static GLFWwindow*      window;     // Указатель на окно GLFW
    static WindowSettings   setting;    // Настройки окна GLFW

    //static double crnt_time;        // Текущее время
    //static double prev_time;        // Предыдущее время
    //static int frames;              // Количество кадров

    friend class Event;
    friend void  glfwWindowSizeCallback(GLFWwindow* window, int width, int height);

public:
    /**
     * @brief Метод для инициализации окна.
     * @return 0 в случае успешной инициализации, иначе -1.
     */
    static int Init();
    /**
     * @brief Метод для завершения работы с окном.
     */
    static void Terminate();

    static int getWidth();
    static int getHeight();

    /**
     * @brief Метод для установки режима курсора.
     * @param mode - Режим курсора.
     */
    static void setCursorMode(int mode);

    /**
     * @brief Метод для установки флага закрытия окна.
     * @param flag - Флаг закрытия окна.
     */
    static void setShouldClose(bool flag);

    /**
     * @brief Метод для проверки, должно ли окно быть закрыто.
     * @return true, если окно должно быть закрыто, иначе false.
     */
    static bool isShouldClose();

    /**
     * @brief Метод для обмена буферов кадра.
     */
    static void swapBuffers();

private:
};