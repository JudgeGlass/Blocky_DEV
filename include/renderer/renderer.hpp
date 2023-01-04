#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <game/blocky.hpp>
#include <renderer/shader.hpp>
#include <world/world.hpp>
#include <stb_image.h>

class Blocky;
class World;
class Renderer{
    public:
        Renderer(Blocky *game);
        ~Renderer();

        void init();
        void draw(double &mouse_x, double &mouse_y);

    private:
        Blocky *game = nullptr;
        Shader *shader = nullptr;

        
        World *world = nullptr;

        GLuint texture;
};

#endif