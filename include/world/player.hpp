#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <game/blocky.hpp>
#include <renderer/shader.hpp>
#include <world/world.hpp>

#include <world/ray.hpp>

class Blocky;
class Player{
    public:
        Player(glm::vec3 pos, World *world);

        void render(Shader *shader);
        void update(Blocky *game, double delta);

        void input(Blocky *game, double delta);

        void set_mouse_pos(const double x, const double y);

        const glm::vec3& get_pos() const;
        
    private:
        double mouse_x = 0.0f;
        double mouse_y = 0.0f;
        double click_sleep = 0.0f; // 250ms
        float yaw = -90.0f;
        float pitch = 0.0;
        float last_x = 1024/2;
        float last_y = 768/2;
        bool first_mouse = true;
        glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);

        World *world = nullptr;       
};

#endif