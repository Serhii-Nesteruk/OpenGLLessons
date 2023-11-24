#include "VBO.h"

VBO::VBO(bool isGenerate, bool isBind)
{
	if (isGenerate)
		generate();
	if (isBind && isGenerated())
		bind();
}

VBO::VBO(const std::vector<GLfloat>& data, GLenum usage) : VBO(true, true)
{
	setData(data, usage);
}

VBO::~VBO()
{
	destroy();
}

void VBO::generate()
{
	if (!isGenerated()) {
		Gl::VBO::generate(1, &id);
		if (!isGenerated())
			throw std::runtime_error("Can't to generate VBO");
	}
}

void VBO::bind()
{
	Gl::VBO::bind(GL_ARRAY_BUFFER, id);
	isBind_ = true;
}

void VBO::unbind()
{
	Gl::VBO::unbind(GL_ARRAY_BUFFER);
	isBind_ = false;
}

void VBO::destroy()
{
	if (isGenerated())
		glGenBuffers(1, &id);
		//Gl::VBO::deleteBuffers(1, &id);
	id = Gl::VBO::invalidId;
	isBind_ = false;
}

void VBO::setData(const std::vector<GLfloat>& data, GLenum usage)
{
	if (!isBind())
		throw std::runtime_error("VBO is not bind");
	if (!isGenerated())
		throw std::runtime_error("VBO is not generate");
	Gl::VBO::buffData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), usage);
}

bool VBO::isBind() const
{
	return isBind_;
}

bool VBO::isGenerated() const
{
	return id != Gl::VBO::invalidId;
}

GLuint VBO::getId() const
{
	return id;
}
