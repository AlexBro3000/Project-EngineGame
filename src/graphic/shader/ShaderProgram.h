#pragma once

#include <glad/glad.h>
#include <string>

// vert � ��������� ������
// tesc � ������ ���������� �����������
// tese � ������ ������ ����������
// geom � �������������� ������
// frag � ����������� ������
// comp � �������������� ������

class ShaderProgram
{
private:
	GLuint ID;

public:
	ShaderProgram();
	ShaderProgram(const std::string& file_vert, const std::string& file_frag);
	~ShaderProgram();

	bool load(const std::string& file_vert, const std::string& file_frag);
	void use() const;

	bool isCompiled() const;

	// _uint32_t getID();
	// void useUniformMatrix4f(std::string name, glm::mat4 matrix);

private:
	std::string readShaderCode(const std::string& file);

};

//#include <glm/glm.hpp>
//#include <glm/ext.hpp>