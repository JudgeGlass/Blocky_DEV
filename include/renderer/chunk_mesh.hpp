#ifndef __CHUNK_MESH__
#define __CHUNK_MESH__

#include <vector>

#include <GL/glew.h>

#include <world/block.hpp>
#include <world/world.hpp>
#include <renderer/texture.hpp>

static const GLfloat cube_vertex_right[] = { // CCW
    0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, 0.5f
};

static const GLfloat cube_vertex_left[] = { // CCW
    -0.5f,0.5f,-0.5f, // Left
    -0.5f,-0.5f,-0.5f,
    -0.5f,-0.5f,0.5f,
    -0.5f,-0.5f,0.5f,
    -0.5f,0.5f,0.5f,
    -0.5f,0.5f,-0.5f
};

static const GLfloat cube_vertex_top[] = { // CCW
    0.5f,0.5f,-0.5f,
    -0.5f,0.5f,-0.5f,
    -0.5f,0.5f,0.5f,
    -0.5f,0.5f,0.5f,
    0.5f,0.5f,0.5f,
    0.5f,0.5f,-0.5f
};

static const GLfloat cube_vertex_bottom[] = { // CCW
    -0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f
};

static const GLfloat cube_vertex_front[] = { //CCW
    -0.5f,0.5f,0.5f,
    -0.5f,-0.5f,0.5f,
    0.5f,-0.5f,0.5f,
    0.5f,-0.5f,0.5f,
    0.5f,0.5f,0.5f,
    -0.5f,0.5f,0.5f
};

static const GLfloat cube_vertex_back[] = { //CCW
    0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, -0.5f 
};

static const GLfloat texture_buffer[] = {
    0.125f, 0.0f,   // RIGHT
    0.125f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.f,
    0.125f, 0.f,

    0.125f, 0.0f, // LEFT
    0.125f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.f,
    0.125f, 0.f,

    0.0625f, 0.0f, // TOP
    0.0625f, 0.0625f,
    0.125f, 0.0625,
    0.125f, 0.0625f,
    0.125f, 0.0f,
    0.0625f, 0.0f,

    3.0f/16.0f, 0.0f, // BOTTOM
    3.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,

    0.125f, 0.0f, // FRONT
    0.125f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.f,
    0.125f, 0.f,

    0.125f, 0.0f,   // BACK
    0.125f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.f,
    0.125f, 0.f
};

class World;
class ChunkMesh{
    public:
        ChunkMesh(const std::vector<Block> &blocks, int cx, int cz, World *world);
        ~ChunkMesh();

        void build();

        void render(GLuint &texture);

        bool is_transparent(int x, int y, int z, unsigned char block_id);
    private:
        int cx;
        int cz;
        std::vector<Block> blocks;
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> texture_coords;
        std::vector<GLfloat> colors;

        int vertices_size = 0;
        int texture_size = 0;

        World *world = nullptr;

        GLuint VAO;
        GLuint VBO;
        GLuint TBO;

        GLfloat *vBuff = nullptr;
        GLfloat *tBuff = nullptr;
};

#endif