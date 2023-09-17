#ifndef __BLOCKY_HPP__
#define __BLOCKY_HPP__

#include <iostream>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <renderer/renderer.hpp>
#include <game/global.hpp>
#include <chrono>

const bool LIGHTING = true;

static void glfw_error_callback(int error, const char *msg);
static void glfw_window_size_callback(GLFWwindow *window, int width, int height);
static void glfw_keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
static void glfw_mouse_callback(GLFWwindow *window, double xpos, double ypos);

class Renderer;
class Blocky{
    static void glfw_mouse_callback(GLFWwindow *window, double xpos, double ypos);

    public:
        Blocky(const int width, const int height);
        ~Blocky();

        void init();
        void loop();
        void clean();

        int get_screen_width() const;
        int get_screen_height() const;

        GLFWwindow* get_window() const;

        std::shared_ptr<Renderer> get_renderer() const;

    private: 
        int screen_width;
        int screen_height;

        GLFWwindow *window = nullptr;
        //std::shared_ptr<GLFWwindow> window;

        //Renderer *renderer = nullptr;
        std::shared_ptr<Renderer> renderer;
};

#endif