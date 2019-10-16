#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

/*
    Display Manager singleton : handles the display

    Responsible for:
        - initializing OpenGL, GLFW, GLEW,
        - Starting and ending frames,
        - Clearing every context when the app is closing,
        - the projection matrix,
        - etc..
*/

namespace RenderEngine {
    class DisplayManager {
        private:
            GLFWwindow* _window;
            float _lastFrameTime, _deltaTime = 0;
            float _wWidth, _wHeight;

            static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
                glViewport(0, 0, width, height);
                DisplayManager::GetInstance().SetSize(width, height);
            };

            static DisplayManager* instance;
            DisplayManager(){};

        public:
            DisplayManager(DisplayManager const&) = delete;
            void operator=(DisplayManager const&) = delete;
            static DisplayManager& GetInstance () {
                static DisplayManager instance;
                return instance;
            };

            int Init ();
            void StartFrame();
            void EndFrame ();
            void Clear ();

                /* Setter */
            void SetSize (const float & width, const float & height) {_wWidth = width; _wHeight = height;};

                /* Getters */
            GLFWwindow* const GetWindow () {return _window;};
            float const DeltaTime () {return _deltaTime;};
            float const GetTime () {return _lastFrameTime;};
            float const GetWidth () {return _wWidth;};
            float const GetHeight () {return _wHeight;};
            float const GetAspect () {return _wWidth/_wHeight;};
            glm::mat4 GetProjectionMatrix () {
                return glm::perspective(glm::radians(45.0f), _wWidth / _wHeight, 0.1f, 300.0f);
            };
    };
}

#endif
