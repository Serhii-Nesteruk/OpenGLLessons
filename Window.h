#pragma once

#include "glad.h"
#include "GLFW/glfw3.h"

#include <string>

class Window {
public:
	Window();
	~Window();
	void create(GLint width, GLint height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	void swapBuffers(GLFWwindow* window);
	void pollEvents();
	void clear(GLbitfield mask);
	void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	void initGLFWVersion(int hint, int value);
	void makeContextCurrent(GLFWwindow* window);

	[[nodiscard]] GLFWwindow* getWinTarget() const;
private:
	GLFWwindow* window;
	GLint width = 0;
	GLint height = 0;
};