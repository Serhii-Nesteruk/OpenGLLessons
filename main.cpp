#include <iostream>

#include "Gl.h"
#include "Window.h"

using namespace std;

int main() {
	Window window;
	window.initGLFWVersion(GLFW_CONTEXT_VERSION_MAJOR, 3);
	window.initGLFWVersion(GLFW_CONTEXT_VERSION_MINOR, 3);
	window.initGLFWVersion(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window.create(600, 600, "Window", nullptr, nullptr);
	window.makeContextCurrent(window.getWinTarget());

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Can't init a CLAD" << std::endl;
		glfwTerminate();
		return 1;
	}

	Gl::viewport(0, 0, 600, 600);

	GLuint vertexShader = Gl::Shader::createAndLoadFromFile("assets/shaders/main.vert",
		Gl::Shader::Type::VERTEX);
	GLuint fragmentShader = Gl::Shader::createAndLoadFromFile("assets/shaders/main.frag",
		Gl::Shader::Type::FRAGMENT);
	
	if (!Gl::Shader::getShaderiv(vertexShader, GL_COMPILE_STATUS)) {
		GLchar infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "Failed to compile the vertex shader:\n" << infoLog << std::endl;
		Gl::Shader::deleteShader(vertexShader);
		Gl::Shader::deleteShader(fragmentShader);
		glfwTerminate();
		return 1;
	}
	if (!Gl::Shader::getShaderiv(fragmentShader, GL_COMPILE_STATUS)) {
		GLchar infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "Failed to compile the vertex shader:\n" << infoLog << std::endl;
		Gl::Shader::deleteShader(vertexShader);
		Gl::Shader::deleteShader(fragmentShader);

		glfwTerminate();
		return 1;
	}

	GLuint shaderProgram = Gl::Program::create();
	Gl::Program::attachShader(shaderProgram, vertexShader);
	Gl::Program::attachShader(shaderProgram, fragmentShader);
	Gl::Program::link(shaderProgram);

	if (!Gl::Program::getProgramiv(shaderProgram, GL_LINK_STATUS)) {
		std::cerr << "Failed to link a shader program" << std::endl;
		Gl::Program::deleteProgram(shaderProgram);
		Gl::Shader::deleteShader(vertexShader);
		Gl::Shader::deleteShader(fragmentShader);

		glfwTerminate();
		return 1;
	}

	Gl::Shader::deleteShader(vertexShader);
	Gl::Shader::deleteShader(fragmentShader);

	GLfloat vertices[] =
	{
		// VERTICES          COLOR
		-0.5,  0.5,		 1.0, 0.0, 0.0,
		-0.5, -0.5,		 0.0, 1.0, 0.0,
		0.5, -0.5,		 0.0, 0.0, 1.0,

		-0.5,  0.5,		 1.0, 0.0, 0.0,
		0.5, -0.5,		 0.0, 0.0, 1.0,
		0.5, 0.5,		 0.0, 1.0, 0.0,
	};

	GLuint VAO = 0;
	GLuint VBO = 0;

	Gl::VAO::generate(1, &VAO);
	Gl::VAO::bind(VAO);

	Gl::VBO::generate(1, &VBO);
	Gl::VBO::bind(GL_ARRAY_BUFFER, VBO);
	Gl::VBO::buffData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	Gl::VAO::vertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	Gl::VAO::vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));

	Gl::VBO::unbind(GL_ARRAY_BUFFER);
	Gl::VAO::unbind();

	while (!glfwWindowShouldClose(window.getWinTarget())) {
		window.clearColor(0.2f, 0.3f, 0.3f, 1.f);
		window.clear(GL_COLOR_BUFFER_BIT);

		Gl::Program::use(shaderProgram);
		Gl::VAO::bind(VAO);
		Gl::drawArrays(GL_TRIANGLES, 0, 6);

		window.swapBuffers(window.getWinTarget());
		window.pollEvents();
	}

	Gl::VAO::deleteVertexArrays(1, &VAO);
	Gl::VBO::deleteBuffers(1, &VBO);
	Gl::Program::deleteProgram(shaderProgram);

	glfwTerminate();

	return 0;
}