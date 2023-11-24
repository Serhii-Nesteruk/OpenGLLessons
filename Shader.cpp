#include "Shader.h"

#include "Utils.h"

Shader::Shader(const Gl::Shader::Type type_, bool shouldCreate)
{
	type = type_;
	if (shouldCreate)
		create();
}

Shader::Shader(const std::filesystem::path& path, const Gl::Shader::Type type)
	: Shader(type, true)
{
	loadFromFile(path);
	compile();
}

Shader::~Shader()
{
	deleteShader();
}

void Shader::loadFromFile(const std::filesystem::path& path)
{
	const std::string source = Utils::getFileContent(path);
	setSource(source);
}

void Shader::compile()
{
	Gl::Shader::compile(shader);

	checkCompileStatus();
	isCompile_ = true;
}

void Shader::setSource(const std::string& source_)
{
	source = source_;
	Gl::Shader::loadSource(shader, source.data());
}

void Shader::create()
{
	shader = Gl::Shader::create(type);
}

void Shader::deleteShader()
{
	//Gl::Shader::deleteShader(shader);
	glDeleteShader(shader);
	isCompile_ = false;
	shader = Gl::Shader::invalidId;
	source.clear();
}

const std::string& Shader::getSource() const
{
	return source;
}

Gl::Shader::Type Shader::getType() const
{
	return type;
}

GLuint Shader::getShader() const
{
	return shader;
}

bool Shader::isCreate() const
{
	return shader != Gl::Shader::invalidId;
}

bool Shader::isCompile() const
{
	return isCompile_;
}

void Shader::checkCompileStatus()
{
	if (!Gl::Shader::getShaderiv(shader, GL_COMPILE_STATUS))
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		throw std::runtime_error("Failed to create shader");
	}
}
