#pragma once

#include "Gl.h"

#include <vector>

class VBO {
public:
	VBO() = default;
	VBO(const VBO&) = default;
	VBO& operator=(const VBO&) = default;

	VBO(bool isGenerate, bool isBind);
	explicit VBO(const std::vector<GLfloat>& data, GLenum usage = GL_STATIC_DRAW);
	~VBO();

	void generate();
	void bind();
	void unbind();
	void destroy();
	void setData(const std::vector<GLfloat>& data, GLenum usage = GL_STATIC_DRAW);

	[[nodiscard]] bool isBind() const;
	[[nodiscard]] bool isGenerated() const;

	[[nodiscard]] GLuint getId() const;
private:
	bool isBind_ = false;
	GLuint id = Gl::VBO::invalidId;
};