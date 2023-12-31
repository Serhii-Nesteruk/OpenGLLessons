#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
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

	Shader vertexShader("assets/shaders/main.vert", Gl::Shader::Type::VERTEX);
	Shader fragmentShader("assets/shaders/main.frag", Gl::Shader::Type::FRAGMENT);

	ShaderProgram shaderProgram(vertexShader.getShader(), fragmentShader.getShader());

	shaderProgram.use();

	GLint windowWidth = 0, windowHeight = 0;
	glfwGetFramebufferSize(window.getWinTarget(), &windowWidth, &windowHeight);
	shaderProgram.uniform("uWindowSize", static_cast<GLfloat>(windowWidth), static_cast<GLfloat>(windowHeight));	
	std::vector<GLfloat> vertices =
	{
		// VERTICES          COLOR
		-100,  100,		 0.0, 0.0, 1.0,		 0.0, 1.0,
		-100, -100,		 0.0, 0.0, 1.0,	     0.0, 0.0,
		100, -100,		 0.0, 0.0, 1.0,		 1.0, 0.0,

		-100,  100,		 0.0, 0.0, 1.0,		 0.0, 1.0,
		100, -100,		 0.0, 0.0, 1.0,		 1.0, 0.0,
		100, 100,		 0.0, 0.0, 1.0,		 1.0, 1.0,
	};

	VAO vao(true, true);	
	VBO vbo(vertices);

	vao.vertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), nullptr);
	vao.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
	vao.vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(5 * sizeof(float)));

	vao.unbind();
	vbo.unbind();

	GLuint texture = GL_INVALID_INDEX;
	Gl::Texture::generate(1, &texture);
	Gl::Texture::bind(texture);
	
	Gl::Texture::setWrapS(Gl::Texture::Wrap::Repeat);
	Gl::Texture::setWrapT(Gl::Texture::Wrap::Repeat);

	Gl::Texture::setMinFilter(Gl::Texture::MinFilter::Linear);
	Gl::Texture::setMagFilter(Gl::Texture::MagFilter::Linear);
	GLint width = 0, height = 0, nrChannels = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		Gl::Texture::texImage2D(Gl::Texture::Target::Texture2D, 0, Gl::Texture::Channel::RGB,
			width, height, 0, Gl::Texture::Channel::RGB, GL_UNSIGNED_BYTE, data);
		Gl::Texture::generateMipmap();
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	GLuint texture2 = GL_INVALID_INDEX;
	Gl::Texture::generate(1, &texture2);
	Gl::Texture::bind(texture2);

	Gl::Texture::setWrapS(Gl::Texture::Wrap::Repeat);
	Gl::Texture::setWrapT(Gl::Texture::Wrap::Repeat);

	Gl::Texture::setMinFilter(Gl::Texture::MinFilter::Linear);
	Gl::Texture::setMagFilter(Gl::Texture::MagFilter::Linear);

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("smiley-face.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		Gl::Texture::texImage2D(Gl::Texture::Target::Texture2D, 0, Gl::Texture::Channel::RGB,
			width, height, 0, Gl::Texture::Channel::RGB, GL_UNSIGNED_BYTE, data);
		Gl::Texture::generateMipmap();
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	shaderProgram.use();

	shaderProgram.uniform("texture1", 0);
	shaderProgram.uniform("texture2", 1);

	glm::mat4 modelMatrix = glm::mat4(1.0);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(200, 0, 0));

	GLint uModelMatrix = Gl::Program::getUniformLocation(shaderProgram.getProgram(), "uModelMatrix");
	shaderProgram.uniform("uModelMatrix", 1, GL_FALSE, modelMatrix);

	glm::mat4 cameraMatrix = glm::mat4(1.0);
	cameraMatrix = glm::translate(cameraMatrix, glm::vec3(200, 420, 0));

	GLint uCameraMatrix = Gl::Program::getUniformLocation(shaderProgram.getProgram(), "uCameraMatrix");
	shaderProgram.uniform("uCameraMatrix", 1, GL_FALSE, cameraMatrix);

	while (!glfwWindowShouldClose(window.getWinTarget())) {
		window.clearColor(0.2f, 0.3f, 0.3f, 1.f);
		window.clear(GL_COLOR_BUFFER_BIT);

		Gl::Texture::activeTexture(GL_TEXTURE0);
		Gl::Texture::bind(texture);
		Gl::Texture::activeTexture(GL_TEXTURE1);
		Gl::Texture::bind(texture2);
		
		shaderProgram.use();
		vao.bind();
		Gl::drawArrays(GL_TRIANGLES, 0, 6);

		window.swapBuffers(window.getWinTarget());
		window.pollEvents();
	}

	return 0;
}