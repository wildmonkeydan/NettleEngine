#pragma once
#include "../types.h"

namespace Nettle {
	namespace Render {
		class Painter
		{
		public:
			virtual bool Init(tinystl::string gameName) = 0;
			virtual bool Begin() = 0;
			virtual void End() = 0;
			virtual void Destroy() = 0;
		private:
			Color background;
		};
	}
}