#include "voodoo.h"

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
            glfwSetWindowMonitor(window, mon, 0, 0, videoMode->width, videoMode->height, GLFW_DONT_CARE);

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

            uint32_t deviceCount = 0;
            vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
            
            if (deviceCount > 0) {
                pdevices.reserve(deviceCount);
                vkEnumeratePhysicalDevices(instance, &deviceCount, pdevices.data());

                for (int i = 0; i < pdevices.size(); i++) {
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

            VkDeviceCreateInfo deviceCreateInfo{};
            deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            deviceCreateInfo.pQueueCreateInfos = queueCreateInfo;
            deviceCreateInfo.queueCreateInfoCount = 2;
            deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

            result = vkCreateDevice(pdevices[deviceInUse], &deviceCreateInfo, nullptr, &device);


            // Get queues
            vkGetDeviceQueue(device, graphicsFamily, 0, &graphicsQueue);
            vkGetDeviceQueue(device, presentFamily, 0, &presentQueue);


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
            vkDestroySurfaceKHR(instance, surface, nullptr);
            vkDestroyInstance(instance, nullptr);
            vkDestroyDevice(device, nullptr);
            glfwDestroyWindow(window);
        }
    }
}