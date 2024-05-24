#pragma once

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
private:
	GLuint ID;

public:
	VAO();
	~VAO();

	void linkAttrib(VBO& VBO, GLuint layout, GLuint components, GLenum type, GLsizeiptr stride, void* offset);
	void bind();
	void unbind();

private:

};