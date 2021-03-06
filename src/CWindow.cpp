#include "CWindow.hpp"
#include <iostream>

void ErrorCallback(int error, const char *desc)
{
    fprintf_s(stderr, "Error %d: %s\n", error, desc);
}

void FramebufferCallback(GLFWwindow *window, int width, int height)
{
}

CWindow::CWindow(const uint32_t width, const uint32_t height) : m_width(width), m_height(height)
{
    InitWindow();
}

void CWindow::InitWindow()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize glfw.");
    }
    glfwSetErrorCallback(ErrorCallback);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    mp_window = glfwCreateWindow(m_width, m_height, "App", nullptr, nullptr);
    glfwSetFramebufferSizeCallback(mp_window, FramebufferCallback);
}

void CWindow::Terminate() const
{
    glfwDestroyWindow(mp_window);
    glfwTerminate();
}

CWindow::~CWindow()
{
    Terminate();
}
