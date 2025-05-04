#pragma once
#include "../painter.h"
#include "types.h"
#include <vector>
#include <GLFW/glfw3.h>

namespace Nettle {
	namespace Render {
		class Voodoo : public Painter
		{
		public:
			struct SwapChainInfo {
			};

			struct Shader {
			};

			bool Init(tinystl::string gameName) override;
			bool Begin() override;
			void End() override;
			void Destroy() override;
		private:
			void SetupGraphicsPipeline();

			GLFWwindow* window = nullptr;
		};
	}
}