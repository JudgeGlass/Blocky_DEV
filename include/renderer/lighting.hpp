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

struct LightRemoveNode {
    LightRemoveNode(unsigned char xx, unsigned char yy, unsigned char zz, Chunk *ch, float val) : x(xx), y(yy), z(zz), chunk(ch), value(val){}

    unsigned char x, y, z;
    float value;
    Chunk *chunk;
};

void gen_lighting(Chunk *c, World *world);
void del_lighting(Chunk *c, World *world, int bx, int by, int bz);

#endif