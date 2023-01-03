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
class Renderer{
    public:
        Renderer(Blocky *game);
        ~Renderer();

        void init();
        void draw();

        void input();
    private:
        Blocky *game = nullptr;
        Shader *shader = nullptr;

        
        World *world = nullptr;

        GLuint texture;


        glm::vec3 cameraPos = glm::vec3(0.0f, 60.0f, 20.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

};

#endif