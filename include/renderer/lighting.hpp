#ifndef __LIGHTING_HPP__
#define __LIGHTING_HPP__

#include <algorithm>

#include <world/chunk.hpp>

struct LightNode {
    LightNode(short i, Chunk *ch) : index(i), chunk(ch);

    short index;
    Chunk *chunk;
};

#endif