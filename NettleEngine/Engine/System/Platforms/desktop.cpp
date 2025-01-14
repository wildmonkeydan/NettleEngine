#ifdef PLATFORM_DESKTOP

#include "desktop.h"

#include <GLFW/glfw3.h>

namespace Nettle {
    namespace System {
        bool Desktop::Init()
        {
            glfwInit();
            prevTime = glfwGetTime();
            return true;
        }
        bool Desktop::BeginLoop(bool isFocused)
        {
            prevTime = glfwGetTime();
            glfwPollEvents();
            return true;
        }
        Fixed Desktop::EndLoop(bool isFocused)
        {
            double deltaTime = glfwGetTime() - prevTime;
            unsigned int fixedDelta = deltaTime * (1 << FIXED_STEP);

            return Fixed(fixedDelta);
        }
        void Desktop::Destroy()
        {
            glfwTerminate();
        }
    }
}

#endif // PLATFORM_DESKTOP