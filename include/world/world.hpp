#ifndef __WORLD_HPP__
#define __WORLD_HPP__

#include <vector>

#include <GL/glew.h>

#include <world/chunk.hpp>
#include <world/player.hpp>

class Chunk;
class Player;
class World{
    public:
        World(int width, int depth);
        ~World();

        void generate();

        void render(GLuint &texture);

        Chunk* get_chunk(int cx, int cz);

        std::vector<Chunk*> get_chunks();

        Player* get_player();
        

    private:
        int width;
        int depth;
        Player *player = nullptr;
        std::vector<Chunk*> chunks;
};


#endif