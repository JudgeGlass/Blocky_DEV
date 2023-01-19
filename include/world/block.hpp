#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

/*  Block data layout (in bits)
 *  0000|0000 0000|0000 00000000 00000000
 *   x    l    z     s    y          t
 * */

enum ID{
    AIR,
    STONE,
    GRASS,
    DIRT,
    

    GLASS = 20
};

class Block{
    public:
        Block(){}
        Block(const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type, const unsigned char light_level, const bool is_sky){
            data |= (unsigned int)((x << 4) | light_level) << 24;
            data |= (unsigned int)((z << 4) | is_sky) << 16;
            data |= (unsigned int)y << 8;
            data |= (unsigned int)type;
        }

        void set_type(const unsigned char type){
            //this->type = type;
            data &= 0xFFFFFF00;
            data |= (unsigned int)type;
        }

        void set_light_level(const unsigned char l){
            //light = l;
            data &= 0xF0FFFFFF;

            data |= (unsigned int)((get_x() << 4) | l) << 24;
        }

        unsigned char get_x() const {
            //return x;
            return (data >> 28) & 0xF;
        }

        unsigned char get_y() const {
            //return y;
            return (data >> 8) & 0xFF;
        }

        unsigned char get_z() const {
            //return z;
            return (data >> 20) & 0xF;
        }

        unsigned char get_light() const {
            //return light;
            return (data >> 24) & 0xF;
        }

        bool get_is_sky() const {
            //return is_sky;
            return (data >> 16) & 0xF;
        }

        unsigned char get_type() const {
//            return type;
            return (data) & 0xFF;
        }

    private:

        unsigned int data = 0;
};

#endif