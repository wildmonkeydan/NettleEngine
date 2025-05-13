#pragma once
#include "../types.h"

namespace Nettle {
	namespace Render {
		class Sprite
		{
		public:
			Sprite() {};
			Sprite(Vector2i pos, iRect texRect);

			Vector2i& GetPosition() { return position; }
			Vector2i& GetUV() { return uv; }
			Vector2i& GetSize() { return size; }
		private:
			Vector2i position, uv, size;
		};
	}
}