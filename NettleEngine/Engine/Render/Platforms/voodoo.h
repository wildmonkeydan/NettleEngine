#pragma once
#include "../painter.h"
#include "types.h"
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

			// Vulkan
			VkInstance instance;

			tinystl::vector<VkPhysicalDevice> pdevices;
			VkDevice device;
			int deviceInUse = 0;

			tinystl::vector<VkQueueFamilyProperties> queueFamilies;
			int graphicsFamily = 0;
			int presentFamily = 0;

			VkQueue graphicsQueue;
			VkQueue presentQueue;

			VkSurfaceKHR surface;

			unsigned int vulkanExtensionCount = 0;
		};
	}
}