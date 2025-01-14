#include "voodoo.h"

namespace Nettle {
    namespace Render {
        bool Voodoo::Init(tinystl::string gameName)
        {         
            GLFWmonitor* mon = glfwGetPrimaryMonitor();
            const GLFWvidmode* videoMode = glfwGetVideoMode(mon);

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);

            window = glfwCreateWindow(videoMode->width, videoMode->height, gameName.c_str(), NULL, nullptr);
            //glfwCreateWindowSurface()
            vkEnumerateInstanceExtensionProperties(nullptr, &vulkanExtensionCount, nullptr);
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
            glfwDestroyWindow(window);
        }
    }
}