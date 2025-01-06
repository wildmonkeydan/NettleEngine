#pragma once

namespace Nettle {
	namespace System {
		class System {
		public:
			virtual bool Init() = 0;
			virtual bool BeginLoop(bool isFocused) = 0;
			// REPLACE WITH FIXED-POINT
			virtual float EndLoop(bool isFocused) = 0;
			virtual void Destroy() = 0;
		};
	}
}