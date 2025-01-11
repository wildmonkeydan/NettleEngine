#pragma once
#include "../types.h"

namespace Nettle {
	namespace System {
		class System {
		public:
			virtual bool Init() = 0;
			virtual bool BeginLoop(bool isFocused) = 0;
			virtual Fixed EndLoop(bool isFocused) = 0;
			virtual void Destroy() = 0;
		};
	}
}