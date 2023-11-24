#include "ShaderProgram.h"

#include "glm/gtc/type_ptr.hpp"

ShaderProgram::ShaderProgram(bool shouldCreate)
{
	if (shouldCreate)
		create();
}

ShaderProgram::ShaderProgram(GLuint vertShader, GLuint fragShader)
	: ShaderProgram(true)
{
	attachShader(vertShader);
	attachShader(fragShader);
	link();
}

ShaderProgram::~ShaderProgram()
{
	destroy();
}

void ShaderProgram::attachShader(GLuint shader)
{
	if (!isCreated())
		throw std::runtime_error("Shader program is not create");
//	Gl::Program::attachShader(shader, program);
	glAttachShader(program, shader);
	isAttached_ = true;
	isLinked_ = false;
}

void ShaderProgram::create()
{
	program = glCreateProgram();
	//program = Gl::Program::create();
}

void ShaderProgram::link()
{
	if (!isAttached())
		throw std::runtime_error("You can't to link the shader program, bacause the program is not attached");
	//Gl::Program::link(program);
	glLinkProgram(program);
	checkLinkStatus();

	isLinked_ = true;
}

void ShaderProgram::use()
{
	if (!isLinked())
		throw std::runtime_error("You can't to use the shader program, because the program is not linked");

	//Gl::Program::use(program);
	glUseProgram(program);
}

void ShaderProgram::destroy()
{
	if (isCreated())
		glDeleteProgram(program);
		//Gl::Program::deleteProgram(program);
	isAttached_ = false;
	isLinked_ = false;
	program = Gl::Program::invalidId;
}

bool ShaderProgram::isCreated() const 
{
	return program != Gl::Program::invalidId;
}

GLuint ShaderProgram::getProgram() const
{
	return program;
}

GLint ShaderProgram::getProgramiv(GLenum pname)
{
	return Gl::Program::getProgramiv(program, pname);
}

bool ShaderProgram::isAttached() const
{
	return isAttached_;
}

bool ShaderProgram::isLinked() const
{
	return isLinked_;
}

void ShaderProgram::uniform(const std::string& name, GLfloat v0)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniform1f(location, v0);
}

void ShaderProgram::uniform(const std::string& name, GLfloat v0, GLfloat v1)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	//Gl::Program::uniform2f(location, v0, v1);
	glUniform2f(location, v0, v1);
}

void ShaderProgram::uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniform3f(location, v0, v1, v2);
}

void ShaderProgram::uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniform4f(location, v0, v1, v2, v3);
}

void ShaderProgram::uniform(const std::string& name, GLint v0)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	//Gl::Program::uniform1i(location, v0);
	glUniform1i(location, v0);
}

void ShaderProgram::uniform(const std::string& name, GLint v0, GLint v1)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniform2i(location, v0, v1);
}

void ShaderProgram::uniform(const std::string& name, GLint v0, GLint v1, GLint v2)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniform3i(location, v0, v1, v2);
}

void ShaderProgram::uniform(const std::string& name, GLint v0, GLint v1, GLint v2, GLint v3)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniform4i(location, v0, v1, v2, v3);
}

void ShaderProgram::uniform(const std::string& name, GLuint v0)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniform1ui(location, v0);
}

void ShaderProgram::uniform(const std::string& name, GLuint v0, GLuint v1)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniform2ui(location, v0, v1);
}

void ShaderProgram::uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniform3ui(location, v0, v1, v2);
}

void ShaderProgram::uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniform4ui(location, v0, v1, v2, v3);
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat2& value)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniformMatrix2fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat3& value)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniformMatrix3fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat4& value)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	//Gl::Program::uniformMatrix4fv(location, count, transponse, glm::value_ptr(value));
	glUniformMatrix4fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat2x3& value)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniformMatrix2x3fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat3x2& value)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniformMatrix3x2fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat2x4& value)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniformMatrix2x4fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat4x2& value)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniformMatrix4x2fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat3x4& value)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniformMatrix3x4fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat4x3& value)
{
	GLint location = Gl::Program::getUniformLocation(program, name.data());
	Gl::Program::uniformMatrix4x3fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::checkLinkStatus()
{
	if (!getProgramiv(GL_LINK_STATUS)) {
		GLchar infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		throw std::runtime_error("Can't to link the shader program");
	}
}
