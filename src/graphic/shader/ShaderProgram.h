#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

// vert Ч вершинный шейдер
// tesc Ч шейдер управлени€ тессел€цией
// tese Ч шейдер оценки тессел€ции
// geom Ч геометрический шейдер
// frag Ч фрагментный шейдер
// comp Ч вычислительный шейдер

class ShaderProgram
{
private:
	GLuint ID;

public:
	ShaderProgram();
	ShaderProgram(const std::string& file_vert, const std::string& file_frag);
	~ShaderProgram();

	GLuint getID();

	bool isCompiled() const;

	bool load(const std::string& file_vert, const std::string& file_frag);
	void use() const;

	template<typename T>
	void useUniform(const char* uniform, T value);

private:
	std::string readShaderCode(const std::string& file);

};

template<class>
inline constexpr bool always_false = false;

template<typename T>
inline void ShaderProgram::useUniform(const char* uniform, T value)
{
	this->use();
	GLint location = glGetUniformLocation(this->ID, uniform);

	if (location != -1) {
		if constexpr (std::is_same_v<T, int>) {
			glUniform1i(location, value);
		}
		else if constexpr (std::is_same_v<T, float>) {
			glad_glUniform1f(location, value);
		}
		else if constexpr (std::is_same_v<T, glm::vec2>) {
			glad_glUniform2f(location, value.x, value.y);
		}
		else if constexpr (std::is_same_v<T, glm::vec3>) {
			glad_glUniform3f(location, value.x, value.y, value.z);
		}
		else if constexpr (std::is_same_v<T, glm::vec4>) {
			glad_glUniform4f(location, value.x, value.y, value.z, value.w);
		}
		else if constexpr (std::is_same_v<T, glm::mat4>) {
			glad_glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		}
		else {
			static_assert(always_false<T>::value, "Unsupported uniform type");
		}
	}
	else {
		// std::cerr << "Uniform variable " << uniform << " not found in shader program." << std::endl;
	}
}




