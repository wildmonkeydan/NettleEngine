#include "voodoo.h"

#include <limits>
#include <algorithm>
#include <fstream>

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

            SetupGraphicsPipeline();

            return true;
        }

        void Voodoo::SetupGraphicsPipeline()
        {
            
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