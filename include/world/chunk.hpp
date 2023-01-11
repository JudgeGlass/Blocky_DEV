#ifndef __CHUNK_HPP__
#define __CHUNK_HPP__

#include <vector>

#include <GL/glew.h>

#include <world/block.hpp>
#include <world/world.hpp>
#include <world/SimplexNoise.h>
#include <renderer/chunk_mesh.hpp>

#include <renderer/lighting.hpp>

class World;
class ChunkMesh;
class Chunk{
    public:
        Chunk(const int cx, const int cz, const unsigned char cw, const unsigned char cl, const unsigned char ch, World *world);
        ~Chunk();

        void generate();
        void build_mesh();
        void rebuild_mesh();
        void build_lighting();
        void render(GLuint texture);
        void render_transparent(GLuint texture);

        void set_block(Block b);

        Block& get_block(unsigned char x, unsigned char y, unsigned char z);

        int get_cx() const;
        int get_cz() const;

        void set_disable_faces(bool v);

    private:
        int cx;
        int cz;
        unsigned char cw;
        unsigned char cl;
        unsigned char ch;

        bool disable_faces = true;

        World *world = nullptr;

        //std::vector<Block> blocks;
        Block blocks[16 * 16 * 256];

        ChunkMesh *chunk_mesh = nullptr;

};

#endif