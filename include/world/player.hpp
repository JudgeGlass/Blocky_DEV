#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Player{
    public:
        Player();

        void render();

        void input();

        
    private:
};

#endif