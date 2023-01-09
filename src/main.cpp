#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include <game/blocky.hpp>

int main(){
    std::cout << "Starting Blocky..." << std::endl;

    Blocky game(1600, 480*2);

    game.init();
    game.loop();

    return 0;
}