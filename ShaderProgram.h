#pragma once

#include "Gl.h"

#include "glm/glm.hpp"

class ShaderProgram {
public:
	ShaderProgram() = default;
	ShaderProgram(const ShaderProgram&) = default;
	ShaderProgram& operator=(const ShaderProgram&) = default;
	
	ShaderProgram(bool shouldCreate);
	ShaderProgram(GLuint vertShader, GLuint fragShader);
	~ShaderProgram();

	void attachShader(GLuint shader);
	void create();
	void link();
	void use();
	void destroy();

	[[nodiscard]] bool isCreated() const;
	[[nodiscard]] GLuint getProgram() const;
	[[nodiscard]] GLint getProgramiv(GLenum pname);
	[[nodiscard]] bool isAttached() const;
	[[nodiscard]] bool isLinked() const;

	void uniform(const std::string& name, GLfloat v0);
	void uniform(const std::string& name, GLfloat v0, GLfloat v1);
	void uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2);
	void uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	void uniform(const std::string& name, GLint v0);
	void uniform(const std::string& name, GLint v0, GLint v1);
	void uniform(const std::string& name, GLint v0, GLint v1, GLint v2);
	void uniform(const std::string& name, GLint v0, GLint v1, GLint v2, GLint v3);
	void uniform(const std::string& name, GLuint v0);
	void uniform(const std::string& name, GLuint v0, GLuint v1);
	void uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2);
	void uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
	void uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat2& value);
	void uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat3& value);
	void uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat4& value);
	void uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat2x3& value);
	void uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat3x2& value);
	void uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat2x4& value);
	void uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat4x2& value);
	void uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat3x4& value);
	void uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat4x3& value);

private:
	void checkLinkStatus();

private:
	GLuint program = Gl::Program::invalidId;
	bool isAttached_ = false, isLinked_ = false;

};