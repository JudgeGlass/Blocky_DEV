#ifndef __CHUNK_MESH__
#define __CHUNK_MESH__

#include <vector>
#include <memory>

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

class World;
class ChunkMesh{
    public:
        ChunkMesh(Block *blocks, int cx, int cz, const unsigned char cw, const unsigned char cl, const unsigned char ch, bool &disable_faces, World *world);
        ~ChunkMesh();

        void build();
        void rebuild(Block *blocks);

        void render(GLuint texture);

    private:
        int cx;
        int cz;
        unsigned char cw;
        unsigned char ch;
        unsigned char cl;
        
        bool disable_faces;
        
        Block *blocks;
        
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> texture_coords;

        std::vector<GLfloat> tvertices;
        std::vector<GLfloat> ttexture_coords;

        std::vector<GLfloat> light_levels;

        int vertices_size = 0;
        int texture_size = 0;
        int tvertices_size = 0;
        int ttexture_size = 0;
        int light_level_size = 0;

        World *world = nullptr;
        //std::shared_ptr<World> world;

        GLuint VAO;
        GLuint VBO;
        GLuint TVBO;
        GLuint TTBO;
        GLuint TBO;
        GLuint LBO;

        GLfloat *vBuff = nullptr;
        GLfloat *tBuff = nullptr;

        GLfloat *tvBuff = nullptr;
        GLfloat *ttBuff = nullptr;

        GLfloat *lBuff = nullptr;

        bool is_transparent(int x, int y, int z, unsigned char block_id);
        void add_face(int x, int y, int z, Face face, unsigned char type, float light);
        void add_face_vertices(const float* vertex_array, int x, int y, int z, float light);
};

#endif