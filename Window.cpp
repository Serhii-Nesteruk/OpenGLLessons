#include "Window.h"

Window::Window()
{
	glfwInit();
}

void Window::create(GLint width, GLint height,const std::string& title, GLFWmonitor* monitor, GLFWwindow* share)
{
	window = glfwCreateWindow(width, height, title.c_str(), monitor, share);
	if (!window) {
		throw std::exception("Failed to create window");
		glfwTerminate();
	}

	this->width = width;
	this->height = height;

}

void Window::swapBuffers(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::clear(GLbitfield mask)
{
	glClear(mask);
}

void Window::clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glClearColor(red, green, blue, alpha);
}

void Window::initGLFWVersion(int hint, int value)
{
	glfwWindowHint(hint, value);
}

void Window::makeContextCurrent(GLFWwindow* window)
{
	glfwMakeContextCurrent(window);
}

GLFWwindow* Window::getWinTarget() const
{
	return window;
}
