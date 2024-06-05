#pragma once

#include <glad/glad.h>
#include <stb_image.h>

#include "../shader/ShaderProgram.h"

class Texture
{
private:
	GLuint ID;

public:
	Texture(const char* file, GLenum type, GLenum slot, GLenum pxl_format, GLenum pxl_type);
	~Texture();

	void useShaderUniform(ShaderProgram& shader, const char* uniform, int value);

	void bind();
	void unbind();

private:

};