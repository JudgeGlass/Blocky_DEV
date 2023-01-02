#ifndef __CHUNK_MESH__
#define __CHUNK_MESH__

#include <vector>

#include <GL/glew.h>

#include <world/block.hpp>

static const GLfloat vertex_buffer[] = { // JUST FOR TESTING!
    0.5f,0.5f,-0.5f,
    0.5f,-0.5f,-0.5f,
    0.5f,-0.5f,0.5f,
    0.5f,-0.5f,0.5f,
    0.5f,0.5f,0.5f,
    0.5f,0.5f,-0.5f,

    -0.5f,0.5f,-0.5f,
    -0.5f,-0.5f,-0.5f,
    -0.5f,-0.5f,0.5f,
    -0.5f,-0.5f,0.5f,
    -0.5f,0.5f,0.5f,
    -0.5f,0.5f,-0.5f,

    -0.5f,0.5f,0.5f,
    -0.5f,0.5f,-0.5f,
    0.5f,0.5f,-0.5f,
    0.5f,0.5f,-0.5f,
    0.5f,0.5f,0.5f,
    -0.5f,0.5f,0.5f,


    -0.5f,-0.5f,0.5f,
    -0.5f,-0.5f,-0.5f,
     0.5f,-0.5f,-0.5f,
     0.5f,-0.5f,-0.5f,
     0.5f,-0.5f,0.5f,
    -0.5f,-0.5f,0.5f,

    -0.5f,0.5f,0.5f,
    -0.5f,-0.5f,0.5f,
    0.5f,-0.5f,0.5f,
    0.5f,-0.5f,0.5f,
    0.5f,0.5f,0.5f,
    -0.5f,0.5f,0.5f,

    -0.5f,0.5f,-0.5f,
    -0.5f,-0.5f,-0.5f,
    0.5f,-0.5f,-0.5f,
    0.5f,-0.5f,-0.5f,
    0.5f,0.5f,-0.5f,
    -0.5f,0.5f,-0.5f    
};

static const GLfloat texture_buffer[] = {
    0.125f, 0.0f,
    0.125f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.f,
    0.125f, 0.f,

    0.125f, 0.0f,
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

    0.125f, 0.0f,
    0.125f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.f,
    0.125f, 0.f,

    0.125f, 0.0f,
    0.125f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.f,
    0.125f, 0.f,

    0.125f, 0.0f,
    0.125f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.0625f,
    0.1875f, 0.f,
    0.125f, 0.f,
};

class ChunkMesh{
    public:
        ChunkMesh(const std::vector<Block> &blocks);

        void build(GLuint &texture);

        void render(GLuint &texture);
    private:
        std::vector<Block> blocks;
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> texture_coords;
        std::vector<GLfloat> colors;

        int vertices_size = 0;
        int texture_size = 0;

        GLuint VAO;
        GLuint VBO;
        GLuint TBO;

        GLfloat *vBuff = nullptr;
        GLfloat *tBuff = nullptr;
};

#endif