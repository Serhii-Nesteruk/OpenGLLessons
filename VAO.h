#pragma once

#include "Gl.h"

class VAO {
public:
	VAO() = default;
	VAO(bool isGenerate, bool isBind);
	VAO(const VAO&) = default;
	VAO& operator=(const VAO&) = default;

	VAO(GLuint index, GLint size, GLenum type, GLboolean normilized,
		GLsizei stride, const void* pointer);
	~VAO();

	void generate();
	void bind();
	void unbind();
	void destroy();

	void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normilized,
		GLsizei stride, const void* pointer);

	[[nodiscard]] bool isBind() const;
	[[nodiscard]] bool isGenerated() const;

	[[nodiscard]] GLuint getId() const;

private:
	bool isBind_ = false;
	GLuint id = Gl::VAO::invalidId;
};