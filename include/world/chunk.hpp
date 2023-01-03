#ifndef __CHUNK_HPP__
#define __CHUNK_HPP__

#include <vector>

#include <GL/glew.h>

#include <world/block.hpp>
#include <world/world.hpp>
#include <renderer/chunk_mesh.hpp>

class World;
class ChunkMesh;
class Chunk{
    public:
        Chunk(const int cx, const int cz, const unsigned char cw, const unsigned char cl, const unsigned char ch, World *world);
        ~Chunk();

        void generate();
        void buil_mesh();
        void render(GLuint &texture);

        Block get_block(unsigned char x, unsigned char y, unsigned char z) const;

        int get_cx() const;
        int get_cz() const;
    private:
        int cx;
        int cz;
        unsigned char cw;
        unsigned char cl;
        unsigned char ch;

        World *world = nullptr;

        std::vector<Block> blocks;
        ChunkMesh *chunk_mesh = nullptr;

};

#endif