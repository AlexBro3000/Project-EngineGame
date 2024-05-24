#pragma once

#include<glad/glad.h>

class EBO
{
private:
	GLuint ID;

public:
	EBO(GLuint* indices, GLsizeiptr size);
	~EBO();

	void bind();
	void unbind();

private:

};