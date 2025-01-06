#pragma once
#include "system.h"

namespace Nettle {
	namespace System {
		class Desktop : public System
		{
		public:
			bool Init() override;
			bool BeginLoop(bool isFocused) override;
			float EndLoop(bool isFocused) override;
			void Destroy() override;
		};
	}
}

