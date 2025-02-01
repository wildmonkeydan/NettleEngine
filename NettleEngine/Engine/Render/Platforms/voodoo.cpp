#include "voodoo.h"

#include <limits>
#include <algorithm>

namespace Nettle {
    namespace Render {
        bool Voodoo::Init(tinystl::string gameName)
        {   
            //
            // Window setup
            //

            GLFWmonitor* mon = glfwGetPrimaryMonitor();
            const GLFWvidmode* videoMode = glfwGetVideoMode(mon);

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);

            window = glfwCreateWindow(videoMode->width, videoMode->height, gameName.c_str(), NULL, nullptr);
            //glfwSetWindowMonitor(window, mon, 0, 0, videoMode->width, videoMode->height, GLFW_DONT_CARE);

            //
            // Vulkan setup
            //


            vkEnumerateInstanceExtensionProperties(nullptr, &vulkanExtensionCount, nullptr);


            // Create instance

            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = gameName.c_str();
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = "Nettle Engine";
            appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
            appInfo.apiVersion = VK_API_VERSION_1_0;

            VkInstanceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &appInfo;

            uint32_t glfwExtensionCount = 0;
            const char** glfwExtensions;

            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);


            createInfo.enabledExtensionCount = glfwExtensionCount;
            createInfo.ppEnabledExtensionNames = glfwExtensions;
            createInfo.enabledLayerCount = 0;
            
            // Do error checking later
            VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

            // Create surface

            glfwCreateWindowSurface(instance, window, nullptr, &surface);






            // Create device

            VkPhysicalDevice dummyDevice{};
            uint32_t deviceCount = 0;
            vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
            
            if (deviceCount > 0) {
                pdevices.assign(deviceCount, dummyDevice);
                vkEnumeratePhysicalDevices(instance, &deviceCount, pdevices.data());

                for (int i = 0; i < pdevices.capacity(); i++) {
                    VkPhysicalDeviceProperties deviceProperties;
                    vkGetPhysicalDeviceProperties(pdevices[i], &deviceProperties);

                    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                        deviceInUse = i;
                }
            }
            else {
                return false;
            }

            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(pdevices[deviceInUse], &queueFamilyCount, nullptr);

            queueFamilies.reserve(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(pdevices[deviceInUse], &queueFamilyCount, queueFamilies.data());

            for (int i = 0; i < queueFamilies.size(); i++) {
                if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
                    graphicsFamily = i;

                VkBool32 presentSupport = false;
                vkGetPhysicalDeviceSurfaceSupportKHR(pdevices[deviceInUse], i, surface, &presentSupport);
                if (presentSupport)
                    presentFamily = i;
            }






            VkDeviceQueueCreateInfo queueCreateInfo[2];
            float queuePriority = 1.f;

            // Graphics queue
            queueCreateInfo[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo[0].queueFamilyIndex = graphicsFamily;
            queueCreateInfo[0].queueCount = 1;
            queueCreateInfo[0].pQueuePriorities = &queuePriority;
            // Present queue
            queueCreateInfo[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo[1].queueFamilyIndex = presentFamily;
            queueCreateInfo[1].queueCount = 1;
            queueCreateInfo[1].pQueuePriorities = &queuePriority;

            VkPhysicalDeviceFeatures deviceFeatures{};

            deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

            VkDeviceCreateInfo deviceCreateInfo{};
            deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            deviceCreateInfo.pQueueCreateInfos = queueCreateInfo;
            deviceCreateInfo.queueCreateInfoCount = 2;
            deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
            deviceCreateInfo.enabledExtensionCount = deviceExtensions.size();
            deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();

            result = vkCreateDevice(pdevices[deviceInUse], &deviceCreateInfo, nullptr, &device);


            // Get queues
            vkGetDeviceQueue(device, graphicsFamily, 0, &graphicsQueue);
            vkGetDeviceQueue(device, presentFamily, 0, &presentQueue);





            // Create swap chain

            vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pdevices[deviceInUse], surface, &scInfo.capabilities);

            unsigned int formatCount;
            vkGetPhysicalDeviceSurfaceFormatsKHR(pdevices[deviceInUse], surface, &formatCount, nullptr);

            if (formatCount != 0) {
                scInfo.formats.resize(formatCount);
                vkGetPhysicalDeviceSurfaceFormatsKHR(pdevices[deviceInUse], surface, &formatCount, scInfo.formats.data());
            }

            unsigned int presentModeCount;
            vkGetPhysicalDeviceSurfacePresentModesKHR(pdevices[deviceInUse], surface, &presentModeCount, nullptr);

            if (presentModeCount != 0) {
                scInfo.presentModes.resize(presentModeCount);
                vkGetPhysicalDeviceSurfacePresentModesKHR(pdevices[deviceInUse], surface, &presentModeCount, scInfo.presentModes.data());
            }

            const VkSurfaceFormatKHR* pickedFormat = nullptr;
            VkPresentModeKHR pickedPresentMode = VK_PRESENT_MODE_FIFO_KHR;

            if (!scInfo.formats.empty() && !scInfo.presentModes.empty()) {

                // Find the ideal format if it exists
                for (const VkSurfaceFormatKHR& format : scInfo.formats) {
                    if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                        pickedFormat = &format;
                    }
                }

                if (!pickedFormat)
                    pickedFormat = &scInfo.formats[0];

                // Find mailbox if it exsists
                for (const VkPresentModeKHR& presentMode : scInfo.presentModes) {
                    if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
                        pickedPresentMode = presentMode;
                }
            }

            VkExtent2D swapExtent;
            if (scInfo.capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
                swapExtent = scInfo.capabilities.currentExtent;
            }
            else {
                int width, height;
                glfwGetFramebufferSize(window, &width, &height);

                swapExtent.width = std::clamp(swapExtent.width, scInfo.capabilities.minImageExtent.width, scInfo.capabilities.maxImageExtent.width);
                swapExtent.height = std::clamp(swapExtent.height, scInfo.capabilities.minImageExtent.height, scInfo.capabilities.maxImageExtent.height);
            }
            
            unsigned int imageCount = scInfo.capabilities.minImageCount + 1;
            if (scInfo.capabilities.maxImageCount > 0 && imageCount > scInfo.capabilities.maxImageCount) {
                imageCount = scInfo.capabilities.maxImageCount;
            }

            VkSwapchainCreateInfoKHR scCreateInfo{};
            scCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            scCreateInfo.surface = surface;
            scCreateInfo.minImageCount = imageCount;
            scCreateInfo.imageFormat = pickedFormat->format;
            scCreateInfo.imageColorSpace = pickedFormat->colorSpace;
            scCreateInfo.imageExtent = swapExtent;
            scCreateInfo.imageArrayLayers = 1;
            scCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

            unsigned int queueFamilyIndices[] = { graphicsFamily, presentFamily };

            if (graphicsFamily != presentFamily) {
                scCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
                scCreateInfo.queueFamilyIndexCount = 2;
                scCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
            }
            else {
                scCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
            }

            scCreateInfo.preTransform = scInfo.capabilities.currentTransform;
            scCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
            scCreateInfo.presentMode = pickedPresentMode;
            scCreateInfo.clipped = VK_TRUE;
            scCreateInfo.oldSwapchain = VK_NULL_HANDLE;

            vkCreateSwapchainKHR(device, &scCreateInfo, nullptr, &swapChain);



            return true;
        }
        bool Voodoo::Begin()
        {
            return !glfwWindowShouldClose(window);
        }
        void Voodoo::End()
        {
        }
        void Voodoo::Destroy()
        {
            vkDestroySwapchainKHR(device, swapChain, nullptr);
            vkDestroySurfaceKHR(instance, surface, nullptr);
            vkDestroyInstance(instance, nullptr);
            vkDestroyDevice(device, nullptr);
            glfwDestroyWindow(window);
        }
    }
}