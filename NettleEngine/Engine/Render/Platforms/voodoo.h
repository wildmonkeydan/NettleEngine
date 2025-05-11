#pragma once
#include "../painter.h"
#include "types.h"
#include <vector>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace Nettle {
	namespace Render {
		class Voodoo : public Painter
		{
		public:
			struct Framebuffer {
				unsigned int fboId = 0;
				unsigned int colourId = 0;
				unsigned int depthId = 0;
			};

			bool Init(tinystl::string gameName) override;
			bool Begin() override;
			void End() override;
			void Destroy() override;
		private:
			void SetupGraphicsPipeline();

			GLFWwindow* window = nullptr;

			unsigned int fragmentShader, vertexShader, shaderProgram, VBO, VAO;
			Framebuffer framebuffer{};
		};
	}
}