#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * @brief ���������, �������������� ��������� ���� GLFW.
 */
struct WindowSettings
{
    int     width;    // ������ ���� GLFW
    int     height;   // ������ ���� GLFW
    char*   title;    // ��������� ���� GLFW

    /**
     * @brief ����������� ��������� WindowSettings �� ���������.
     */
    WindowSettings() : width(800), height(800), title("Window") {}

    /**
     * @brief ����������� ��������� WindowSettings.
     * @param width - ������ ����.
     * @param height - ������ ����.
     * @param title - ��������� ����.
     */
    WindowSettings(int width, int height, char* title) : width(width), height(height), title(title) {}
};

/**
 * @brief ����� ��� ������ � ����� GLFW.
 */
class Window
{
private:
    static GLFWwindow*      window;     // ��������� �� ���� GLFW
    static WindowSettings   setting;    // ��������� ���� GLFW

    //static double crnt_time;        // ������� �����
    //static double prev_time;        // ���������� �����
    //static int frames;              // ���������� ������

    friend class Event;
    friend void  glfwWindowSizeCallback(GLFWwindow* window, int width, int height);

public:
    /**
     * @brief ����� ��� ������������� ����.
     * @return 0 � ������ �������� �������������, ����� -1.
     */
    static int Init();
    /**
     * @brief ����� ��� ���������� ������ � �����.
     */
    static void Terminate();

    static int getWidth();
    static int getHeight();

    /**
     * @brief ����� ��� ��������� ������ �������.
     * @param mode - ����� �������.
     */
    static void setCursorMode(int mode);

    /**
     * @brief ����� ��� ��������� ����� �������� ����.
     * @param flag - ���� �������� ����.
     */
    static void setShouldClose(bool flag);

    /**
     * @brief ����� ��� ��������, ������ �� ���� ���� �������.
     * @return true, ���� ���� ������ ���� �������, ����� false.
     */
    static bool isShouldClose();

    /**
     * @brief ����� ��� ������ ������� �����.
     */
    static void swapBuffers();

private:
};