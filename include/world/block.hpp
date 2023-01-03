#ifndef __BLOCK_HPP__
#define __BLOCK_HPP__

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
        Block(const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type){
            this->x = x;
            this->y = y;
            this->z = z;
            this->type = type;
        }

        unsigned char get_x() const {
            return x;
        }

        unsigned char get_y() const {
            return y;
        }

        unsigned char get_z() const {
            return z;
        }

        unsigned char get_type() const {
            return type;
        }

    private:
        unsigned char x;
        unsigned char y;
        unsigned char z;

        unsigned char type;
};

#endif