#include "desktop.h"

#include <GLFW/glfw3.h>

namespace Nettle {
    namespace System {
        bool Desktop::Init()
        {
            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

            return true;
        }
        bool Desktop::BeginLoop(bool isFocused)
        {
            return false;
        }
        float Desktop::EndLoop(bool isFocused)
        {
            return 0.0f;
        }
        void Desktop::Destroy()
        {
            glfwTerminate();
        }
    }
}