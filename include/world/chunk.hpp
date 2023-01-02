#ifndef __CHUNK_HPP__
#define __CHUNK_HPP__

#include <vector>

#include <GL/glew.h>

#include <world/block.hpp>
#include <renderer/chunk_mesh.hpp>

class Chunk{
    public:
        Chunk(const int cx, const int cy, const unsigned char cw, const unsigned char cl, const unsigned char ch);
        ~Chunk();

        void generate();
        void render(GLuint &texture);
    private:
        int cx;
        int cy;
        unsigned char cw;
        unsigned char cl;
        unsigned char ch;

        std::vector<Block> blocks;
        ChunkMesh *chunk_mesh = nullptr;

};

#endif