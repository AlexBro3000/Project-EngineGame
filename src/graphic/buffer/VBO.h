#pragma once

#include<glad/glad.h>

class VBO
{
private:
	GLuint ID;

public:
	VBO(GLfloat* vertices, GLsizeiptr size);
	~VBO();

	void bind();
	void unbind();

private:

};