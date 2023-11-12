#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

#include "Gl.h"
#include "Window.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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
		return 1;
	}
	if (!Gl::Shader::getShaderiv(fragmentShader, GL_COMPILE_STATUS)) {
		GLchar infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "Failed to compile the vertex shader:\n" << infoLog << std::endl;
		return 1;
	}

	GLuint shaderProgram = Gl::Program::create();
	Gl::Program::attachShader(shaderProgram, vertexShader);
	Gl::Program::attachShader(shaderProgram, fragmentShader);
	Gl::Program::link(shaderProgram);

	if (!Gl::Program::getProgramiv(shaderProgram, GL_LINK_STATUS)) {
		GLchar infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "Failed to compile the shader program:\n" << infoLog << std::endl;
		return 1;
	}

	Gl::Shader::deleteShader(vertexShader);
	Gl::Shader::deleteShader(fragmentShader);

	Gl::Program::use(shaderProgram);

	GLint windowWidth = 0, windowHeight = 0;
	glfwGetFramebufferSize(window.getWinTarget(), &windowWidth, &windowHeight);
	GLint windowSizeLocation = glGetUniformLocation(shaderProgram, "uWindowSize");
	glUniform2f(windowSizeLocation, static_cast<float>(windowWidth), static_cast<float>(windowHeight));


	GLfloat vertices[] =
	{
		// VERTICES          COLOR
		-100,  100,		 0.0, 0.0, 1.0,		 0.0, 1.0,
		-100, -100,		 0.0, 0.0, 1.0,	     0.0, 0.0,
		100, -100,		 0.0, 0.0, 1.0,		 1.0, 0.0,

		-100,  100,		 0.0, 0.0, 1.0,		 0.0, 1.0,
		100, -100,		 0.0, 0.0, 1.0,		 1.0, 0.0,
		100, 100,		 0.0, 0.0, 1.0,		 1.0, 1.0,
	};

	GLuint VAO = 0;
	GLuint VBO = 0;

	Gl::VAO::generate(1, &VAO);
	Gl::VAO::bind(VAO);

	Gl::VBO::generate(1, &VBO);
	Gl::VBO::bind(GL_ARRAY_BUFFER, VBO);
	Gl::VBO::buffData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	Gl::VAO::vertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), nullptr);
	Gl::VAO::vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
	Gl::VAO::vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(5 * sizeof(float)));

	Gl::VBO::unbind(GL_ARRAY_BUFFER);
	Gl::VAO::unbind();

	GLuint texture = GL_INVALID_INDEX;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	GLint width = 0, height = 0, nrChannels = 0;

	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	glm::mat4 modelMatrix = glm::mat4(1.0);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(200, 0, 0));

	GLint uModelMatrix = glGetUniformLocation(shaderProgram, "uModelMatrix");
	glUniformMatrix4fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	
	glm::mat4 cameraMatrix = glm::mat4(1.0);
	cameraMatrix = glm::translate(cameraMatrix, glm::vec3(200, 420, 0));

	GLint uCameraMatrix = glGetUniformLocation(shaderProgram, "uCameraMatrix");
	glUniformMatrix4fv(uCameraMatrix, 1, GL_FALSE, glm::value_ptr(cameraMatrix));

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