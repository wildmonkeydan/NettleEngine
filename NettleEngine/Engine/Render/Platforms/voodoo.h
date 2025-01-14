#pragma once
#include "../painter.h"
#include <GLFW/glfw3.h>

namespace Nettle {
	namespace Render {
		class Voodoo : public Painter
		{
		public:
			bool Init(tinystl::string gameName) override;
			bool Begin() override;
			void End() override;
			void Destroy() override;
		private:
			GLFWwindow* window = nullptr;
			VkSurfaceKHR surface;
			unsigned int vulkanExtensionCount = 0;
		};
	}
}