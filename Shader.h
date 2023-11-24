//#pragma once
//
//#include "Gl.h"
//
//#include <filesystem>
//
//class Shader 
//{
//public:
//	explicit Shader(Gl::Shader::Type type, bool shouldCreate = true);
//	Shader(const std::filesystem::path& path, Gl::Shader::Type type);
//	~Shader();
//
//	void create();
//	void loadFromFile(const std::filesystem::path& path);
//	void setType(Gl::Shader::Type type);
//	[[nodiscard]] Gl::Shader::Type getType() const;
//	void compile() const;
//	void setSource(const std::string& source);
//	[[nodiscard]] const std::string& getSource();
//	void deleteShader();
//	GLuint data() const;
//
//private:
//	std::string source_;
//	Gl::Shader::Type type_ = Gl::Shader::Type::FRAGMENT;
//	GLuint data_ = Gl::Shader::invalidId;
//};

#pragma once

#include "Gl.h"

#include <string>
#include <filesystem>

class Shader {
public:
	Shader() = default;
	explicit Shader(const Gl::Shader::Type type_, bool shouldCreate = true);
	Shader(const std::filesystem::path& path, const Gl::Shader::Type type_);
	Shader(const Shader&) = default;
	Shader& operator=(const Shader&) = default;
	~Shader();

	void loadFromFile(const std::filesystem::path& path);
	void compile();
	void setSource(const std::string& source_);
	void create();
	void deleteShader();

	void setType(Gl::Shader::Type type_);

	[[nodiscard]] const std::string& getSource() const;
	[[nodiscard]] Gl::Shader::Type getType() const;

	[[nodiscard]] GLuint getShader() const;

	[[nodiscard]] bool isCreate() const;
	[[nodiscard]] bool isCompile() const;

private:
	bool isCompile_ = false;
	GLuint shader = Gl::Shader::invalidId;
	Gl::Shader::Type type = Gl::Shader::Type::FRAGMENT;
	std::string source{};
		
};