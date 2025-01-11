#pragma once

#ifdef PLATFORM_PSX
#include "libpsn00b/psxgte.h"
#endif

#ifdef PLATFORM_DESKTOP
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#endif

namespace Nettle {

	///
	/// Vector Types
	///

	class Vector2i {
	public:
		// Constructors
		Vector2i() { };
		Vector2i(int _x, int _y) : x(_x), y(_y) { }

		// Arthimetic
		Vector2i operator+(Vector2i const& other) {
			return Vector2i(other.x + this->x, other.y + this->y);
		}
		Vector2i& operator+=(Vector2i const& rhs) {
			this->x += rhs.x;
			this->y += rhs.y;
			return *this;
		}
		Vector2i operator-(Vector2i const& other) {
			return Vector2i(this->x - other.x, this->y - other.y);
		}
		Vector2i& operator-=(Vector2i const& rhs) {
			this->x -= rhs.x;
			this->y -= rhs.y;
			return *this;
		}
		Vector2i operator*(Vector2i const& other) {
			return Vector2i(this->x * other.x, this->y * other.y);
		}
		Vector2i& operator*=(Vector2i const& rhs) {
			this->x *= rhs.x;
			this->y *= rhs.y;
			return *this;
		}
		Vector2i operator/(Vector2i const& other) {
			return Vector2i(this->x / other.x, this->y / other.y);
		}
		Vector2i& operator/=(Vector2i const& rhs) {
			this->x /= rhs.x;
			this->y /= rhs.y;
			return *this;
		}
		Vector2i& operator++() {
			this->x++;
			this->y++;
			return *this;
		}
		Vector2i& operator--() {
			this->x--;
			this->y--;
			return *this;
		}

		// Conversion



		// Platform specific
#ifdef PLATFORM_PSX
		operator DVECTOR() const {
			DVECTOR out;
			out.vx = this->x;
			out.vy = this->y;
			return out;
		}
#endif
#ifdef PLATFORM_DESKTOP
		operator glm::i32vec2() const {
			return glm::i32vec2(this->x, this->y);
		}
		operator glm::vec2() const {
			return glm::vec2(this->x, this->y);
		}
#endif // PLATFORM_DESKTOP


		int x = 0, y = 0;
	};
}