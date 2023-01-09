#ifndef __HUD_HPP__
#define __HUD_HPP__

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb_image.h>

#include <renderer/shader.hpp>
#include <game/global.hpp>
#include <game/blocky.hpp>

class HUD{
    public:
        HUD();
        ~HUD();

        void render(double delta);

    private:
        Shader *shader = nullptr;
        std::string fragment_file;
        std::string vertex_file;

        GLuint VAO;
        GLuint VBO;
        GLuint TBO;
        GLuint texture_id;
        GLuint shader_program_id;
};

#endif