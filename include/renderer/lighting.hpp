#ifndef __LIGHTING_HPP__
#define __LIGHTING_HPP__

#include <queue>

#include <world/world.hpp>
#include <world/chunk.hpp>
#include <world/block.hpp>

class World;
class Chunk;
struct LightNode {
    LightNode(unsigned char xx, unsigned char yy, unsigned char zz, Chunk *ch) : x(xx), y(yy), z(zz), chunk(ch){}

    unsigned char x, y, z;
    Chunk *chunk;
};

void gen_lighting(Chunk *c, World *world);

#endif