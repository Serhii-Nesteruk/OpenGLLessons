#pragma once

#include "glad.h"
#include "GLFW/glfw3.h"

#include <string>
#include <vector>

class OpenGlApp {
public:
	OpenGlApp();
	~OpenGlApp();

	void draw();
private:
	bool init();
	bool shadersSetup();
	bool setupVertexShader(GLuint& vertexShader);
	bool setupFragmentShader(GLuint& fragmentShader);
	bool setupShaderProgram(GLuint& vertexShader, GLuint& fragmentShader);
	void initVertexBuffer();
	void removeShaders(GLuint& vertexShader, GLuint& fragmentShader);
	void setupGLFWVersion();

	void initializeShaderSources();
	std::string checkShaderFailureStatus(GLuint shader, GLenum pname);
	std::string checkProgramFailureStatus(GLuint program, GLenum pname);
	bool createWindow();
private:
	const char* vertexShaderSource = nullptr;
	const char* fragmentShaderSource = nullptr;
	//std::string vertexShaderSource{};
	//std::string fragmentShaderSource{};
	GLFWwindow* window = nullptr;
	GLuint shaderProgram = 0;
	GLuint VBO = 0;
	GLuint VAO = 0;

};