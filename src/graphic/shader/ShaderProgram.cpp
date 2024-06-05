#include "ShaderProgram.h"

#include "../../system/console/Console.h"
#include <sstream>
#include <fstream>

ShaderProgram::ShaderProgram()
{
	ID = 0;
}

ShaderProgram::ShaderProgram(const std::string& file_vert, const std::string& file_frag) : ShaderProgram()
{
	load(file_vert, file_frag);
}

ShaderProgram::~ShaderProgram()
{
	if (ID) {
		glDeleteProgram(ID);
	}
}

GLuint ShaderProgram::getID()
{
	return ID;
}

bool ShaderProgram::isCompiled() const
{
	if (ID) {
		return true;
	}
	return false;
}

bool ShaderProgram::load(const std::string& file_vert, const std::string& file_frag)
{
	std::string vert_code, frag_code;
	GLuint VS, FS, shader_program;
	GLint success;

	// Vertex Shader
	vert_code = readShaderCode(file_vert);
	const GLchar* vert_shader_code = vert_code.c_str();

	VS = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VS, 1, &vert_shader_code, nullptr);
	glCompileShader(VS);

	glGetShaderiv(VS, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(VS, 512, nullptr, infoLog);

		glDeleteShader(VS);
		Console::Warn("Failed to compile vertex shader.", infoLog);
		return false;
	}

	// Fragment Shader
	frag_code = readShaderCode(file_frag);
	const GLchar* frag_shader_code = frag_code.c_str();

	FS = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FS, 1, &frag_shader_code, nullptr);
	glCompileShader(FS);

	glGetShaderiv(FS, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[512];
		glGetShaderInfoLog(FS, 512, nullptr, infoLog);

		glDeleteShader(VS);
		glDeleteShader(FS);
		Console::Warn("Failed to compile fragment shader.", infoLog);
		return false;
	}

	// Shader Program
	shader_program = glCreateProgram();
	glAttachShader(shader_program, VS);
	glAttachShader(shader_program, FS);
	glLinkProgram(shader_program);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (success) {
		if (ID) {
			glDeleteProgram(ID);
		}
		ID = shader_program;
	}
	else {
		GLchar infoLog[512];
		glGetProgramInfoLog(shader_program, 512, nullptr, infoLog);

		glDeleteShader(VS);
		glDeleteShader(FS);
		glDeleteProgram(shader_program);
		Console::Warn("Failed to link shader program.", infoLog);
		return false;
	}

	glDeleteShader(VS);
	glDeleteShader(FS);
	return true;
}

void ShaderProgram::use() const
{
	glUseProgram(ID);
}

std::string ShaderProgram::readShaderCode(const std::string& file)
{
	std::string shader_code = std::string();

	try
	{
		std::ifstream shader_file(file);
		shader_file.exceptions(std::ifstream::badbit);
		
		if (shader_file.is_open()) {
			std::stringstream shader_stream;
			shader_stream << shader_file.rdbuf();
			shader_code = shader_stream.str();

			Console::Info("The shader file was read successfully.", ("src: " + file).c_str());
		}
		else {
			Console::Warn("Failed to open shader file.", ("src: " + file).c_str());
		}
	}
	catch (std::ifstream::failure& exc)
	{
		Console::Warn("Failed to read shader file.", ("src: " + file).c_str());
	}

	return shader_code;
}