#ifndef __BLOCKY_HPP__
#define __BLOCKY_HPP__

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static void glfw_error_callback(int error, const char *msg);
static void glfw_window_size_callback(GLFWwindow *window, int width, int height);

class Blocky{
    public:
        Blocky(const int width, const int height);
        ~Blocky();

        void init();
        void loop();
        void clean();

        int get_screen_width() const;
        int get_screen_height() const;

    private: 
        int screen_width;
        int screen_height;

        GLFWwindow *window = nullptr;

};

#endif