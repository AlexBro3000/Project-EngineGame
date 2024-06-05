#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace DT
{
	// Vector 2
	typedef glm::vec<2, std::int8_t,   glm::defaultp>	vec2_i8;
	typedef glm::vec<2, std::int16_t,  glm::defaultp>	vec2_i16;
	typedef glm::vec<2, std::int32_t,  glm::defaultp>	vec2_i32;
	typedef glm::vec<2, std::int64_t,  glm::defaultp>	vec2_i64;

	typedef glm::vec<2, std::uint8_t,  glm::defaultp>	vec2_u8;
	typedef glm::vec<2, std::uint16_t, glm::defaultp>	vec2_u16;
	typedef glm::vec<2, std::uint16_t, glm::defaultp>	vec2_u32;
	typedef glm::vec<2, std::uint16_t, glm::defaultp>	vec2_u64;

	typedef glm::vec<2, float, glm::defaultp>			vec2_f32;
	typedef glm::vec<2, double, glm::defaultp>			vec2_f64;

	// Vector 3
	typedef glm::vec<3, std::int8_t,   glm::defaultp>	vec3_i8;
	typedef glm::vec<3, std::int16_t,  glm::defaultp>	vec3_i16;
	typedef glm::vec<3, std::int32_t,  glm::defaultp>	vec3_i32;
	typedef glm::vec<3, std::int64_t,  glm::defaultp>	vec3_i64;

	typedef glm::vec<3, std::uint8_t,  glm::defaultp>	vec3_u8;
	typedef glm::vec<3, std::uint16_t, glm::defaultp>	vec3_u16;
	typedef glm::vec<3, std::uint16_t, glm::defaultp>	vec3_u32;
	typedef glm::vec<3, std::uint16_t, glm::defaultp>	vec3_u64;

	typedef glm::vec<3, float, glm::defaultp>			vec3_f32;
	typedef glm::vec<3, double, glm::defaultp>			vec3_f64;
}