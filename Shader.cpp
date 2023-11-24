//#include "Shader.h"
//
//#include "Utils.h"
//
//Shader::Shader(Gl::Shader::Type type, bool shouldCreate /* = true*/)
//{
//	setType(type);
//	if (shouldCreate)
//	{
//		create();
//	}
//}
//
//Shader::Shader(const std::filesystem::path& path, Gl::Shader::Type type) : Shader(type, true)
//{
//	loadFromFile(path);
//	compile();
//}
//
//void Shader::create()
//{
//	data_ = Gl::Shader::create(type_);
//}
//
//void Shader::loadFromFile(const std::filesystem::path& path)
//{
//	setSource(source_ = Utils::getFileContent(path));
//}
//
//void Shader::setType(Gl::Shader::Type type)
//{
//	type_ = type;
//}
//
//Gl::Shader::Type Shader::getType() const
//{
//	return type_;
//}
//
//void Shader::compile() const
//{
//	Gl::Shader::compile(data_);
//}
//
//const std::string& Shader::getSource()
//{
//	return source_;
//}
//
//void Shader::deleteShader()
//{
//	//Gl::Shader::deleteShader(data_);
//	glDeleteShader(data_);
//
//	data_ = Gl::Shader::invalidId;
//	source_.clear();
//}
//
//GLuint Shader::data() const
//{
//	return data_;
//}
//
//Shader::~Shader()
//{
//	deleteShader();
//}
//
//void Shader::setSource(const std::string& source)
//{
//	source_ = source;
//	Gl::Shader::loadSource(data_, source_.c_str());
//}

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

	if (!Gl::Shader::getShaderiv(shader, GL_COMPILE_STATUS))
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		throw std::runtime_error("Failed to create shader");
	}
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
