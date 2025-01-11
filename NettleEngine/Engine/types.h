#pragma once

//======================================
//
// NETTLE ENGINE - types.h
// 
// Types for use throughout the engine
// 
// This code is under the MIT license
// Daniel Turner - 2025
//
//======================================

#ifdef PLATFORM_PSX
#include "libpsn00b/psxgte.h"
#include "libpsn00b/psxgpu.h"
#endif

#ifdef PLATFORM_DESKTOP
#include <glm/vec2.hpp>
#endif

namespace Nettle {

	///
	/// 
	/// Fixed-Point
	/// 
	/// Based on https://github.com/raroni/fixie/blob/master/Library/Include/Fixie/Num.h
	/// 
	/// 

	constexpr int FIXED_STEP = 12;
	constexpr unsigned int FIXED_MASK = 0xFFFFFFFF >> (32 - FIXED_STEP);

	class Fixed {
	public:
		// Constructors
		Fixed() { }
		Fixed(int whole) { raw = whole << FIXED_STEP; }
		Fixed(int whole, int frac) { raw = (whole << FIXED_STEP) + frac; }
		Fixed(unsigned int _raw) : raw(_raw) { }

		int GetWhole() const { return raw >> FIXED_STEP; }
		int GetFrac() const { return raw & FIXED_MASK; }
		unsigned int GetRaw() const { return raw; }

		// Arthimetic
		Fixed operator+(Fixed const& rhs) {
			return Fixed(this->raw + rhs.raw);
		}
		Fixed operator+(int const& rhs) {
			return Fixed(this->GetWhole() + rhs);
		}
		Fixed& operator+=(Fixed const& rhs) {
			this->raw += rhs.raw;
			return *this;
		}
		Fixed& operator+=(int const& rhs) {
			this->raw += rhs << FIXED_STEP;
			return *this;
		}
		Fixed operator-(Fixed const& rhs) {
			return Fixed(this->raw - rhs.raw);
		}
		Fixed operator-(int const& rhs) {
			return Fixed(this->GetWhole() - rhs);
		}
		Fixed& operator-=(Fixed const& rhs) {
			this->raw -= rhs.raw;
			return *this;
		}
		Fixed& operator-=(int const& rhs) {
			this->raw -= rhs << FIXED_STEP;
			return *this;
		}
		Fixed operator*(Fixed const& rhs) {
			return Fixed(this->raw * rhs.raw);
		}
		Fixed operator*(int const& rhs) {
			return Fixed(this->raw * (rhs << FIXED_STEP));
		}
		Fixed& operator*=(Fixed const& rhs) {
			this->raw *= rhs.raw;
			return *this;
		}
		Fixed& operator*=(int const& rhs) {
			this->raw *= rhs << FIXED_STEP;
			return *this;
		}
		Fixed operator/(Fixed const& rhs) {
			Fixed out;

			int negative = ((this->raw ^ rhs.raw) & 0x8000000) >> 31;
			int sign = (negative * -2) + 1;
			unsigned int temp = this->raw << FIXED_STEP;

			temp += (rhs.raw / 2) * sign;
			out.raw = temp / rhs.raw;

			return out;
		}
		Fixed operator/(int const& rhs) {
			Fixed temp(this->raw);
			temp /= Fixed(rhs);
			return temp;
		}
		Fixed& operator/=(Fixed const& rhs) {
			int negative = ((this->raw ^ rhs.raw) & 0x8000000) >> 31;
			int sign = (negative * -2) + 1;
			unsigned int temp = this->raw << FIXED_STEP;

			temp += (rhs.raw / 2) * sign;
			this->raw = temp / rhs.raw;

			return *this;
		}
		Fixed& operator/=(int const& rhs) {
			*this /= Fixed(rhs);
			return *this;
		}
		Fixed operator++(int) { 
			this->raw += (1 << FIXED_STEP);
			return *this;
		}
		Fixed operator--(int) {
			this->raw -= (1 << FIXED_STEP);
			return *this;
		}
		Fixed operator%(Fixed rhs) {
			int here = *this;
			int there = rhs;
			return here % there;
		}

		// Logic

		bool operator==(const Fixed& rhs) { return this->raw && rhs.raw; }
		bool operator!=(const Fixed& rhs) { return !(*this == rhs); }
		bool operator<(const Fixed& rhs) { return this->raw < rhs.raw; }
		bool operator<=(const Fixed& rhs) { return this->raw <= rhs.raw; }
		bool operator>(const Fixed& rhs) { return this->raw > rhs.raw; }
		bool operator>=(const Fixed& rhs) { return this->raw >= rhs.raw; }

		// Conversion

		operator int() { return this->GetWhole(); }
#ifdef PLATFORM_DESKTOP
		operator float() { return static_cast<float>(this->raw) / (1 << FIXED_STEP); }
#endif // PLATFORM_DESKTOP


	private:
		unsigned int raw = 0;
	};

	///
	/// 
	/// Vector Types
	///
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
		Vector2i operator++(int) {
			this->x++;
			this->y++;
			return *this;
		}
		Vector2i operator--(int) {
			this->x--;
			this->y--;
			return *this;
		}

		// Logic

		bool operator==(const Vector2i& rhs) { return (this->x == rhs.x) && (this->y == rhs.y); }
		bool operator!=(const Vector2i& rhs) { return !(*this == rhs); }
		bool operator<(const Vector2i& rhs) { return (this->x < rhs.x) && (this->y < rhs.y); }
		bool operator<=(const Vector2i& rhs) { return (this->x <= rhs.x) && (this->y <= rhs.y); }
		bool operator>(const Vector2i& rhs) { return (this->x > rhs.x) && (this->y > rhs.y); }
		bool operator>=(const Vector2i& rhs) { return (this->x >= rhs.x) && (this->y >= rhs.y); }

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

	class Vector2f {
	public:
		// Constructors
		Vector2f() { };
		Vector2f(Fixed _x, Fixed _y) : x(_x), y(_y) { }

		// Arthfmetfc
		Vector2f operator+(Vector2f const& other) {
			return Vector2f(this->x + other.x, this->y + other.y);
		}
		Vector2f& operator+=(Vector2f const& rhs) {
			this->x += rhs.x;
			this->y += rhs.y;
			return *this;
		}
		Vector2f operator-(Vector2f const& other) {
			return Vector2f(this->x - other.x, this->y - other.y);
		}
		Vector2f& operator-=(Vector2f const& rhs) {
			this->x -= rhs.x;
			this->y -= rhs.y;
			return *this;
		}
		Vector2f operator*(Vector2f const& other) {
			return Vector2f(this->x * other.x, this->y * other.y);
		}
		Vector2f& operator*=(Vector2f const& rhs) {
			this->x *= rhs.x;
			this->y *= rhs.y;
			return *this;
		}
		Vector2f operator/(Vector2f const& other) {
			return Vector2f(this->x / other.x, this->y / other.y);
		}
		Vector2f& operator/=(Vector2f const& rhs) {
			this->x /= rhs.x;
			this->y /= rhs.y;
			return *this;
		}
		Vector2f& operator++() {
			this->x++;
			this->y++;
			return *this;
		}
		Vector2f& operator--() {
			this->x--;
			this->y--;
			return *this;
		}

		// Logic

		bool operator==(const Vector2f& rhs) { return (this->x == rhs.x) && (this->y == rhs.y); }
		bool operator!=(const Vector2f& rhs) { return !(*this == rhs); }
		bool operator<(const Vector2f& rhs) { return (this->x < rhs.x) && (this->y < rhs.y); }
		bool operator<=(const Vector2f& rhs) { return (this->x <= rhs.x) && (this->y <= rhs.y); }
		bool operator>(const Vector2f& rhs) { return (this->x > rhs.x) && (this->y > rhs.y); }
		bool operator>=(const Vector2f& rhs) { return (this->x >= rhs.x) && (this->y >= rhs.y); }

		// Conversion

		// Platform specific
#ifdef PLATFORM_PSX
		operator VECTOR() const {
			VECTOR out;
			out.vx = this->x.GetRaw();
			out.vy = this->y.GetRaw();
			return out;
		}
#endif
#ifdef PLATFORM_DESKTOP
		operator glm::vec2() const {
			return glm::vec2(this->x, this->y);
		}
#endif // PLATFORM_DESKTOP

		Fixed x = 0, y = 0;
	};

	///
	/// 
	/// Utility Types
	///
	/// 
	
	class iRect {
	public:
		iRect() { }
		iRect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) { }
		iRect(Vector2i pos, Vector2i size) : x(pos.x), y(pos.y), w(size.x), h(size.y) { }

#ifdef PLATFORM_PSX
		operator RECT() const {
			RECT out;
			out.x = x; out.y = y; out.w = w; out.h = h;
			return out;
		}
#endif // PLATFORM_PSX

		int x = 0, y = 0, w = 0, h = 0;
	};

	class fRect {
	public:
		fRect() { }
		fRect(Fixed _x, Fixed _y, Fixed _w, Fixed _h) : x(_x), y(_y), w(_w), h(_h) { }
		fRect(Vector2i pos, Vector2i size) : x(pos.x), y(pos.y), w(size.x), h(size.y) { }

#ifdef PLATFORM_PSX
		operator RECT() const {
			RECT out;
			out.x = x.GetRaw(); out.y = y.GetRaw(); out.w = w.GetRaw(); out.h = h.GetRaw();
			return out;
		}
#endif // PLATFORM_PSX

		Fixed x = 0, y = 0, w = 0, h = 0;
	};

	class Color {
	public:
		Color() { }
		Color(unsigned char _r, unsigned char _g, unsigned char _b) : r(_r), g(_g), b(_b) { }
		Color(Fixed _r, Fixed _g, Fixed _b) : r(_r.GetFrac() >> (FIXED_STEP - 8)), g(_g.GetFrac() >> (FIXED_STEP - 8)), b(_b.GetFrac() >> (FIXED_STEP - 8)) { }
		Color(short h, Fixed s, Fixed v) {
			// Taken from raylib - https://github.com/raysan5/raylib/blob/c53dd8a9310ad34f730ea853478dc77c8caff23d/src/rtextures.c#L4875
			// Red channel
			Fixed k = (Fixed(5) + Fixed(h) / Fixed(60)) % Fixed(6);
			Fixed t = Fixed(4) - k;
			k = (t < k) ? t : k;
			k = (k < Fixed(1)) ? k : Fixed(1);
			k = (k > Fixed()) ? k : Fixed();
			r = (v - v * s * k).GetFrac() >> (FIXED_STEP - 8);

			// Green channel
			k = (Fixed(3) + Fixed(h) / Fixed(60)) % Fixed(6);
			t = Fixed(4) - k;
			k = (t < k) ? t : k;
			k = (k < Fixed(1)) ? k : Fixed(1);
			k = (k > Fixed()) ? k : Fixed();
			g = (v - v * s * k).GetFrac() >> (FIXED_STEP - 8);

			// Blue channel
			k = (Fixed(1) + Fixed(h) / Fixed(60)) % Fixed(6);
			t = Fixed(4) - k;
			k = (t < k) ? t : k;
			k = (k < Fixed(1)) ? k : Fixed(1);
			k = (k > Fixed()) ? k : Fixed();
			b = (v - v * s * k).GetFrac() >> (FIXED_STEP - 8);
		}

		unsigned char r = 127, g = 127, b = 127;
	};

	///
	///
	/// Container Types
	/// 
	/// 
	
	template <typename T>
	class vector {
	public:
		vector() { }
		int push_back(T value) {
			size;
		}
	private:
		T* base;
		unsigned int size;
	};
}