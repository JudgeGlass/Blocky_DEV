#ifndef __BLOCKY_FONT_HPP__
#define __BLOCKY_FONT_HPP__

#include <string>

class Font{

    public:
        Font(const std::string text, int x, int y) {
            this->text = text;
            this->x = x;
            this->y = y;
        }

        std::string getText() const{
            return text;
        }

        int getX() const {
            return x;
        }

        int getY() const {
            return y;
        }

    private:
        std::string text;

        int x;
        int y;
};

#endif //__BLOCKY_FONT_HPP__
