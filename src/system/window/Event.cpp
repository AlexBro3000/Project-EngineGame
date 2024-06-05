#include "Event.h"

#include "Window.h"

bool*           Event::button_keys;
bool*           Event::button_keys_frame;
std::list<int>  Event::button_frame_stack;
glm::vec2       Event::cursor_pos;
glm::vec2       Event::cursor_delta_pos;
bool            Event::cursor_locked;
bool            Event::cursor_started;

#define KEY_BUTTON_SIZE    512
#define MOUSE_BUTTON_SIZE  8

/* Положение мышки */
void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (Event::cursor_started) {
        Event::cursor_delta_pos.x += xpos - Event::cursor_pos.x;
        Event::cursor_delta_pos.y += ypos - Event::cursor_pos.y;
    }
    else {
        Event::cursor_started = true;
    }
    Event::cursor_pos.x = xpos;
    Event::cursor_pos.y = ypos;
}

/* Нажатие кнопки мыши */
void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
{
    if (action == GLFW_PRESS) {
        Event::button_keys[KEY_BUTTON_SIZE + button]       = true;
        Event::button_keys_frame[KEY_BUTTON_SIZE + button] = true;
        Event::button_frame_stack.push_back(KEY_BUTTON_SIZE + button);
    }
    else if (action == GLFW_RELEASE) {
        Event::button_keys[KEY_BUTTON_SIZE + button]       = false;
        Event::button_keys_frame[KEY_BUTTON_SIZE + button] = true;
        Event::button_frame_stack.push_back(KEY_BUTTON_SIZE + button);
    }
}

/* Нажатие кнопки клавиатуры */
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS) {
        Event::button_keys[key]       = true;
        Event::button_keys_frame[key] = true;
        Event::button_frame_stack.push_back(key);
    }
    else if (action == GLFW_RELEASE) {
        Event::button_keys[key]       = false;
        Event::button_keys_frame[key] = true;
        Event::button_frame_stack.push_back(key);
    }
}

/* Изменение размеров экрана */
void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    Window::setting.width  = width;
    Window::setting.height = height;
}

int Event::Init()
{
    button_keys        = new bool[KEY_BUTTON_SIZE + MOUSE_BUTTON_SIZE];
    button_keys_frame  = new bool[KEY_BUTTON_SIZE + MOUSE_BUTTON_SIZE];
    button_frame_stack = std::list<int>();
    memset(button_keys,       false, KEY_BUTTON_SIZE + MOUSE_BUTTON_SIZE);
    memset(button_keys_frame, false, KEY_BUTTON_SIZE + MOUSE_BUTTON_SIZE);

    cursor_pos.x = 0.0f;
    cursor_pos.y = 0.0f;
    cursor_delta_pos.x = 0.0f;
    cursor_delta_pos.y = 0.0f;
    cursor_locked  = false;
    cursor_started = false;

    glfwSetCursorPosCallback(Window::window,   glfwCursorPosCallback);
    glfwSetMouseButtonCallback(Window::window, glfwMouseButtonCallback);
    glfwSetKeyCallback(Window::window,         glfwKeyCallback);
    glfwSetWindowSizeCallback(Window::window,  glfwWindowSizeCallback);
    return 0;
}

void Event::Terminate()
{
    delete button_keys;
    delete button_keys_frame;
}

glm::vec2 Event::getCursorMovement()
{
    return cursor_delta_pos;
}

void Event::setCursorLocked(bool flag)
{
    cursor_locked = flag;
    Window::setCursorMode(cursor_locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

bool Event::isCursorLocked()
{
    return cursor_locked;
}

bool Event::isMouseDown(int keycode)
{
    if (keycode < 0 || keycode >= MOUSE_BUTTON_SIZE)
        return false;
    return button_keys[KEY_BUTTON_SIZE + keycode] && button_keys_frame[KEY_BUTTON_SIZE + keycode];
}

bool Event::isMousePressed(int keycode)
{
    if (keycode < 0 || keycode >= MOUSE_BUTTON_SIZE)
        return false;
    return button_keys[KEY_BUTTON_SIZE + keycode];
}

bool Event::isMouseUp(int keycode)
{
    if (keycode < 0 || keycode >= MOUSE_BUTTON_SIZE)
        return false;
    return !button_keys[KEY_BUTTON_SIZE + keycode] && button_keys_frame[KEY_BUTTON_SIZE + keycode];
}

bool Event::isMouseReleased(int keycode)
{
    if (keycode < 0 || keycode >= MOUSE_BUTTON_SIZE)
        return false;
    return !button_keys[KEY_BUTTON_SIZE + keycode];
}

bool Event::isKeyDown(int keycode)
{
    if (keycode < 0 || keycode >= KEY_BUTTON_SIZE)
        return false;
    return button_keys[keycode] && button_keys_frame[keycode];
}

bool Event::isKeyPressed(int keycode)
{
    if (keycode < 0 || keycode >= KEY_BUTTON_SIZE)
        return false;
    return button_keys[keycode];
}

bool Event::isKeyUp(int keycode)
{
    if (keycode < 0 || keycode >= KEY_BUTTON_SIZE)
        return false;
    return !button_keys[keycode] && button_keys_frame[keycode];
}

bool Event::isKeyReleased(int keycode)
{
    if (keycode < 0 || keycode >= KEY_BUTTON_SIZE)
        return false;
    return !button_keys[keycode];
}

void Event::pollEvents()
{
    if (button_frame_stack.size() != 0)
        clearFrameStack();
    cursor_delta_pos.x = 0.0f;
    cursor_delta_pos.y = 0.0f;
    glfwPollEvents();
}

void Event::clearFrameStack()
{
    for (int it : button_frame_stack)
        button_keys_frame[it] = false;
    button_frame_stack.clear();
}