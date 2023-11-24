#include "VAO.h"

#include "Gl.h"

VAO::VAO(bool isGenerate, bool isBind)
{
	if (isGenerate)
	{
		generate();
	}
	if (isBind && isGenerated())
	{
		bind();
	}
}

VAO::VAO(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) : VAO(true, true)
{
	vertexAttribPointer(index, size, type, normalized, stride, pointer);
}

VAO::~VAO()
{
	destroy();
}

void VAO::generate()
{
	if (!isGenerated()) {
		Gl::VAO::generate(1, &id);
		if (!isGenerated())
			throw std::runtime_error("Can't to generate VAO");
	}
}

void VAO::bind()
{
	Gl::VAO::bind(id);
	isBind_ = true;
}

void VAO::unbind()
{
	Gl::VAO::unbind();
	isBind_ = false;
}

void VAO::destroy()
{
	if (isGenerated())
		glDeleteVertexArrays(1, &id);
		//Gl::VAO::deleteVertexArrays(1, &id);

	id = Gl::VAO::invalidId;
	isBind_ = false;
}

bool VAO::isGenerated() const
{
	return id != Gl::VAO::invalidId;
}

bool VAO::isBind() const
{
	return isBind_;
}

GLuint VAO::getId() const
{
	return id;
}

void VAO::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normilized,
	GLsizei stride, const void* pointer)
{
	Gl::VAO::vertexAttribPointer(index, size, type, normilized, stride, pointer);
}

//#include "VAO.h"
//
//VAO::VAO(bool isGenerate, bool isBind)
//{
//	if (isGenerate)
//		generate();
//	if (isBind && isGenerated())
//		bind();
//}
//
//VAO::VAO(GLuint index, GLint size, GLenum type, GLboolean normilized, GLsizei stride, const void* pointer) 
//	: VAO(true, true)
//{
//	vertexAttribPointer(index, size, type, normilized, stride, pointer);
//}
//
//void VAO::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normilized,
//	GLsizei stride, const void* pointer)
//{
//	Gl::VAO::vertexAttribPointer(index, size, type, normilized, stride, pointer);
//}
//
//VAO::~VAO()
//{
//	destroy();
//}
//
//void VAO::generate()
//{
//	if (!isGenerated()) {
//		Gl::VAO::generate(1, &id);
//		if (!isGenerated())
//			throw std::runtime_error("Can't to generate VAO");
//	}
//}
//
//void VAO::unbind()
//{
//	Gl::VAO::unbind();
//	isBind_ = false;
//}
//
//void VAO::bind() 
//{
//	Gl::VAO::bind(id);
//	isBind_ = true;
//}
//
//void VAO::destroy() 
//{
////	Gl::VAO::disableVertexAttribArray(id);
//	if (isGenerated())
//		Gl::VAO::deleteVertexArrays(1, &id);
//	id = Gl::VAO::invalidId;
//	isBind_ = false;
//}
//
//bool VAO::idBind() const
//{
//	return isBind_;
//}
//
//bool VAO::isGenerated() const
//{
//	return id != Gl::VAO::invalidId;
//}
//
//GLuint VAO::getId() const
//{
//	return id;
//}
//