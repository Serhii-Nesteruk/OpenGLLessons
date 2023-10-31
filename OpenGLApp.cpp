#include "OpenGLApp.h"

#include <iostream>
#include "Utils.h"


//#include "OpenGLApp.h"
//
//#include <iostream>
//
//OpenGlApp::OpenGlApp()
//{
//	if (!init())
//	{
//		std::cerr << "Failed to initialize a GLFW and/or a GLAD" << std::endl;
//	}
//	else
//	{
//		std::cerr << "Initialize succeeded" << std::endl;
//	}
//
//	if (!shadersSetup())
//	{
//		std::cerr << "Failed to setup shaders" << std::endl;
//	}
//	else
//	{
//		std::cerr << "setup shaders is succeeded" << std::endl;
//	}
//		
//}
//
//OpenGlApp::~OpenGlApp()
//{
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteProgram(shaderProgram);
//
//	glfwTerminate();
//}
//
//void OpenGlApp::draw()
//{
//	while (!glfwWindowShouldClose(window))//Todo: bind VAO
//	{
//		glClearColor(0.2f, 0.3f, 0.3f, 1.f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glUseProgram(shaderProgram);
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 6); // drawcall
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//}
//
//bool OpenGlApp::init()
//{
//	setupGLFWVersion();
//	createWindow();
//	glfwMakeContextCurrent(window);//?
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
//	{
//		std::cerr << "Can't init a CLAD" << std::endl;
//		glfwTerminate();
//		return false;
//	}
//
//	glViewport(0, 0, 600, 600);
//
//	initializeShaderSources();
//	initVertexBuffer();
//
//	return true;
//}
//
//bool OpenGlApp::shadersSetup()
//{
//	GLuint vertexShader;
//	GLuint fragmentShader;
//
//	if (!setupVertexShader(vertexShader)) 
//	{
//		std::cerr << "Cannot setup a vertux shader" << std::endl;
//		removeShaders(vertexShader, fragmentShader);
//		return false;
//	}
//	if (!setupFragmentShader(fragmentShader))
//	{
//		std::cerr << "Cannot setup a fragment shader" << std::endl;
//		removeShaders(vertexShader, fragmentShader);
//		return false;
//	}
//	if (!setupShaderProgram(vertexShader, fragmentShader))
//	{
//		std::cerr << "Cannot setup a shader program" << std::endl;
//		removeShaders(vertexShader, fragmentShader);
//		return false;
//	}
//
//	removeShaders(vertexShader, fragmentShader);
//	return true;
//}
//
//bool OpenGlApp::setupVertexShader(GLuint& vertexShader)
//{
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
//	glCompileShader(vertexShader);
//	std::string shaderFailureStatus = checkShaderFailureStatus(vertexShader, GL_COMPILE_STATUS);
//	if (!shaderFailureStatus.empty())
//	{
//		std::cerr << shaderFailureStatus << std::endl;
//		return false;
//	}
//	return true;
//}
//
//bool OpenGlApp::setupFragmentShader(GLuint& fragmentShader)
//{
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
//	glCompileShader(fragmentShader);
//	std::string shaderFailureStatus = checkShaderFailureStatus(fragmentShader, GL_COMPILE_STATUS);
//	if (!shaderFailureStatus.empty())
//	{
//		std::cerr << shaderFailureStatus << std::endl;
//		return false;
//	}
//	return true;
//}
//
//bool OpenGlApp::setupShaderProgram(GLuint& vertexShader, GLuint& fragmentShader)
//{
//	shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//	std::string programFailureStatus = checkProgramFailureStatus(shaderProgram, GL_LINK_STATUS);
//	if (!programFailureStatus.empty()) {
//		std::cerr << programFailureStatus << std::endl;
//		return false;
//	}
//
//	return true;
//}
//
//void OpenGlApp::initVertexBuffer()
//{
//	GLfloat vertices[] =
//	{
//		// VERTICES          COLOR
//		-0.5,  0.5,		 1.0, 0.0, 0.0,
//		-0.5, -0.5,		 0.0, 1.0, 0.0,
//		0.5, -0.5,		 0.0, 0.0, 1.0,
//
//		-0.5,  0.5,		 1.0, 0.0, 0.0,
//		0.5, -0.5,		 0.0, 0.0, 1.0,
//		0.5, 0.5,		 0.0, 1.0, 0.0,
//	};
//
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//		glGenBuffers(1, &VBO);
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
//
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//}
//
//void OpenGlApp::removeShaders(GLuint& vertexShader, GLuint& fragmentShader)
//{
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//}
//
//void OpenGlApp::setupGLFWVersion()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//}
//
//void OpenGlApp::initializeShaderSources()
//{
//	vertexShaderSource = R"(#version 330 core
//			layout (location = 0) in vec2 aPos;
//			layout (location = 1) in vec3 aColor;
//				
//			out vec3 ioColor;
//				
//			void main()
//			{
//				ioColor = aColor;
//				gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
//			})";
//	fragmentShaderSource = R"(#version 330 core
//
//		out vec4 FragColor;
//			
//		in vec3 ioColor;
//			
//		void main()
//		{
//			FragColor = vec4(ioColor.r, ioColor.g, ioColor.b, 1.0f);
//		})";
//}
//
//std::string OpenGlApp::checkShaderFailureStatus(GLuint shader, GLenum pname)
//{
//	int success = 0;
//	char infoLog[512];
//	glGetShaderiv(shader, pname, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(shader, 512, NULL, infoLog);
//		return std::string("ERROR::SHADER::VERTEX::COMPILATION_FAILED: ") + infoLog;
//	}
//
//	return std::string();
//}
//
//std::string OpenGlApp::checkProgramFailureStatus(GLuint program, GLenum pname)
//{
//	int success = 0;
//	char infoLog[512];
//	glGetProgramiv(program, pname, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(program, 512, NULL, infoLog);
//		return std::string("ERROR::SHADER::VERTEX::COMPILATION_FAILED: ") + infoLog;
//	}
//
//	return std::string();
//}
//
//bool OpenGlApp::createWindow()
//{
//	window = glfwCreateWindow(600, 600, "Window", nullptr, nullptr);
//	if (!window)
//	{
//		std::cerr << "Can't create a window" << std::endl;
//		glfwTerminate();
//		return false;
//	}
//	return true;
//}

void Gl::VBO::generate(GLsizei n, GLuint* arrays)
{
	glGenBuffers(n, arrays);
	checkGLErrors();
}

void Gl::VBO::bind(GLenum target, GLuint buffer)
{
	glBindBuffer(target, buffer);
	id = buffer;
	checkGLErrors();
}

void Gl::VBO::unbind(GLenum target)
{
	glBindBuffer(target, 0u);
	id = invalidId;
	checkGLErrors();
}

bool Gl::VBO::isBind() 
{
	return id != invalidId;
}

void Gl::VBO::buffData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	if (!isBind())
		throw std::exception("VBO is not bound");
	else
		glBufferData(target, size, data, usage);
	checkGLErrors(); GL_ARRAY_BUFFER;
}

void Gl::VAO::generate(GLsizei n, GLuint* arrays)
{
	glGenVertexArrays(n, arrays);
	checkGLErrors();
}

void Gl::VAO::bind(GLuint array)
{
	glBindVertexArray(array);
	id = array;
	checkGLErrors();
}

void Gl::VAO::unbind()
{
	glBindVertexArray(0);
	id = invalidId;
	checkGLErrors();
}

bool Gl::VAO::isBind()
{
	return id != invalidId;
}

void Gl::VAO::enableVertexAttribArray(GLuint index)
{
	if (!isBind())
		throw std::exception("VAO is not bound");
	else
		glEnableVertexAttribArray(index);
	checkGLErrors();
}

void Gl::VAO::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
	GLsizei stride, const void* pointer)
{
	if (!isBind())
		throw std::exception("VAO is not bound");
	else {
		enableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, normalized, stride, &pointer);
		checkGLErrors();
	}
}

void Gl::VAO::disableVertexAttribArray(GLuint index)
{
	if (!isBind())
		throw std::exception("VAO is not bound");
	else {
		glDisableVertexAttribArray(index);
		checkGLErrors();
	}
}

void Gl::checkGLErrors()
{
	switch (glGetError())
	{
		case GL_INVALID_ENUM:
			throw std::exception("Set when an enumeration parameter is not legal");
		case GL_INVALID_VALUE:
			throw std::exception("Set when a value parameter is not legal");
		case GL_INVALID_OPERATION:
			throw std::exception("Set when the state for a command is not legal for its given parameters");
		case GL_STACK_OVERFLOW:
			throw std::exception("Set when a stack pushing operation causes a stack overflow");
		case GL_STACK_UNDERFLOW:
			throw std::exception("Set when a stack popping operation occurs while the stack is at its lowest point");
		case GL_OUT_OF_MEMORY:
			throw std::exception("Set when a memory allocation operation cannot allocate (enough) memory");
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			throw std::exception("Set when reading or writing to a framebuffer that is not complete");
	}
}

GLuint Gl::Shader::createAndLoadFromFile(const std::filesystem::path& path, const Type type)
{
	const std::string fileContent = Utils::getFileContent(path);
	GLuint shader = create(type);
	loadSource(shader, fileContent.data());
	compile(shader);
	return shader;
}

GLuint Gl::Shader::create(const Type type)
{
	GLuint shader = glCreateShader(static_cast<GLenum>(type));
	checkGLErrors();

	return shader;
}

GLint Gl::Shader::getShaderiv(GLuint shader, GLenum pname)
{
	GLint params = 0;
	glGetShaderiv(shader, pname, &params);

	checkGLErrors();

	return params;
}

void Gl::Shader::deleteShader(GLuint shader)
{
	glDeleteShader(shader);
	id = invalidId;
	checkGLErrors();
}

void Gl::Shader::compile(GLuint shader)
{
	glCompileShader(shader);
	checkGLErrors();
}

void Gl::Shader::loadSource(GLuint shader, const char* shaderSource)
{
	glShaderSource(shader, 1,&shaderSource, nullptr);
	id = shader;
	checkGLErrors();
}

GLuint Gl::Program::create()
{
	GLuint shaderProgram = glCreateProgram();
	checkGLErrors();
	return shaderProgram;
}

void Gl::Program::attachShader(GLuint shaderProgram, GLuint shader)
{
	glAttachShader(shaderProgram, shader);
	id = shaderProgram;
	checkGLErrors();
}

void Gl::Program::link(GLuint shaderProgram)
{
	if (!isAttached())
		throw std::exception("Shader program is not attached");
	else
		glLinkProgram(shaderProgram);
	checkGLErrors();
}

bool Gl::Program::isAttached()
{
	return id != invalidId;
}

void Gl::Program::deleteProgram(GLuint shaderProgram)
{
	glDeleteProgram(shaderProgram);
	id = invalidId;
	checkGLErrors();
}
