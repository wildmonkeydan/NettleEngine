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
				VkSurfaceCapabilitiesKHR capabilities;
				tinystl::vector<VkSurfaceFormatKHR> formats;
				tinystl::vector<VkPresentModeKHR> presentModes;
			};

			bool Init(tinystl::string gameName) override;
			bool Begin() override;
			void End() override;
			void Destroy() override;
		private:
			GLFWwindow* window = nullptr;

			// Vulkan
			VkInstance instance;

			std::vector<VkPhysicalDevice> pdevices;
			VkDevice device;
			int deviceInUse = 0;

			std::vector<VkQueueFamilyProperties> queueFamilies;
			int graphicsFamily = 0;
			int presentFamily = 0;

			VkQueue graphicsQueue;
			VkQueue presentQueue;

			VkSwapchainKHR swapChain;
			std::vector<VkImage> swapChainImages;
			VkFormat swapChainFormat;
			VkExtent2D swapChainExtent;
			std::vector<VkImageView> swapChainImageViews;
			SwapChainInfo scInfo;

			VkSurfaceKHR surface;

			std::vector<const char*> deviceExtensions;
			unsigned int vulkanExtensionCount = 0;
		};
	}
}