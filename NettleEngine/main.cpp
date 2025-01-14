///
///		Nettle Engine - Daniel Turner 2024
/// 
///		main.cpp
///		Example of how to use the engine with windows
/// 
/// 
///		This engine is under MIT licence
///

#include "nettle.h"

class Test : public Nettle::Game {
    bool Start() override { return true; };
    void Update() override {};
    void Render() override {};
    void End() override {};
};

int main() {
    /*glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported\n";

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

*/
    Test test;

    Nettle::Core::GetCore().Run(&test);

	return 0;
}