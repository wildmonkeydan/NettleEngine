#pragma once

#ifdef PLATFORM_PSX
#include "psxgte.h"
#endif // PLATFORM_PSX


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
#ifdef PLATFORM_PSX
		operator DVECTOR() const {
			DVECTOR out;
			out.vx = this->x;
			out.vy = this->y;
			return out;
		}
#endif // PLATFORM_PSX


		int x = 0, y = 0;
	};
}