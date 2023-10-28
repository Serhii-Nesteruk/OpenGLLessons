#include "OpenGLApp.h"

#include <iostream>

OpenGlApp::OpenGlApp()
{
	if (!init())
	{
		std::cerr << "Failed to initialize a GLFW and/or a GLAD" << std::endl;
	}
	else
	{
		std::cerr << "Initialize succeeded" << std::endl;
	}

	if (!shadersSetup())
	{
		std::cerr << "Failed to setup shaders" << std::endl;
	}
	else
	{
		std::cerr << "setup shaders is succeeded" << std::endl;
	}
		
}

OpenGlApp::~OpenGlApp()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
}

void OpenGlApp::draw()
{
	while (!glfwWindowShouldClose(window))//Todo: bind VAO
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6); // drawcall

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

bool OpenGlApp::init()
{
	setupGLFWVersion();
	createWindow();
	glfwMakeContextCurrent(window);//?

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cerr << "Can't init a CLAD" << std::endl;
		glfwTerminate();
		return false;
	}

	glViewport(0, 0, 600, 600);

	initializeShaderSources();
	initVertexBuffer();

	return true;
}

bool OpenGlApp::shadersSetup()
{
	GLuint vertexShader;
	GLuint fragmentShader;

	if (!setupVertexShader(vertexShader)) 
	{
		std::cerr << "Cannot setup a vertux shader" << std::endl;
		removeShaders(vertexShader, fragmentShader);
		return false;
	}
	if (!setupFragmentShader(fragmentShader))
	{
		std::cerr << "Cannot setup a fragment shader" << std::endl;
		removeShaders(vertexShader, fragmentShader);
		return false;
	}
	if (!setupShaderProgram(vertexShader, fragmentShader))
	{
		std::cerr << "Cannot setup a shader program" << std::endl;
		removeShaders(vertexShader, fragmentShader);
		return false;
	}

	removeShaders(vertexShader, fragmentShader);
	return true;
}

bool OpenGlApp::setupVertexShader(GLuint& vertexShader)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	std::string shaderFailureStatus = checkShaderFailureStatus(vertexShader, GL_COMPILE_STATUS);
	if (shaderFailureStatus != std::string())
	{
		std::cerr << shaderFailureStatus << std::endl;
		return false;
	}
	return true;
}

bool OpenGlApp::setupFragmentShader(GLuint& fragmentShader)
{
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	std::string shaderFailureStatus = checkShaderFailureStatus(fragmentShader, GL_COMPILE_STATUS);
	if (shaderFailureStatus != std::string())
	{
		std::cerr << shaderFailureStatus << std::endl;
		return false;
	}
	return true;
}

bool OpenGlApp::setupShaderProgram(GLuint& vertexShader, GLuint& fragmentShader)
{
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	std::string programFailureStatus = checkProgramFailureStatus(shaderProgram, GL_LINK_STATUS);
	if (programFailureStatus == std::string()) {
		std::cerr << programFailureStatus << std::endl;
		return false;
	}

	return true;
}

void OpenGlApp::initVertexBuffer()
{
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

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void OpenGlApp::removeShaders(GLuint& vertexShader, GLuint& fragmentShader)
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void OpenGlApp::setupGLFWVersion()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void OpenGlApp::initializeShaderSources()
{
	vertexShaderSource = R"(#version 330 core
			layout (location = 0) in vec2 aPos;
			layout (location = 1) in vec3 aColor;
				
			out vec3 ioColor;
				
			void main()
			{
				ioColor = aColor;
				gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
			})";
	fragmentShaderSource = R"(#version 330 core

		out vec4 FragColor;
			
		in vec3 ioColor;
			
		void main()
		{
			FragColor = vec4(ioColor.r, ioColor.g, ioColor.b, 1.0f);
		})";
}

std::string OpenGlApp::checkShaderFailureStatus(GLuint shader, GLenum pname)
{
	int success = 0;
	char infoLog[512];
	glGetShaderiv(shader, pname, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		return std::string("ERROR::SHADER::VERTEX::COMPILATION_FAILED: ") + infoLog;
	}

	return std::string();
}

std::string OpenGlApp::checkProgramFailureStatus(GLuint program, GLenum pname)
{
	int success = 0;
	char infoLog[512];
	glGetProgramiv(program, pname, &success);
	if (!success)
	{
		glGetShaderInfoLog(program, 512, NULL, infoLog);
		return std::string("ERROR::SHADER::VERTEX::COMPILATION_FAILED: ") + infoLog;
	}

	return std::string();
}

bool OpenGlApp::createWindow()
{
	window = glfwCreateWindow(600, 600, "Window", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Can't create a window" << std::endl;
		glfwTerminate();
		return false;
	}
	return true;
}
