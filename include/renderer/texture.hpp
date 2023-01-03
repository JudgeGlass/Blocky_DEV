#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <vector>

#include <GL/glew.h>

#include <world/block.hpp>

enum Face {
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
    ALL
};

static const GLfloat texture_uv_grass[] = {
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

static const GLfloat texture_uv_stone[] = {
    0.0f, 0.0f,
    0.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 1.0f/16.0f,
    1.0f/16.0f, 0.0f,
    0.0f, 0.0f
};

static const GLfloat texture_uv_glass[] = {
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 2.0f/16.0f,
    14.0f/16.0f, 1.0f/16.0f,
    13.0f/16.0f, 1.0f/16.0f,
};

static const GLfloat texture_uv_dirt[] = {
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f,
    3.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 1.0f/16.0f,
    4.0f/16.0f, 0.0f,
    3.0f/16.0f, 0.0f
};

static void add_texture_face(const unsigned char &block, Face face, std::vector<GLfloat> &texture_coords){
    if(block == 0) return;

    int offset = 0;
    switch (face)
    {
    case FRONT:
        offset = 4 * 12;
        break;
    case BACK:
        offset = 5 * 12;
        break;
    case LEFT:
        offset = 12;
        break;
    case RIGHT:
        offset = 0;
        break;
    case TOP:
        offset = 2 * 12;
        break;
    case BOTTOM:
        offset = 3 * 12;
        break;
    default:
        offset = 0;
        break;
    }

    for(int i = offset; i < offset + 12; i++){
        switch (block)
        {
        case ID::AIR:
            return;
        case ID::GRASS:
            texture_coords.push_back(texture_uv_grass[i]);
            break;
        case ID::STONE:
            texture_coords.push_back(texture_uv_stone[i]);
            break;
        case DIRT:
            texture_coords.push_back(texture_uv_dirt[i]);
            break;
        case GLASS:
            texture_coords.push_back(texture_uv_glass[i]);
            break;
        default:
            return;
        }
    }
}


#endif