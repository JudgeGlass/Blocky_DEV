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
        Block(const unsigned char x, const unsigned char y, const unsigned char z, const unsigned char type, const float light_level, const bool is_sky){
            this->x = x;
            this->y = y;
            this->z = z;
            this->type = type;
            this->light = light_level;
            this->is_sky = is_sky;
        }

        void set_type(const unsigned char type){
            this->type = type;
        }

        void set_light_level(const float l){
            light = l;
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

        float get_light() const {
            return light;
        }

        bool get_is_sky() const {
            return is_sky;
        }

        unsigned char get_type() const {
            return type;
        }

    private:
        unsigned char x;
        unsigned char y;
        unsigned char z;

        float light;

        unsigned char type;
        bool is_sky;
};

#endif