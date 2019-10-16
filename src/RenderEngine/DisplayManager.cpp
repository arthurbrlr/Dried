#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "GraphicInterface/DebugInterface.h"
#include "RenderEngine/DisplayManager.h"

namespace RenderEngine {
    int DisplayManager::Init () {
        /* Initialize the GLFW library */
        if (!glfwInit()) {
            #ifdef DDEBUG
                std::cout << "ERROR: GLFW Init" << std::endl;
            #endif
            return -1;
        }

        /* Set the version of OpenGL used in the project */
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        /* Set the profile used for OpenGL */
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwSwapInterval(0);

        /* Create a windowed mode window and its OpenGL context */
        _wWidth = WINDOW_WIDTH; _wHeight = WINDOW_HEIGHT;
        _window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dried", NULL, NULL);
        if (!_window) {
            glfwTerminate();
            #ifdef DDEBUG
                std::cout << "ERROR: GLFW Create Window" << std::endl;
            #endif
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(_window);
        /* Set the viewport */
        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        /* Set the resize callback */
        glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
        /* Enable Depth test */
        glEnable(GL_DEPTH_TEST);
        /* Mouse Input Mode */
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        /* Face Culling */
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);


        /* Initialize the GLEW library in the current context */
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            #ifdef DDEBUG
                std::cout << "ERROR: GLEW Init" << std::endl;
            #endif
            return -1;
        }

        #ifdef DDEBUG
            std::cout << glGetString(GL_VERSION) << std::endl;
        #endif

        _lastFrameTime = glfwGetTime();

        return 1;
    }

    void DisplayManager::StartFrame () {
        if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(_window, true);
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void DisplayManager::EndFrame () {
        GraphicInterface::DebugInterface::GetInstance().Render();
        glfwSwapBuffers(_window);
        glfwPollEvents();

        _deltaTime = glfwGetTime() - _lastFrameTime;
        _lastFrameTime = glfwGetTime();
    }

    void DisplayManager::Clear () {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }
}
