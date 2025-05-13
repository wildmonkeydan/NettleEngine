#include "sprite.h"

namespace Nettle {
	namespace Render {
		Sprite::Sprite(Vector2i pos, iRect texRect)
		{
			position = pos;
			uv = Vector2i(texRect.x, texRect.y);
			size = Vector2i(texRect.w, texRect.h);
		}
	}
}