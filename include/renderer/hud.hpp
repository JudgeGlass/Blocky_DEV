#ifndef __HUD_HPP__
#define __HUD_HPP__

#include <string>
#include <vector>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <renderer/shader.hpp>
#include <renderer/font.hpp>
#include <game/global.hpp>
#include <game/blocky.hpp>

class Player;
class HUD{
    public:
        HUD(std::shared_ptr<Player> player);
        ~HUD();

        void render(double delta);

    private:
        std::shared_ptr<Player> player;

        void drawDebug();
};

#endif