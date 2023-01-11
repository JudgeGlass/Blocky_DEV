#ifndef __LIGHTING_HPP__
#define __LIGHTING_HPP__

#include <queue>

#include <world/chunk.hpp>

class Chunk;
struct LightNode {
    LightNode(int xx, int yy, int zz, Chunk *ch) : x(xx), y(yy), z(zz), chunk(ch){}

    int x, y, z;
    Chunk *chunk;
};

#endif