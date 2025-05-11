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

            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window = glfwCreateWindow(videoMode->width, videoMode->height, gameName.c_str(), mon, nullptr);
            glfwMakeContextCurrent(window);

            SetupGraphicsPipeline();

            return true;
        }

        void Voodoo::SetupGraphicsPipeline()
        {
            gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            int w = 0, h = 0;
            glfwGetWindowSize(window, &w, &h);
            glViewport(0, 0, w, h);


            // Setup framebuffer
            glGenFramebuffers(1, &framebuffer.fboId);
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.fboId);

            // Make colour texture
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glGenTextures(1, &framebuffer.colourId);
            glBindTexture(GL_TEXTURE_2D, framebuffer.colourId);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 320, 240, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glBindTexture(GL_TEXTURE_2D, 0);

            // Make depth texture
            glGenRenderbuffers(1, &framebuffer.depthId);
            glBindRenderbuffer(GL_RENDERBUFFER, framebuffer.depthId);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 320, 240);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);

            // Bind the textures to FBO
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.fboId);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebuffer.fboId, 0);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_FRAMEBUFFER, framebuffer.depthId);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            // Tests
            const char* vertexShaderSource = "#version 330 core\n"
                "layout (location = 0) in vec3 aPos;\n"
                "void main()\n"
                "{\n"
                "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                "}\0";

            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
            glCompileShader(vertexShader);

            const char* fragmentShaderSource = "#version 330 core\n"
                "out vec4 FragColor;\n"
                "void main()\n"
                "{\n"
                "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                "}\n\0";

            
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
            glCompileShader(fragmentShader);

            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                 0.5f, -0.5f, 0.0f,
                 0.0f,  0.5f, 0.0f
            };  

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        bool Voodoo::Begin()
        {
            glClearColor((float)((float)background.r/255.f), (float)((float)background.g / 255.f), (float)((float)background.b / 255.f), 1.f);
            glClear(GL_COLOR_BUFFER_BIT);
            return !glfwWindowShouldClose(window);
        }

        void Voodoo::End()
        {
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
        }

        void Voodoo::Destroy()
        {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteProgram(shaderProgram);
            glfwDestroyWindow(window);
            glfwTerminate();
        }
    }
}